
#include "MeshLoader.h"
#include "TextureLoader.h"
#include "Application.h"
#include "C_Mesh.h"
#include "C_Texture.h"
#include "C_Camera.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

vector<MeshInfo*> MeshLoader::meshList;

void MeshLoader::DebugMode()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}

void MeshLoader::LoadFile(const char* file_path)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{

		GameObject* FbxGameObject = new GameObject(App->scene_intro->gameObjects[0], file_path);

		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			MeshInfo* mesh = new MeshInfo();
			
			// copy vertices
			mesh->num_vertex = scene->mMeshes[i]->mNumVertices;
			mesh->vertex = new float[mesh->num_vertex * VERTEX_FEATURES];
			//memcpy(ourMesh->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * ourMesh->num_vertex * 3);
			App->editorGui->console.AddLog(__FILE__, __LINE__, "New mesh with %d vertices", mesh->num_vertex);

			for (int v = 0; v < mesh->num_vertex; v++) {
				// Vertex
				mesh->vertex[v * VERTEX_FEATURES] = scene->mMeshes[i]->mVertices[v].x;
				mesh->vertex[v * VERTEX_FEATURES + 1] = scene->mMeshes[i]->mVertices[v].y;
				mesh->vertex[v * VERTEX_FEATURES + 2] = scene->mMeshes[i]->mVertices[v].z;

				if (scene->mMeshes[i]->HasTextureCoords(0))
				{
					// UVs
					mesh->vertex[v * VERTEX_FEATURES + 3] = scene->mMeshes[i]->mTextureCoords[0][v].x;
					mesh->vertex[v * VERTEX_FEATURES + 4] = scene->mMeshes[i]->mTextureCoords[0][v].y;
				}
			}

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				mesh->num_index = scene->mMeshes[i]->mNumFaces * 3;
				mesh->index = new uint[mesh->num_index]; // assume each face is a triangle

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						App->editorGui->console.AddLog(__FILE__, __LINE__, "WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&mesh->index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}

			uint ID = App->scene_intro->CreateGameObject(FbxGameObject, scene->mMeshes[i]->mName.C_Str());

			//Mesh
			dynamic_cast<C_Mesh*>(App->scene_intro->gameObjects[ID]->CreateComponent(Component::TYPE::MESH))->SetMesh(mesh, scene->mMeshes[i]->mName.C_Str());
			GetNodeInfo(scene, scene->mRootNode, FbxGameObject);

			//Texture
			mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->tex);
			dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[ID]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(mesh->tex); 


			MeshLoader::SetUpMesh(mesh);

			
		}

		aiReleaseImport(scene);

	}
	else
	{
		LOG("Error loading scene % s", file_path);

	}
		
}

void MeshInfo::RenderMesh(const GLfloat* globalTransform)
{

	//Wireframe mode
	if (App->editorGui->wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Enable/Disable lights
	if (App->editorGui->lights_active == false)
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);

	//Enable/Disable depth test
	if (App->editorGui->depth_test_active == false)
		glDisable(GL_DEPTH_TEST);
	else
		glEnable(GL_DEPTH_TEST);

	//Enable/Disable cull face
	if (App->editorGui->cull_face_active == false)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);


	// Bind Buffers
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);

	glBindTexture(GL_TEXTURE_2D, texture_id);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);

	// Vertex Array [ x, y, z, u, v ]
	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, (void*)(3 * sizeof(float)));
	glNormalPointer(GL_FLOAT, sizeof(float) * VERTEX_FEATURES, NULL);
	

	glPushMatrix();
	//glMultMatrixf(globalTransform); 

	// Draw
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

	glPopMatrix();

	glClientActiveTexture(GL_TEXTURE0);

	

	// Unbind buffers
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_COORD_ARRAY);

}

void MeshLoader::Render()
{
	for (size_t i = 0; i < meshList.size(); i++) {
		//meshList[i]->RenderMesh();
	}
}


void MeshLoader::CleanUp()
{
	
	meshList.clear();

	// detach log stream
	aiDetachAllLogStreams();
}

void MeshLoader::SetUpMesh(MeshInfo* ourMesh)
{
	//Create vertices and indices buffers
	glGenBuffers(1, (GLuint*)&(ourMesh->id_vertex));
	glGenBuffers(1, (GLuint*)&(ourMesh->id_index));

	//Bind and fill buffers
	glBindBuffer(GL_ARRAY_BUFFER, ourMesh->id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ourMesh->num_vertex * 5, ourMesh->vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ourMesh->id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * ourMesh->num_index, ourMesh->index, GL_STATIC_DRAW);

	//Unbind buffers
	glDisableClientState(GL_VERTEX_ARRAY);

	//Add mesh to meshes vector
	meshList.push_back(ourMesh);
}

const char* MeshLoader::GetMeshName(const char* mesh_name)
{
	const char* name = mesh_name;
	return name;
}


void MeshLoader::GetNodeInfo(const aiScene* rootScene, aiNode* rootNode, GameObject* goParent)
{
	aiVector3D translation, scaling;
	aiQuaternion quatRot;
	rootNode->mTransformation.Decompose(scaling, quatRot, translation);

	float3 pos(translation.x, translation.y, translation.z);
	float3 scale(scaling.x, scaling.y, scaling.z);
	Quat rot(quatRot.x, quatRot.y, quatRot.z, quatRot.w);

	dynamic_cast<C_Transform*>(goParent->GetComponent(Component::TYPE::TRANSFORM))->SetTransform(pos, rot, scale);




	// We make it recursive for its children
	if (rootNode->mNumChildren > 0)
	{
		for (int n = 0; n < rootNode->mNumChildren; n++)
		{
			GetNodeInfo(rootScene, rootNode->mChildren[n], goParent);
		}
	}
}

void MeshInfo::GenerateBoundingBox()
{
	localAABB.SetNegativeInfinity();
	localAABB.Enclose((float3*)vertex, num_vertex);
	
}

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
		GetNodeInfo(scene, scene->mRootNode, FbxGameObject);
		
		for (uint i = 0; i < scene->mRootNode->mNumChildren; i++)
		{
			MeshInfo* mesh = new MeshInfo();
			
			aiMesh* ai_mesh = scene->mMeshes[scene->mRootNode->mChildren[i]->mMeshes[0]];

			// copy vertices
			mesh->num_vertex = ai_mesh->mNumVertices;
			mesh->vertex = new float[mesh->num_vertex * VERTEX_FEATURES];
			
			App->editorGui->console.AddLog(__FILE__, __LINE__, "New mesh with %d vertices", mesh->num_vertex);

			for (int v = 0; v < mesh->num_vertex; v++) {
				// Vertex
				mesh->vertex[v * VERTEX_FEATURES] = ai_mesh->mVertices[v].x;
				mesh->vertex[v * VERTEX_FEATURES + 1] = ai_mesh->mVertices[v].y;
				mesh->vertex[v * VERTEX_FEATURES + 2] = ai_mesh->mVertices[v].z;

				if (ai_mesh->HasTextureCoords(0))
				{
					// UVs
					mesh->vertex[v * VERTEX_FEATURES + 3] = ai_mesh->mTextureCoords[0][v].x;
					mesh->vertex[v * VERTEX_FEATURES + 4] = ai_mesh->mTextureCoords[0][v].y;
				}
			}

			// copy faces
			if (ai_mesh->HasFaces())
			{
				mesh->num_index = ai_mesh->mNumFaces * 3;
				mesh->index = new uint[mesh->num_index]; // assume each face is a triangle

				for (uint j = 0; j < ai_mesh->mNumFaces; ++j)
				{
					if (ai_mesh->mFaces[j].mNumIndices != 3)
					{
						App->editorGui->console.AddLog(__FILE__, __LINE__, "WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&mesh->index[j * 3], ai_mesh->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}

			mesh->textures[0] = "Assets/Street2/Building_V02_C.png";
			mesh->textures[1] = "Assets/Street2/Building_V01_C.png";
			mesh->textures[2] = "Assets/Street2/building05-_c.png";
			mesh->textures[3] = "Assets/Street2/building03_c.png";
			mesh->textures[4] = "Assets/Street2/building_025_c.png";
			mesh->textures[5] = "Assets/Street2/building_016_c.png";
			mesh->textures[6] = "Assets/Street2/building-06_-c.png";
			mesh->textures[7] = "Assets/Street2/building-06_-c-.png";
			mesh->textures[8] = "Assets/Street2/building-01_c.png";


			mesh->ID = App->scene_intro->CreateGameObject(FbxGameObject, scene->mRootNode->mChildren[i]->mName.C_Str());

			//Mesh
			dynamic_cast<C_Mesh*>(App->scene_intro->gameObjects[mesh->ID]->CreateComponent(Component::TYPE::MESH))->SetMesh(mesh, scene->mRootNode->mChildren[i]->mName.C_Str());
			GetNodeInfo(scene, scene->mRootNode->mChildren[i], App->scene_intro->gameObjects[mesh->ID]);


			/*casa 40: Building_V01_C
			casa 41 : Building_V02_C
			casa 36 : building - 06_ - c -

			casa 38, 37, 34, 26, 22 : building05 - _c
			casa 33 : building - 06_ - c
			casa 24 : building_025_c
			casa 23 : building_016_c
			casa 32, 14 : building03_c
			casa 17 : building - 01_c*/

			if (App->scene_intro->gameObjects[mesh->ID]->name == "City_building_040")
			{
				mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->textures[1]);
				dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[mesh->ID]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(mesh->textures[1]);
			}
			else if (App->scene_intro->gameObjects[mesh->ID]->name == "City_building_041")
			{
				mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->textures[0]);
				dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[mesh->ID]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(mesh->textures[0]);
			}
			else if (App->scene_intro->gameObjects[mesh->ID]->name == "City_building_036")
			{
				mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->textures[7]);
				dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[mesh->ID]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(mesh->textures[7]);
			}
			else if (App->scene_intro->gameObjects[mesh->ID]->name == "City_building_038" || App->scene_intro->gameObjects[mesh->ID]->name == "City_building_037" || App->scene_intro->gameObjects[mesh->ID]->name == "City_building_034" || App->scene_intro->gameObjects[mesh->ID]->name == "City_building_026" || App->scene_intro->gameObjects[mesh->ID]->name == "City_building_022")
			{
				mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->textures[2]);
				dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[mesh->ID]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(mesh->textures[2]);
			}
			else if (App->scene_intro->gameObjects[mesh->ID]->name == "City_building_033")
			{
				mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->textures[6]);
				dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[mesh->ID]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(mesh->textures[6]);
			}
			else if (App->scene_intro->gameObjects[mesh->ID]->name == "City_building_024")
			{
				mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->textures[4]);
				dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[mesh->ID]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(mesh->textures[4]);
			}
			else if (App->scene_intro->gameObjects[mesh->ID]->name == "City_building_023")
			{
				mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->textures[5]);
				dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[mesh->ID]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(mesh->textures[5]);
			}
			else if (App->scene_intro->gameObjects[mesh->ID]->name == "City_building_032" && App->scene_intro->gameObjects[mesh->ID]->name == "City_building_014")
			{
				mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->textures[3]);
				dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[mesh->ID]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(mesh->textures[3]);
			}
			else if (App->scene_intro->gameObjects[mesh->ID]->name == "City_building_017")
			{
				mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->textures[8]);
				dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[mesh->ID]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(mesh->textures[8]);
			}
			

			mesh->GenerateLocalBoundingBox();
			

			MeshLoader::SetUpMesh(mesh);

			
		}

		aiReleaseImport(scene);

	}
	else
	{
		LOG("Error loading scene % s", file_path);

	}
		
}

void MeshInfo::RenderMesh(const GLfloat* globalTransform, uint texID)
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

	RenderAABB();

	// Bind Buffers
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);

	glBindTexture(GL_TEXTURE_2D, texID);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);

	// Vertex Array [ x, y, z, u, v ]
	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, (void*)(3 * sizeof(float)));
	glNormalPointer(GL_FLOAT, sizeof(float) * VERTEX_FEATURES, NULL);
	

	glPushMatrix();
	glMultMatrixf(globalTransform); 

	// Draw
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

	glPopMatrix();

	glClientActiveTexture(GL_TEXTURE0);

	// Unbind buffers
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_COORD_ARRAY);

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


void MeshLoader::GetNodeInfo(const aiScene* rootScene, aiNode* rootNode, GameObject* go)
{
	if (go->name == "Mesh.025")
	{
		int y = 0;
	}
	aiVector3D translation, scaling;
	aiQuaternion quatRot;
	rootNode->mTransformation.Decompose(scaling, quatRot, translation);

	float3 pos(translation.x, translation.y, translation.z);
	float3 scale(scaling.x, scaling.y, scaling.z);

	if (rootNode == rootScene->mRootNode)
	{
		scale *= 100;
	}

	Quat rot(quatRot.x, quatRot.y, quatRot.z, quatRot.w);

	dynamic_cast<C_Transform*>(go->GetComponent(Component::TYPE::TRANSFORM))->SetTransform(pos/100, rot, scale/100);

}

void MeshInfo::GenerateLocalBoundingBox()
{

	//TODO: Should this be here?
	float* vertex_positions = new float[num_vertex * 3];
	for (size_t i = 0; i < num_vertex; i++)
	{
		vertex_positions[i * 3] = vertex[i * VERTEX_FEATURES];
		vertex_positions[i * 3 + 1] = vertex[i * VERTEX_FEATURES + 1];
		vertex_positions[i * 3 + 2] = vertex[i * VERTEX_FEATURES + 2];
	}

	localAABB.SetNegativeInfinity();
	localAABB.Enclose((float3*)vertex_positions, num_vertex);
	localAABB_init = true;
	
}

void MeshInfo::GenerateGlobalBoundingBox()
{
	// Generate global OBB
	globalOBB = localAABB;
	globalOBB.Transform(App->scene_intro->gameObjects[ID]->transform->GetGlobalMatrix());
	
	// Generate global AABB
	globalAABB.SetNegativeInfinity();
	globalAABB.Enclose(globalOBB);
}

void MeshInfo::RenderAABB()
{
	float3 vertexAABB[8];

	globalAABB.GetCornerPoints(vertexAABB);


	if (App->editorGui->show_AABB)
	{
		glBegin(GL_LINES);
		glVertex3f(vertexAABB[0].x, vertexAABB[0].y, vertexAABB[0].z);
		glVertex3f(vertexAABB[1].x, vertexAABB[1].y, vertexAABB[1].z);
		glVertex3f(vertexAABB[0].x, vertexAABB[0].y, vertexAABB[0].z);
		glVertex3f(vertexAABB[4].x, vertexAABB[4].y, vertexAABB[4].z);
		glVertex3f(vertexAABB[1].x, vertexAABB[1].y, vertexAABB[1].z);
		glVertex3f(vertexAABB[5].x, vertexAABB[5].y, vertexAABB[5].z);
		glVertex3f(vertexAABB[4].x, vertexAABB[4].y, vertexAABB[4].z);
		glVertex3f(vertexAABB[5].x, vertexAABB[5].y, vertexAABB[5].z);

		glVertex3f(vertexAABB[2].x, vertexAABB[2].y, vertexAABB[2].z);
		glVertex3f(vertexAABB[3].x, vertexAABB[3].y, vertexAABB[3].z);
		glVertex3f(vertexAABB[2].x, vertexAABB[2].y, vertexAABB[2].z);
		glVertex3f(vertexAABB[6].x, vertexAABB[6].y, vertexAABB[6].z);
		glVertex3f(vertexAABB[6].x, vertexAABB[6].y, vertexAABB[6].z);
		glVertex3f(vertexAABB[7].x, vertexAABB[7].y, vertexAABB[7].z);
		glVertex3f(vertexAABB[3].x, vertexAABB[3].y, vertexAABB[3].z);
		glVertex3f(vertexAABB[7].x, vertexAABB[7].y, vertexAABB[7].z);

		glVertex3f(vertexAABB[0].x, vertexAABB[0].y, vertexAABB[0].z);
		glVertex3f(vertexAABB[2].x, vertexAABB[2].y, vertexAABB[2].z);
		glVertex3f(vertexAABB[1].x, vertexAABB[1].y, vertexAABB[1].z);
		glVertex3f(vertexAABB[3].x, vertexAABB[3].y, vertexAABB[3].z);
		glVertex3f(vertexAABB[4].x, vertexAABB[4].y, vertexAABB[4].z);
		glVertex3f(vertexAABB[6].x, vertexAABB[6].y, vertexAABB[6].z);
		glVertex3f(vertexAABB[5].x, vertexAABB[5].y, vertexAABB[5].z);
		glVertex3f(vertexAABB[7].x, vertexAABB[7].y, vertexAABB[7].z);
		glEnd();
	}
	
	
}


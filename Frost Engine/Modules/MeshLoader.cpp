
#include "MeshLoader.h"
#include "TextureLoader.h"
#include "Application.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

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
			mesh->texture_id = TextureLoader::LoadTextureFromFile(mesh->tex);

			App->scene_intro->CreateGameObject(App->scene_intro->gameObjects[0], scene->mMeshes[i]->mName.C_Str());

			MeshLoader::SetUpMesh(mesh);

			
		}

		aiReleaseImport(scene);

	}
	else
	{
		LOG("Error loading scene % s", file_path);

	}
		
}

void MeshInfo::RenderMesh()
{
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
	

	// Draw
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

	glClientActiveTexture(GL_TEXTURE0);

	// Unbind buffers
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_COORD_ARRAY);

}

void MeshLoader::Render()
{
	for (size_t i = 0; i < meshList.size(); i++) {
		meshList[i]->RenderMesh();
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

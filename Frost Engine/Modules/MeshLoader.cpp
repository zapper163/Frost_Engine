
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

void MeshLoader::LoadFile(const char* file_path, MeshInfo* ourMesh)
{
	
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{

			MeshInfo* ourMesh = new MeshInfo();
			// copy vertices
			ourMesh->num_vertex = scene->mMeshes[i]->mNumVertices;
			ourMesh->vertex = new float[ourMesh->num_vertex * VERTEX_FEATURES];
			//memcpy(ourMesh->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * ourMesh->num_vertex * 3);
			App->editorGui->console.AddLog(__FILE__, __LINE__, "New mesh with %d vertices", ourMesh->num_vertex);

			for (int v = 0; v < ourMesh->num_vertex; v++) {
				// Vertex
				ourMesh->vertex[v * VERTEX_FEATURES] = scene->mMeshes[i]->mVertices[v].x;
				ourMesh->vertex[v * VERTEX_FEATURES + 1] = scene->mMeshes[i]->mVertices[v].y;
				ourMesh->vertex[v * VERTEX_FEATURES + 2] = scene->mMeshes[i]->mVertices[v].z;

				if (scene->mMeshes[i]->HasTextureCoords(0))
				{
					// UVs
					ourMesh->vertex[v * VERTEX_FEATURES + 3] = scene->mMeshes[i]->mTextureCoords[0][v].x;
					ourMesh->vertex[v * VERTEX_FEATURES + 4] = scene->mMeshes[i]->mTextureCoords[0][v].y;
				}
				// -------------------------------------------------------------------------------------- In a future
				//if (scene->mMeshes[i]->HasNormals())
				//{
					//newMesh->vertex[v * VERTEX_FEATURES + 5] = scene->mMeshes[i]->mNormals[v].x;
					//newMesh->vertex[v * VERTEX_FEATURES + 6] = scene->mMeshes[i]->mNormals[v].y;
					//newMesh->vertex[v * VERTEX_FEATURES + 7] = scene->mMeshes[i]->mNormals[v].z;
				//}
			}

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				ourMesh->num_index = scene->mMeshes[i]->mNumFaces * 3;
				ourMesh->index = new uint[ourMesh->num_index]; // assume each face is a triangle

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						App->editorGui->console.AddLog(__FILE__, __LINE__, "WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&ourMesh->index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}

				MeshLoader::SetUpMesh(ourMesh);
				//meshList.push_back(ourMesh);
				
			}

			ourMesh->texture_id = TextureLoader::LoadTextureFromFile(ourMesh->tex);

		}
		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene % s", file_path);
}

void MeshInfo::RenderMesh()
{

	//Bind Texture
	glEnable(GL_TEXTURE_COORD_ARRAY);
	//glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	// Bind Buffers
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);

	// Vertex Array [ x, y, z, u, v ]
	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, (void*)(3 * sizeof(float)));
	glNormalPointer(GL_FLOAT, sizeof(float) * VERTEX_FEATURES, NULL);

	//glPushMatrix();

	// Draw
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

	//glPopMatrix(); 

	for (int v = 0; v < num_vertex; v++) {
		//glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, &vertex[v * VERTEX_FEATURES]);
		glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, &vertex[v * VERTEX_FEATURES + 1]);
		glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, &vertex[v * VERTEX_FEATURES + 2]);
		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, &vertex[v * VERTEX_FEATURES + 3]);
		glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_FEATURES, &vertex[v * VERTEX_FEATURES + 4]);
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(float) * VERTEX_FEATURES, &vertex[v * VERTEX_FEATURES + 5]);
		glNormalPointer(GL_FLOAT, sizeof(float) * VERTEX_FEATURES, &vertex[v * VERTEX_FEATURES + 6]);
		glNormalPointer(GL_FLOAT, sizeof(float) * VERTEX_FEATURES, &vertex[v * VERTEX_FEATURES + 7]);

		//glDrawRangeElements(GL_TRIANGLES, vertex[v * VERTEX_FEATURES], vertex[v * VERTEX_FEATURES + 1], vertex[v * VERTEX_FEATURES + 2], GL_UNSIGNED_SHORT, index);

	}

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
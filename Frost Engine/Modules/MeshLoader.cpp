
#include "MeshLoader.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

void MeshLoader::DebugMode()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}

void MeshLoader::LoadFile(const char* file_path, MeshData* ourMesh)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(scene);
		LOG("% s loaded, all good!", file_path);
		
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			
			// copy vertices
			//ourMesh->num_vertex = scene->mMeshes[i]->mNumVertices;
			//ourMesh->vertex = new float[ourMesh->num_vertex * 3];
			//memcpy(ourMesh->vertex, &scene->mMeshes[i]->mVertices->x, sizeof(float) * ourMesh->num_vertex * 3);
			LOG("New mesh with %d vertices", ourMesh->num_vertex);
			
			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				//ourMesh->num_vertex = scene->mMeshes[i]->mNumFaces * 3;
				//ourMesh->index = new uint[ourMesh->num_index]; // assume each face is a triangle

				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						//memcpy(&ourMesh->index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}
		}
	}
	else
		LOG("Error loading scene % s", file_path);
}

void MeshLoader::CreateMeshBuffer(MeshData ourMesh)
{
	glGenBuffers(1, (GLuint*)(ourMesh.id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, ourMesh.id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ourMesh.num_vertex * 3, ourMesh.vertex, GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*)&(ourMesh.id_index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ourMesh.id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * ourMesh.num_index, ourMesh.index, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ourMesh.id_index);
}

void MeshLoader::RenderMesh(MeshData ourMesh)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);


	glDrawElements(GL_TRIANGLES, ourMesh.num_vertex, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
}
void MeshLoader::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();
}
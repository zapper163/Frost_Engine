
#include "MeshLoader.h"
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
			// copy vertices
			ourMesh->num_vertex = scene->mMeshes[i]->mNumVertices;
			ourMesh->vertex = new float[ourMesh->num_vertex * 3];
			memcpy(ourMesh->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * ourMesh->num_vertex * 3);
			App->editorGui->console.AddLog(__FILE__, __LINE__, "New mesh with %d vertices", ourMesh->num_vertex);

			ourMesh->num_uvs = *scene->mMeshes[i]->mNumUVComponents;
			ourMesh->uvs = new float[ourMesh->num_uvs * 2];
			memcpy(ourMesh->uvs, scene->mMeshes[i]->mNumUVComponents, sizeof(float) * ourMesh->num_uvs * 2);
			

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
				meshList.push_back(ourMesh);
			}

		}

		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene % s", file_path);
}

void MeshInfo::RenderMesh()
{
	glBegin(GL_TRIANGLES);

	for (uint i = 0; i < num_index; i++) {
		//glTexCoord2f(vertex[index[i] * 3], vertex[index[i] * 3 + 1], vertex[index[i] * 3 + 2]);
		glVertex3f(vertex[index[i] * 3], vertex[index[i] * 3 + 1], vertex[index[i] * 3 + 2]);
	}

	for (uint z = 0; z < num_uvs; z++)
	{
		glTexCoord2f(uvs[z] * 2, uvs[z] * 2 + 1);
	}

	glEnd();
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

/*void MeshInfo::SetUpMesh()
{
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
  
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0)
}*/
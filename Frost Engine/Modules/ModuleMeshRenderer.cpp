#include "Globals.h"
#include "Application.h"
#include "ModuleMeshRenderer.h"
#include "TextureLoader.h"



#include "DevIL/include/il.h"
#include "DevIL/include/ilut.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

ModuleMeshRenderer::ModuleMeshRenderer(bool start_enabled) : Module(start_enabled)
{
}

// Destructor
ModuleMeshRenderer::~ModuleMeshRenderer()
{
}


// Called before render is available
bool ModuleMeshRenderer::Init()
{
	//Initialize DevIL
	ilInit();
	ilClearColour(255, 255, 255, 000);
	texture_ID = TextureLoader::CheckerTexture();

	LoadFile("Assets/BakerHouse.fbx");
	
	return true;
}

// Called every draw update
update_status ModuleMeshRenderer::PreUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

update_status ModuleMeshRenderer::Update(float dt)
{
	

	return UPDATE_CONTINUE;
}

update_status ModuleMeshRenderer::PostUpdate(float dt)
{
	for (int i = 0; i < meshList.size(); i++) {
		meshList[i]->RenderMesh(texture_ID);
	}

	//FrameBuffer     
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleMeshRenderer::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}


void ModuleMeshRenderer::LoadFile(const char* file_path)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			MeshInfo* ourMesh = new MeshInfo();
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
				LoadBuffers(ourMesh);
				meshList.push_back(ourMesh);
			}

		}

		aiReleaseImport(scene);
	}
}

void MeshInfo::RenderMesh(uint texture_ID)
{
	//Bind checker texture
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_ID);

	// Binding buffers
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	// Draw
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

	// Unbind buffers
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ModuleMeshRenderer::LoadBuffers(MeshInfo* ourMesh)
{
	//Create vertices and indices buffers
	glGenBuffers(1, (GLuint*)&(ourMesh->id_vertex));
	glGenBuffers(1, (GLuint*)&(ourMesh->id_index));

	//Bind and fill buffers
	glBindBuffer(GL_ARRAY_BUFFER, ourMesh->id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ourMesh->num_vertex * 3, ourMesh->vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ourMesh->id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * ourMesh->num_index, ourMesh->index, GL_STATIC_DRAW);

	//Unbind buffers
	glDisableClientState(GL_VERTEX_ARRAY);

	//Add mesh to meshes vector
	meshList.push_back(ourMesh);
}

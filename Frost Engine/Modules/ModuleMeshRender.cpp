#include "Globals.h"
#include "Application.h"
#include "ModuleMeshRender.h"

#include "MeshLoader.h"
#include "TextureLoader.h"
#include "GameObject.h"

#include <iostream>
#include <filesystem>


#define MAX_KEYS 300



ModuleMeshRender::ModuleMeshRender(bool start_enabled) : Module(start_enabled)
{

}

// Destructor
ModuleMeshRender::~ModuleMeshRender()
{
}

// Called before render is available
bool ModuleMeshRender::Init()
{
	bool ret = true;

	LOG("Mesh Renderer started");
	App->editorGui->console.AddLog(__FILE__, __LINE__, "Mesh Renderer started");


	
	// Checker Texture
	// 
	// Load pattern into image data array
	/*
	int value;
	for (int row = 0; row < IMAGE_ROWS; row++) {
		for (int col = 0; col < IMAGE_COLS; col++) {
			// Each cell is 8x8, value is 0 or 255 (black or white)
			value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
			imageData[row][col][0] = (GLubyte)value;
			imageData[row][col][1] = (GLubyte)value;
			imageData[row][col][2] = (GLubyte)value;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB,
		GL_UNSIGNED_BYTE, imageData);  // Create texture from image data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	*/


	return ret;
}

bool ModuleMeshRender::Start()
{

	GameObject* Root = new GameObject(NULL, "World");
	
	App->scene_intro->gameObjects[0] = Root;

	MeshLoader::LoadFile(filepath);

	if (cube)
	{
		MeshLoader::LoadFile(cube_filepath);
	}

	if (cone)
	{
		MeshLoader::LoadFile(cone_filepath);
	}

	if (sphere)
	{
		MeshLoader::LoadFile(sphere_filepath);
	}


	return true;
}

// Called every draw update
update_status ModuleMeshRender::PreUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

update_status ModuleMeshRender::Update(float dt)
{
	MeshLoader::Render();

	if (cube)
	{
		//PrintCubeV2();
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleMeshRender::CleanUp()
{
	LOG("Destroying Mesh Renderer");
	App->editorGui->console.AddLog(__FILE__, __LINE__, "Destroying Mesh Renderer");

	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}


void ModuleMeshRender::InitCube()
{
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals) + sizeof(colors), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);                             // copy vertices starting from 0 offest
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);                // copy normals after vertices
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals), sizeof(colors), colors);  // copy colours after normals
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ModuleMeshRender::RefreshCube()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
}

void ModuleMeshRender::PrintCube()
{

	// enable vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);

	
	glEnableClientState(GL_COLOR_ARRAY);
	

	glEnableClientState(GL_VERTEX_ARRAY);

	
	glNormalPointer(GL_FLOAT, 0, (void*)sizeof(vertices));
	glColorPointer(3, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals)));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawElements(GL_TRIANGLES,            // primitive type
		36,                      // # of indices
		GL_UNSIGNED_INT,         // data type
		(void*)0);               // ptr to indices

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void ModuleMeshRender::PrintCubeV2()
{

	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	//glPushMatrix();
	glTranslatef(-1.5, 1.5, -1.5);
	glPopMatrix();

}

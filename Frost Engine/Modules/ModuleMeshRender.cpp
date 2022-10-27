#include "Globals.h"
#include "Application.h"
#include "ModuleMeshRender.h"

#include "MeshLoader.h"
#include "TextureLoader.h"

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

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//MeshLoader::LoadFile(filepath, &houseMesh);
	


	return ret;
}

// Called every draw update
update_status ModuleMeshRender::PreUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}

update_status ModuleMeshRender::Update(float dt)
{
	//MeshLoader::Render();

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleMeshRender::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
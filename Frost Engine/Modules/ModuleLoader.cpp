#include "Globals.h"
#include "Application.h"
#include "ModuleLoader.h"
#include "SDL\include\SDL_opengl.h"


#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include "SDL/include/SDL_opengl.h"
#endif

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleLoader::ModuleLoader(bool start_enabled) : Module(start_enabled)
{
}

// Destructor
ModuleLoader::~ModuleLoader()
{}

// Called before render is available
bool ModuleLoader::Init()
{
	bool ret = true;



	return ret;
}


// PostUpdate present buffer to screen
update_status ModuleLoader::PostUpdate(float dt)
{
	


	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleLoader::CleanUp()
{
	LOG("");

	// Cleanup
	
	return true;
}


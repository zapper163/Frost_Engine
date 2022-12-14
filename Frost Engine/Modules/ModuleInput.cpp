#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "MeshLoader.h"
#include "TextureLoader.h"
#include "C_Texture.h"
#include "C_Mesh.h"

#include "ImGui/imgui_impl_sdl.h"

#include <iostream>


#define MAX_KEYS 300



ModuleInput::ModuleInput(bool start_enabled) : Module(start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KEY_STATE) * MAX_MOUSE_BUTTONS);

}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[] keyboard;
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	App->editorGui->console.AddLog(__FILE__, __LINE__, "Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	//SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		App->editorGui->console.AddLog(__FILE__, __LINE__, "SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());

		ret = false;
	}

	


	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate(float dt)
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	
	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	for(int i = 0; i < 5; ++i)
	{
		if(buttons & SDL_BUTTON(i))
		{
			if(mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if(mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;

	bool quit = false;
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);

		switch(e.type)
		{
			case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;
			break;

			case SDL_MOUSEMOTION:
			mouse_x = e.motion.x / SCREEN_SIZE;
			mouse_y = e.motion.y / SCREEN_SIZE;

			mouse_x_motion = e.motion.xrel / SCREEN_SIZE;
			mouse_y_motion = e.motion.yrel / SCREEN_SIZE;
			break;

			case SDL_QUIT:
			quit = true;
			break;

			case SDL_WINDOWEVENT:
			{
				if(e.window.event == SDL_WINDOWEVENT_RESIZED)
					App->renderer3D->OnResize(e.window.data1, e.window.data2);
				break;
			}

			case (SDL_DROPFILE): 
			{   
				dropped_filedir = e.drop.file;
				std::string fn = e.drop.file;
				if (fn.substr(fn.find_last_of(".") + 1) == "fbx") {
					MeshLoader::LoadFile(dropped_filedir);
					App->editorGui->console.AddLog(__FILE__, __LINE__, "Fbx Loaded");
				}
				else if(fn.substr(fn.find_last_of(".") + 1) == "png") {

					C_Mesh* mesh = dynamic_cast<C_Mesh*>(App->scene_intro->gameobject_selected->GetComponent(Component::TYPE::MESH));
					mesh->GetMesh()->texture_id = TextureLoader::LoadTextureFromFile(dropped_filedir);
					dynamic_cast<C_Texture*>(App->scene_intro->gameobject_selected->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(dropped_filedir);

					
					App->editorGui->console.AddLog(__FILE__, __LINE__, "Png Loaded");
				}

				SDL_free(dropped_filedir);
				break;
			}
		}
	}

	if(quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP || App->editorGui->show_main_window == false)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

update_status ModuleInput::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->debug = !App->debug;


	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	App->editorGui->console.AddLog(__FILE__, __LINE__, "Quitting SDL input event subsystem");

	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
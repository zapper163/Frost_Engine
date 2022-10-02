#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleLoader : public Module
{
public:
	ModuleLoader(bool start_enabled = true);
	~ModuleLoader();

	bool Init();
	update_status PostUpdate(float dt) override;
	bool CleanUp();


public:

	SDL_GLContext context;

	bool show_demo_window = false;
	bool show_credits_window = false;
	bool show_main_window = true;
	bool show_hardware_window = false;
	
};
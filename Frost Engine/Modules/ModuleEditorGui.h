#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleEditorGui : public Module
{
public:
	ModuleEditorGui(bool start_enabled = true);
	~ModuleEditorGui();

	bool Init();
	update_status PreUpdate(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();


public:

	SDL_GLContext context;

	bool show_demo_window = true;
	bool show_credits_window = false;
	bool show_main_window = true;
	
};
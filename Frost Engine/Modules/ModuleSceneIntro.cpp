#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"



std::map<uint, GameObject*> ModuleSceneIntro::gameObjects;


ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	App->editorGui->console.AddLog(__FILE__, __LINE__, "Loading Intro assets");

	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	//primitives updated
	for (uint n = 0; n < primitives.Count(); n++)
	{
		primitives[n]->Update();
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	//primitives rendered
	for (uint n = 0; n < primitives.Count(); n++)
	{
		primitives[n]->Render();
	}

	return UPDATE_CONTINUE;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->editorGui->console.AddLog(__FILE__, __LINE__, "Unloading Intro scene");


	for (uint n = 0; n < primitives.Count(); n++)
	{
		delete primitives[n];
	}
	primitives.Clear();

	return true;
}


void ModuleSceneIntro::CreateGameObject(GameObject* parent, std::string name)
{
	GameObject* BakerHouse = new GameObject(parent, name);

}


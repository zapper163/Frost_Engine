#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "GameObject.h"

class Primitive;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	uint CreateGameObject(GameObject* parent, std::string name);
	//void Patata();

	static std::map<uint, GameObject*> gameObjects;

	GameObject* gameobject_selected = nullptr;

private:
	p2DynArray<Primitive*> primitives;
	
};

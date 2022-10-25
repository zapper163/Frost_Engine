#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"

#include <iostream>
#include <string>
#include <vector>

class GameObject;

class Component
{
public:
	enum class TYPE
	{
		NONE,
		TRANSFORM,
		MESH_RENDERER,
		MATERIAL,
		CAMERA,
		NUM_OF_COMPS,
	};


	Component(GameObject* game_object, TYPE type);
	virtual ~Component();
	
	TYPE GetType() { return type; }

	//virtual void Enable();

	//virtual void Update();

	//virtual void Disable();
	
	bool active;

	//GameObject owner;



private:
	TYPE type = TYPE::NONE;
	GameObject* go = nullptr;
};
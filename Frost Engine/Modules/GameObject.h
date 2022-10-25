#pragma once
#include "Globals.h"
#include "Application.h"
#include "Component.h"
#include "C_Transform.h"

#include <iostream>
#include <string>
#include <vector>

class GameObject
{
public:
	GameObject(GameObject* parent, std::string name = "Default");
	~GameObject();

	void Update();
	Component* CreateComponent(Component::TYPE);
	Component* GetComponent(Component::TYPE);

	bool AddChild(GameObject* child);

	C_Transform* transform = nullptr;

	bool active;
	string name;
	uint id = 0; 


	GameObject* parent;

	vector<Component*> components;
	
};
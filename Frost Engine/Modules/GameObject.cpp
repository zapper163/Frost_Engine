#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "C_Transform.h"
#include "C_Mesh.h"
#include "C_Texture.h"
#include "C_AudioListener.h"
#include "C_AudioSource.h"
#include "C_Camera.h"
#include "MeshLoader.h"

#include <iostream>
#include <string>
#include <vector>


GameObject::GameObject(GameObject* parent, std::string name)
{
	
	App->scene_intro->gameObjects[App->meshRender->id_count] = this;

	this->parent = parent;
	this->name = name;
	id = App->meshRender->id_count;
	App->meshRender->id_count++;
	transform = dynamic_cast<C_Transform*>(CreateComponent(Component::TYPE::TRANSFORM));

	if (parent != nullptr) parent->AddChild(this);
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i] != nullptr)
		{
			delete components[i];
			components[i] = nullptr;
		}
	}
	components.clear();
}

Component* GameObject::CreateComponent(Component::TYPE type)
{
	Component* new_component;
	switch (type)
	{
	case Component::TYPE::TRANSFORM:
		new_component = new C_Transform(this);
		break;
		
	case Component::TYPE::MESH:
		new_component = new C_Mesh(this);
		break;
	case Component::TYPE::TEXTURE:
		new_component = new C_Texture(this);
		break;
	case Component::TYPE::CAMERA:
		new_component = new C_Camera(this);
		break;
	case Component::TYPE::AUDIOLISTENER:
		new_component = new C_AudioListener(this);
		break;
	case Component::TYPE::AUDIOSOURCE:
		new_component = new C_AudioSource(this);
		break;
	default:
		LOG("component type error");
		break;
	}
	components.push_back(new_component);
	return new_component;
}

Component* GameObject::GetComponent(Component::TYPE type)
{
	for (auto component : components) // check all components
	{
		if (component->GetType() == type)
		{
			return component;
		}
	}
	return NULL; // component not find
}

vector <GameObject*> GameObject::GetChildren()
{
	
	return children; // component not find
}

GameObject* GameObject::GetChild(int n)
{

	return children[n]; 
}

bool GameObject::AddChild(GameObject* child)
{
	children.push_back(child);

	return true;
}

void GameObject::Update()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}
}

vector <Component*> GameObject::GetComponents()
{
	return components;
}

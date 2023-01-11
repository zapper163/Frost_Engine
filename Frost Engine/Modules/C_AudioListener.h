#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "MeshLoader.h"

#include <iostream>
#include <string>
#include <vector>



class C_AudioListener : public Component
{
public:
	C_AudioListener(GameObject* gameObject);
	~C_AudioListener();

	
	void OnGui();

	GameObject* ListenerGameObject;
	unsigned int listenerID;

	const char* name;
};
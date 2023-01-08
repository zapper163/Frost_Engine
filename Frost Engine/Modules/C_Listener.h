#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "MeshLoader.h"

#include <iostream>
#include <string>
#include <vector>



class C_Listener : public Component
{
public:
	C_Listener(GameObject* gameObject);
	~C_Listener();

	
	void OnGui();


	const char* name;
};
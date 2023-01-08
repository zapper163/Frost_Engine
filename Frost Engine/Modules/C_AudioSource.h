#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "MeshLoader.h"

#include <iostream>
#include <string>
#include <vector>



class C_AudioSource : public Component
{
public:
	C_AudioSource(GameObject* gameObject);
	~C_AudioSource();

	
	void OnGui();


	const char* name;
};
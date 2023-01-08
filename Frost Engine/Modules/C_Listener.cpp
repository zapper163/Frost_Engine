#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "C_Listener.h"

#include <iostream>
#include <string>
#include <vector>

C_Listener::C_Listener(GameObject* gameObject) : Component(gameObject, TYPE::TEXTURE)
{
	
}

C_Listener::~C_Listener()
{

}



void C_Listener::OnGui()
{

	if (ImGui::CollapsingHeader("Texture"))
	{
		ImGui::Text("Texture path:");
		ImGui::SameLine();
		ImGui::Text(name);

	}

}

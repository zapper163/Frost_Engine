#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "C_Texture.h"

#include <iostream>
#include <string>
#include <vector>

C_Texture::C_Texture(GameObject* gameObject) : Component(gameObject, TYPE::TEXTURE)
{
	
}

C_Texture::~C_Texture()
{

}

void C_Texture::SetTexture(const char* texture_name)
{

}


void C_Texture::OnGui()
{

	if (ImGui::CollapsingHeader("Texture"))
	{
		ImGui::Text("texture");
		ImGui::SameLine();

		ImGui::Text(name);
		ImGui::SameLine();

		//ImGui::Text(std::to_string().c_str());
		//ImGui::SameLine();

	}

}

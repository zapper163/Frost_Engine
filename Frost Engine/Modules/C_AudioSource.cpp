#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "C_AudioSource.h"

#include <iostream>
#include <string>
#include <vector>

C_AudioSource::C_AudioSource(GameObject* gameObject) : Component(gameObject, TYPE::TEXTURE)
{
	SourceGameObject = gameObject;
	sourceID = gameObject->id;
}

C_AudioSource::~C_AudioSource()
{

}



void C_AudioSource::OnGui()
{

	if (ImGui::CollapsingHeader("Texture"))
	{
		ImGui::Text("Texture path:");
		ImGui::SameLine();
		ImGui::Text(name);

	}

}

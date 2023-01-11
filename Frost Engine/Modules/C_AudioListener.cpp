#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "C_AudioListener.h"

#include <iostream>
#include <string>
#include <vector>

C_AudioListener::C_AudioListener(GameObject* gameObject) : Component(gameObject, TYPE::TEXTURE)
{
	ListenerGameObject = gameObject;
	listenerID = gameObject->id;

	App->audio->RegisterGameObject(listenerID);
	App->audio->SetDefaultListener(listenerID);
}

C_AudioListener::~C_AudioListener()
{
	App->audio->UnregisterGameObject(listenerID);
}

void C_AudioListener::Update()
{

}

void C_AudioListener::OnGui()
{

	if (ImGui::CollapsingHeader("Texture"))
	{
		ImGui::Text("Texture path:");
		ImGui::SameLine();
		ImGui::Text(name);

	}

}

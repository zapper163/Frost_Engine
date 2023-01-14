#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "C_AudioListener.h"

#include <iostream>
#include <string>
#include <vector>

C_AudioListener::C_AudioListener(GameObject* gameObject) : Component(gameObject, TYPE::AUDIOLISTENER)
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
	App->audio->SetListenerPos(ListenerGameObject, listenerID);

}

void C_AudioListener::OnGui()
{

	if (ImGui::CollapsingHeader("Audio Listener"))
	{
		ImGui::Text("AudioClip");
		ImGui::SameLine(ImGui::GetWindowWidth() * 0.65f);
		ImGui::Checkbox("##AudioClip", &activeListener);
		ImGui::SameLine();
		ImGui::Text("Listen");
	}

}

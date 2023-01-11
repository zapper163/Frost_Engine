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

	App->audio->RegisterGameObject(sourceID);
}

C_AudioSource::~C_AudioSource()
{
	App->audio->UnregisterGameObject(sourceID);
}


void C_AudioSource::PlayEvent(unsigned int index) const
{
	App->audio->PostEvent(eventsList[index], sourceID);

}

void C_AudioSource::StopEvent(unsigned int index) const
{
	App->audio->StopEvent(eventsList[index], sourceID);

}

void C_AudioSource::StopAllEvents() const
{
	for (int i = 0; i < eventsList.size(); ++i)
	{
		StopEvent(i);

	}
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

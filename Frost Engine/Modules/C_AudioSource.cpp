#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "C_AudioSource.h"

#include <iostream>
#include <string>
#include <vector>

C_AudioSource::C_AudioSource(GameObject* gameObject) : Component(gameObject, TYPE::AUDIOSOURCE)
{
	SourceGameObject = gameObject;
	sourceID = gameObject->id;

	events = App->audio->wwiseData.events;

	App->audio->RegisterGameObject(sourceID);

	audioClip = events[0];
	App->audio->PostEvent(audioClip.c_str(), sourceID);
	isPlaying = true;
}

C_AudioSource::~C_AudioSource()
{
	App->audio->UnregisterGameObject(sourceID);
}

void C_AudioSource::OnGui()
{
	
	if (ImGui::CollapsingHeader("Audio Source"))
	{
		ImGui::Text("AudioClip");
		ImGui::SameLine();
		if (ImGui::BeginCombo("##AudioClip", audioClip.c_str()))
		{
			if (ImGui::Selectable("None"))
			{
				audioClip = "None";
			}
			
			for (int i = 0; i < events.size(); i++)
			{
				if (ImGui::Selectable(events[i].c_str()))
				{
					audioClip = events[i];
				}
			}

			ImGui::EndCombo();
		}

		ImGui::Text("Volume");
		ImGui::SameLine();
		if (ImGui::SliderFloat("##Volume", &volume, 0.0f, 100.0f))
		{
			App->audio->SetRTPCValue("Volume", volume, sourceID);
		}
		if (ImGui::Button("Play"))
		{
			if (isPlaying == false)
			{
				App->audio->PostEvent(audioClip.c_str(), sourceID);
				isPlaying = true;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Pause"))
		{
			App->audio->PauseEvent(audioClip.c_str(), sourceID);
		}
		ImGui::SameLine();
		if (ImGui::Button("Resume"))
		{
			App->audio->ResumeEvent(audioClip.c_str(), sourceID);
		}
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
		{
			App->audio->StopEvent(audioClip.c_str(), sourceID);
			isPlaying = false;
		}

	}

	

}

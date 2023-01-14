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

	App->audio->RegisterGameObject(sourceID);
}

C_AudioSource::~C_AudioSource()
{
	App->audio->UnregisterGameObject(sourceID);
}


void C_AudioSource::PlayEvent(unsigned int index) const
{
	//App->audio->PostEvent(eventsList[index], sourceID);

}

void C_AudioSource::StopEvent(unsigned int index) const
{
	//App->audio->StopEvent(eventsList[index], sourceID);

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
			std::vector<std::string> events = App->audio->wwiseData.events;
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
			AK::SoundEngine::SetRTPCValue("Volume", volume, sourceID);
		}
		
		if (ImGui::Button("Play"))
		{
			App->audio->PostEvent(audioClip.c_str(), sourceID);
		}
		ImGui::SameLine();
		if (ImGui::Button("Pause"))
		{
			//PauseClip();
		}
		ImGui::SameLine();
		if (ImGui::Button("Resume"))
		{
			//ResumeClip();
		}
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
		{
			//StopClip();
		}

	}

}

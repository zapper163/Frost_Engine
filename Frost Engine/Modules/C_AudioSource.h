#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "MeshLoader.h"
#include "AudioEvent.h"

#include <iostream>
#include <string>
#include <vector>

class AudioEvent;

class C_AudioSource : public Component
{
public:
	C_AudioSource(GameObject* gameObject);
	~C_AudioSource();

	GameObject* SourceGameObject;
	uint sourceID;

	std::vector<std::string> events = App->audio->wwiseData.events;


	void OnGui();

	float volume;
	bool isPlaying = false;
	std::string audioClip;
};
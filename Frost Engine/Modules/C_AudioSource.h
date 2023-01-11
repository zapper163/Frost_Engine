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
	unsigned int sourceID;

	vector<AudioEvent*> eventsList;
	AudioEvent* emptyEvent = nullptr;

	void OnGui();

	void PlayEvent(unsigned int index) const;
	void StopEvent(unsigned int index) const;
	void StopAllEvents() const;

	const char* name;
};
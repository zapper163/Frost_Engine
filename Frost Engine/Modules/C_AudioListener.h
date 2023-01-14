#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "MeshLoader.h"
#include "Component.h"

#include <iostream>
#include <string>
#include <vector>


class TransformComponent;
class C_AudioListener : public Component
{
public:
	C_AudioListener(GameObject* gameObject);
	~C_AudioListener();

	void Update() override;

	void OnGui();

	bool activeListener;
	GameObject* ListenerGameObject;
	unsigned int listenerID;

	TransformComponent* transform;

};
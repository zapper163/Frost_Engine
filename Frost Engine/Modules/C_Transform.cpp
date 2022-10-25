#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "C_Transform.h"

#include <iostream>
#include <string>
#include <vector>

C_Transform::C_Transform(GameObject* gameObject) : Component(gameObject, TYPE::TRANSFORM)
{
	// If this is not the root node, we need the parents global transform.
	/*if (this->GetGameObject()->GetParent() != NULL)
	{
		C_Transform* parentTransform = dynamic_cast<C_Transform*>(gameObject->GetParent()->GetComponent(Component::TYPE::TRANSFORM));
		parentGlobalTransform = parentTransform->GetGlobalTransform();
	}*/
}

C_Transform::~C_Transform()
{

}
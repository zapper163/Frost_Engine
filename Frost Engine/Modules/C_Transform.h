#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"

#include "External_Libraries/MathGeoLib/include/MathGeoLib.h"


#include <iostream>
#include <string>
#include <vector>

struct Transform
{
	float3 position;

	float3 rotation;

	float3 scale;
};

class C_Transform : public Component
{
public:
	C_Transform(GameObject* gameObject);
	~C_Transform();

	void SetTransform(float3 position, float3 rotation, float3 scale);

	void OnGui();

	Transform transform;
};


#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "MeshLoader.h"

#include <iostream>
#include <string>
#include <vector>



class C_Camera : public Component
{
public:
	C_Camera(GameObject* gameObject);
	~C_Camera();

	void Update();

	void OnGui();

	void Move(const float3& Movement);


	void InitFrameBuffer();
	void RefreshBuffer();
	void ResizeBuffer(int width, int height);


	Frustum frustum;
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
	float3 reference;

	vec3 X, Y, Z, Position, Reference;

	float nearPlaneDistance = 0.1f;
	float farPlaneDistance = 500.f;

	unsigned int textureColorbuffer_mini;
	unsigned int framebuffer_mini;
	unsigned int renderbuffer_mini;

	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;
};
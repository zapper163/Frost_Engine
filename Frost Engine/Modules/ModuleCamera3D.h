#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt) override;
	bool CleanUp();

	void Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference = false);
	void LookAt(const float3&Spot);
	void Move(const float3&Movement);
	float* GetOpenGLViewMatrix();

	

private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;

	Frustum frustum;
	float4x4 viewMatrix;
	float4x4 projectionMatrix;
	float3 reference;

};
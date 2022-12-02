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

	transform.globalPos.SetIdentity();
	transform.localPos.SetIdentity();
	transform.transGlobalPos.SetIdentity();

	transform.localPos.Decompose(transform.position, transform.quatRotation, transform.scale);
	transform.quatRotation.Normalize();

	transform.eulRotation = transform.quatRotation.ToEulerXYZ();

	transform.transGlobalPos = transform.globalPos.Transposed();

	
}

C_Transform::~C_Transform()
{

}

void C_Transform::SetTransform(float3 position, Quat rotation, float3 scale)
{
	
	transform.position = position;

	transform.rotation = rotation.Normalized();

	transform.scale = scale;

	transform.eulRotation = transform.quatRotation.ToEulerXYZ() * RADTODEG;

	transform.localPos = float4x4::FromTRS(transform.position, transform.quatRotation, transform.scale);
	
	if (this->go->parent != nullptr)
	{
		if (this->go->parent->transform != nullptr)
		{
			transform.globalPos = go->parent->transform->transform.globalPos * transform.localPos;
		}
	}
	transform.transGlobalPos = transform.globalPos.Transposed();
}

void C_Transform::Update()
{
	// ---------------------------------------------------------------------------------------------------------------------------- Define rotation (QUAT from EULER)
	transform.quatRotation = Quat::FromEulerXYZ(transform.eulRotation.x * DEGTORAD, transform.eulRotation.y * DEGTORAD, transform.eulRotation.z * DEGTORAD);
	transform.quatRotation.Normalize();

	// -------------------------------------------------------------------------------------------------------------- Define the Local Position
	transform.localPos = float4x4::FromTRS(transform.position, transform.quatRotation, transform.scale);

	

	if (this->go->id > 1)
	{
		if (this->go->parent != nullptr)
		{
			if (this->go->parent->transform != nullptr)
			{
				// We apply the posicion formula
				this->transform.globalPos = this->go->parent->transform->transform.globalPos * this->transform.localPos;
				this->transform.transGlobalPos = this->transform.globalPos.Transposed();
			}
		}
	}


}

float4x4 C_Transform::GetGlobalTransposed()
{
	return transform.transGlobalPos;
}


void C_Transform::OnGui()
{
	
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Position: ");
		ImGui::SameLine();
		ImGui::DragFloat3("##Pos", &transform.position[0], 0.1f);

		ImGui::Text("Rotation: ");
		ImGui::SameLine();
		ImGui::DragFloat3("##Rot", &transform.eulRotation[0], 0.1f);

		ImGui::Text("Scale:");
		ImGui::SameLine();
		ImGui::DragFloat3("##Sca", &transform.scale[0], 0.1f);
	}
}
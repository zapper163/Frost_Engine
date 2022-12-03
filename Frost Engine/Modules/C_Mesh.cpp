#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "C_Mesh.h"

#include <iostream>
#include <string>
#include <vector>

C_Mesh::C_Mesh(GameObject* gameObject) : Component(gameObject, TYPE::MESH)
{
	
}

C_Mesh::~C_Mesh()
{

}

void C_Mesh::SetMesh(MeshInfo* mesh,std::string mesh_name) 
{
	this->mesh = mesh;
	name = mesh_name;
}

void C_Mesh::OnGui()
{

	if (ImGui::CollapsingHeader("Mesh"))
	{
		ImGui::Text("Mesh Name:");
		ImGui::SameLine();

		ImGui::Text(name.c_str());

	}

}

void C_Mesh::Update()
{
	if (CheckInFrustrum())
	{
		mesh->RenderMesh(go->transform->GetGlobalTransposed(), mesh->texture_id);
	}
	
}

bool C_Mesh::CheckInFrustrum()
{
	float3 vCorner[8];
	mesh->globalAABB.GetCornerPoints(vCorner); // get the corners of the box into the vCorner array
	// test all 8 corners against the 6 sides
	// if all points are behind 1 specific plane, we are out
	// if we are in with all points, then we are fully in
	for (int p = 0; p < 6; ++p) {
		int iInCount = 8;
		int iPtIn = 1;
		for (int i = 0; i < 8; ++i) {
			// test this point against the planes
			if (App->camera->frustum.GetPlane(p).IsOnPositiveSide(vCorner[i])) { //<-- “IsOnPositiveSide” from MathGeoLib
				iPtIn = 0;
				--iInCount;
			}
		}
		// were all the points outside of plane p?
		if(iInCount == 0)
			return false;
	}
	
	return true;
}
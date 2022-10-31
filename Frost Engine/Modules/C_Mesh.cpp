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

void C_Mesh::SetMesh(MeshInfo* mesh, const char* mesh_name) 
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

		ImGui::Text(name);
		ImGui::SameLine();

		//ImGui::Text(std::to_string().c_str());
		ImGui::SameLine();

	}

}

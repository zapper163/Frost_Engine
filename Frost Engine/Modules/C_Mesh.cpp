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

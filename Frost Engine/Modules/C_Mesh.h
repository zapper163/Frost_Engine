#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "MeshLoader.h"

#include <iostream>
#include <string>
#include <vector>



class C_Mesh : public Component
{
public:
	C_Mesh(GameObject* gameObject);
	~C_Mesh();

	void SetMesh(MeshInfo* mesh, std::string mesh_name);

	void OnGui();

	void Update();

	bool CheckInFrustrum();

	MeshInfo* GetMesh()
	{
		return mesh;
	}

	std::string name;
	MeshInfo* mesh;
};
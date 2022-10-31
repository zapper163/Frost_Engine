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

	void SetMesh(MeshInfo* mesh, const char* mesh_name);

	void OnGui();


	const char* name;
	MeshInfo* mesh;
};
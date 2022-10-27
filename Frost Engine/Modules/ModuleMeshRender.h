#pragma once
#include "Module.h"
#include "Globals.h"
#include "MeshLoader.h"
#include "TextureLoader.h"

class ModuleMeshRender : public Module
{
public:
	
	ModuleMeshRender(bool start_enabled = true);
	~ModuleMeshRender();

	bool Init();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	bool CleanUp();

	
	const char* tex = "Assets/Baker_house.png";

	const char* filepath = "Assets/BakerHouse.fbx";
	MeshInfo houseMesh;

private:
	
};
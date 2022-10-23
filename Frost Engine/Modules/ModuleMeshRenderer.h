#pragma once
#include "Module.h"
#include "Globals.h"
#include "MeshLoader.h"
#include "TextureLoader.h"


using namespace std;

struct Mesh
{

	Mesh() {}

	~Mesh() {
		delete[num_vertex]  vertex;
		delete[num_index]  index;

	}
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	float* texture_vertex = nullptr;

	int id_vertex = 0; // index in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	uint num_uvs;
	float* uvs = nullptr;
	//unsigned int VAO, VBO, EBO;


	//void SetUpMesh();
	void RenderMesh(uint texture_ID);
};



class ModuleMeshRenderer : public Module
{
public:
	
	uint texture_ID;

	ModuleMeshRenderer(bool start_enabled = true);
	~ModuleMeshRenderer();

	bool Init();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	static void LoadFile(const char* file_path);
	static void LoadBuffers(MeshInfo* ourMesh);

	
private:
	static vector<MeshInfo*> meshList;
};
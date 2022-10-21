#pragma once
#include "Globals.h"

#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include <vector>


using namespace std;

struct MeshInfo
{

	MeshInfo() {}

	~MeshInfo() {
		delete[num_vertex]  vertex;
		delete[num_index]  index;

	}

	uint num_index = 0;
	uint* index = nullptr;

	float* texture_vertex = nullptr;

	uint num_vertex = 0;
	float* vertex = nullptr;

	uint num_uvs;
	float* uvs = nullptr;
	//unsigned int VAO, VBO, EBO;

	//void SetUpMesh();
	void RenderMesh();
 };

class MeshLoader
{
public:
	void DebugMode();
	static void LoadFile(const char* file_path, MeshInfo* ourMesh);

	static void Render();
	void CleanUp();
	
	static vector<MeshInfo*> meshList;
};
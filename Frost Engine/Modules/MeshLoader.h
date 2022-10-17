#pragma once
#include "Globals.h"

#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>


using namespace std;

class MeshInfo
{
public:
	MeshInfo() {}

	~MeshInfo() {
		delete[num_vertex]  vertex;
		delete[num_index]  index;

	}

	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	void RenderMesh();



private:

 };

class MeshLoader
{
public:
	void DebugMode();
	static void LoadMesh(const char* file_path, MeshInfo* ourMesh);

	static void Render();
	void CleanUp();

	
	static vector<MeshInfo*> meshList;
};
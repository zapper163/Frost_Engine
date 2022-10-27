#pragma once
#include "Globals.h"

#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include <vector>


using namespace std;

#define VERTEX_FEATURES 5

struct MeshInfo
{

	MeshInfo() {}

	~MeshInfo() {
		delete[num_vertex]  vertex;
		delete[num_index]  index;

	}

	uint id_vertex = 0;
	uint num_index = 0;
	uint* index = nullptr;

	float* texture_vertex = nullptr;
	GLuint texture_id;

	uint id_index = 0;
	uint num_vertex = 0;
	float* vertex = nullptr;
	
	const char* tex = "Assets/Baker_house.png";

	void RenderMesh();
 };

class MeshLoader
{
public:
	void DebugMode();
	static void LoadFile(const char* file_path, MeshInfo* ourMesh);

	static void Render();
	static void CleanUp();

	static void SetUpMesh(MeshInfo* ourMesh);
	
	static vector<MeshInfo*> meshList;

	
};
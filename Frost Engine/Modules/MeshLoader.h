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

	uint id_vertex = 0;
	uint num_index = 0;
	uint* index = nullptr;

	float* texture_vertex = nullptr;
	GLuint texture_id;

	uint id_index = 0;
	uint num_vertex = 0;
	float* vertex = nullptr;

	uint num_uvs;
	float* uvs = nullptr;
	//unsigned int VAO, VBO, EBO;

	const char* tex = "/Assets/Baker_house.png";


	static void SetUpMesh(MeshInfo* ourMesh);
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
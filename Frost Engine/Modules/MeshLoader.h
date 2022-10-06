#pragma once
#include "Globals.h"

#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>


class aiMesh;

struct MeshData
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
 };

namespace MeshLoader 
{
	void DebugMode();
	void LoadFile(const char* file_path, MeshData* ourMesh);
	void CreateMeshBuffer(MeshData ourMesh);
	void RenderMesh(MeshData ourMesh);
	void CleanUp();
}
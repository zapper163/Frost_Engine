#pragma once
#include "Globals.h"

#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include "External_Libraries/MathGeoLib/include/MathGeoLib.h"

#include <vector>
#include <string>


using namespace std;

#define VERTEX_FEATURES 5

class GameObject;

struct MeshInfo
{

	MeshInfo() {
		vertex = nullptr;
		num_vertex = 0;

	}

	~MeshInfo() {

		delete vertex;
		vertex = nullptr;

		delete index;
		index = nullptr;
	}

	

	uint id_vertex = 0;
	uint num_index = 0;
	uint* index = nullptr;

	float* texture_vertex = nullptr;
	GLuint texture_id = 0;

	uint id_index = 0;
	static uint num_vertex;
	static float* vertex;
	
	const char* tex = "Assets/building 06_ c.tga";

	const char* mesh_name = "Default";

	static AABB AABB_box;
	
	OBB OBB_box;
	AABB Global_AABB_box;

	static void InitAABB();

	void RenderMesh(const GLfloat* globalTransform);
 };

class MeshLoader
{
public:
	void DebugMode();

	static const char* GetMeshName(const char* mesh_name);

	static void LoadFile(const char* file_path);

	static void Render();
	static void CleanUp();

	static void SetUpMesh(MeshInfo* ourMesh);

	static void GetNodeInfo(const aiScene* rootScene, aiNode* rootNode, GameObject* GameObgectFather);
	
	float* transGlobalPos;

	static vector<MeshInfo*> meshList;

	
};
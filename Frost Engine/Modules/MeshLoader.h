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


using namespace std;

#define VERTEX_FEATURES 5

class GameObject;

struct MeshInfo
{

	MeshInfo() {}

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
	GLuint texture_id;

	uint id_index = 0;
	uint num_vertex = 0;
	float* vertex = nullptr;
	
	const char* tex = "Assets/building 06_ c.png";

	const char* mesh_name;


	bool localAABB_init = false;
	AABB localAABB;
	AABB globalAABB;
	OBB globalOBB;

	uint ID;

	void GenerateGlobalBoundingBox();
	void GenerateLocalBoundingBox();

	void RenderMesh(const GLfloat* globalTransform, uint texID);
	void RenderAABB();
 };

class MeshLoader
{
public:
	void DebugMode();

	static const char* GetMeshName(const char* mesh_name);

	static void LoadFile(const char* file_path);

	
	static void CleanUp();

	static void SetUpMesh(MeshInfo* ourMesh);

	static void GetNodeInfo(const aiScene* rootScene, aiNode* rootNode, GameObject* GameObgectFather);
	
	float* transGlobalPos;

	static vector<MeshInfo*> meshList;

	
};
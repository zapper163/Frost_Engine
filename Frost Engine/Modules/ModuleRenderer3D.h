#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "MeshLoader.h"
#include "TextureLoader.h"


#define MAX_LIGHTS 8

#define IMAGE_ROWS 64      // Texture image rows and columns
#define IMAGE_COLS 64

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
    bool Start();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();


    void InitFrameBuffer();
    void RefreshBuffer();
    void ResizeBuffer(int width,int height);

   

	void OnResize(int width, int height);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

    unsigned int textureColorbuffer;
    unsigned int framebuffer;
    unsigned int renderbuffer;

    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;

  /*  bool wireframe = false;
    bool lights_active = true;
    bool depth_test_active = true;
    bool cull_face_active = true;*/

    

    float x = 0;
    float y = 0;
    float z = 0;
};





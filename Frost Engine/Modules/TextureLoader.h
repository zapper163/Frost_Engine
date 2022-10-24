#pragma once
#include "Globals.h"
#include "Application.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class TextureLoader
{
public:
	
	static GLuint LoadTextureFromFile(const char* path);

	
	//static bool RenderTexture();

	void CleanUp();
};
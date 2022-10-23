#pragma once
#include "Globals.h"

#include <iostream>
#include <string>
#include <vector>


#define IMAGE_ROWS 64      // Texture image rows and columns
#define IMAGE_COLS 64


using namespace std;

class TextureLoader
{
public:

	// Texture
	static GLubyte imageData[IMAGE_ROWS][IMAGE_COLS][3]; // Texture image data

	static GLuint textureID;
	
	static bool LoadTextureFromFile(const char* path);
	static uint CheckerTexture();
	//static bool RenderTexture();

	void CleanUp();
};
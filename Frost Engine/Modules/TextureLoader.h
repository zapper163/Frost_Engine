#pragma once
#include "Globals.h"
#include "Application.h"

#include "DevIL/include/il.h"
#include "DevIL/include/ilut.h"

#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment (lib, "DevIL/libx86/ILU.lib" )
#pragma comment (lib, "DevIL/libx86/ILUT.lib" )

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
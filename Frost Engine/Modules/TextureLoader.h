#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"


#include "DevIL/include/il.h"
#include "DevIL/include/ilut.h"

#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment (lib, "DevIL/libx86/ILU.lib" )
#pragma comment (lib, "DevIL/libx86/ILUT.lib" )

#include <iostream>
#include <string>
#include <map>

using namespace std;

class TextureLoader
{
public:
	
	const char path;

	static GLuint LoadTextureFromFile(const char* path);

	static std::map<std::string, uint> loaded_textures;

	void CleanUp();
};
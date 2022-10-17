#pragma once
#include "Globals.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;

struct Texture {
	ILuint ID = 0;
	string name;
};

class TextureLoader
{
public:
	
	static uint LoadTextureFromFile(std::string path);
	static bool RenderTexture();

	void CleanUp();
};
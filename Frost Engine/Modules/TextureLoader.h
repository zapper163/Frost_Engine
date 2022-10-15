#pragma once
#include "Globals.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class TextureLoader
{
public:
	
	static bool loadTextureFromFile(std::string path);

	void CleanUp();
};
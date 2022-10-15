
#include "TextureLoader.h"

#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "DevIL/include/il.h"
#include "DevIL/include/ilut.h"

#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment (lib, "DevIL/libx86/ILU.lib" )
#pragma comment (lib, "DevIL/libx86/ILUT.lib" )

bool TextureLoader::loadTextureFromFile(std::string path)
{
    //Texture loading success
    bool textureLoaded = false;

    //Generate and set current image ID
    ILuint imgID = 0;
    ilGenImages(1, &imgID);
    ilBindImage(imgID);
   
    //Load image
    ILboolean success = ilLoadImage(path.c_str());

    //Image loaded successfully
    if (success == IL_TRUE)
    {
        textureLoaded = true;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        imgID = ilutGLBindTexImage();
        glBindTexture(GL_TEXTURE_2D, 0);

        //Delete file from memory
        ilDeleteImages(1, &imgID);
    }

    
    //Report error
    if (!textureLoaded)
    {
        LOG("Unable to load %s\n", path.c_str());
    }

    return textureLoaded;
}


void TextureLoader::CleanUp()
{

}
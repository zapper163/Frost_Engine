
#include "TextureLoader.h"
#include "Application.h"

#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "DevIL/include/il.h"
#include "DevIL/include/ilut.h"

#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment (lib, "DevIL/libx86/ILU.lib" )
#pragma comment (lib, "DevIL/libx86/ILUT.lib" )

GLuint TextureLoader::LoadTextureFromFile(const char* path)
{
    ilInit();
    iluInit();
    ilutInit();

    // -------------------------------------- Loading Image
    if (ilLoadImage(path))
    {
        ILuint imageID;
        ilGenImages(1, &imageID);
        ilBindImage(imageID);
        
        ilLoadImage(path);

        BYTE* data = ilGetData();
        
        int const width = ilGetInteger(IL_IMAGE_WIDTH);
        int const height = ilGetInteger(IL_IMAGE_HEIGHT);
        int const type = ilGetInteger(IL_IMAGE_TYPE); // matches OpenGL
        int const format = ilGetInteger(IL_IMAGE_FORMAT); // matches OpenGL

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); // rows are tightly packed
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // pixels are tightly packed

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        return textureID;
    }
    else
    {
        //App->menus->info.AddConsoleLog(FILE, LINE, "DevIL ERROR: Could not Load Image. Error: %s", ilGetError());

        return 0;
    }
}


void TextureLoader::CleanUp()
{

}

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

bool TextureLoader::LoadTextureFromFile(const char* path)
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

uint TextureLoader::CheckerTexture()
{
    int value;
    for (int row = 0; row < IMAGE_ROWS; row++) {
        for (int col = 0; col < IMAGE_COLS; col++) {
            // Each cell is 8x8, value is 0 or 255 (black or white)
            value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
            imageData[row][col][0] = (GLubyte)value;
            imageData[row][col][1] = (GLubyte)value;
            imageData[row][col][2] = (GLubyte)value;
        }
    }

    //Generate and bind texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //How texture behaves outside 0,1 range (S->x, T->y)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_CLAMP
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Texture behaviour after resize (MIN->smaller , MAG->bigger)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //Create Texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, IMAGE_ROWS, IMAGE_COLS,
        0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    //unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}


void TextureLoader::CleanUp()
{

}

#include "TextureLoader.h"
#include "Application.h"
#include "ModuleEditorGui.h"

#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>



GLuint TextureLoader::LoadTextureFromFile(const char* path)
{
    ilInit();
    iluInit();
    ilutInit();

    // -------------------------------------- Loading Image
    if (ilLoadImage(path))
    {
		ilEnable(IL_FILE_OVERWRITE);
		ilSaveImage(path);

		ILuint ImgId = 0;
		ilGenImages(1, &ImgId);
		ilBindImage(ImgId);

		ilLoadImage(path);
		/////
		BYTE* data = ilGetData();

		ILuint imgWidth, imgHeight;
		imgWidth = ilGetInteger(IL_IMAGE_WIDTH);
		imgHeight = ilGetInteger(IL_IMAGE_HEIGHT);
		int const type = ilGetInteger(IL_IMAGE_TYPE);
		int const format = ilGetInteger(IL_IMAGE_FORMAT);

		ImgId = ilutGLBindTexImage();

		ilBindImage(0);
		ilDeleteImages(1, &ImgId);

		//info.LOGC("TEX ID: %d", ImgId);

		return ImgId;
    }
    else
    {
       //App->editorGui->console.AddLog(__FILE__, __LINE__, "DevIL ERROR: Could not Load Image. Error: %s", ilGetError());
        LOG("DevIL ERROR : Could not Load Image.Error : ");
        return 0;
    }
}


void TextureLoader::CleanUp()
{

}
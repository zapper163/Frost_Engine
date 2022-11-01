
#include "TextureLoader.h"
#include "Application.h"
#include "ModuleEditorGui.h"
#include "C_Texture.h"


#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

std::map<std::string, uint> TextureLoader::loaded_textures;

GLuint TextureLoader::LoadTextureFromFile(const char* path)
{
	/*for (size_t i = 0; i < App->scene_intro->gameObjects.size(); i++)
	{
		dynamic_cast<C_Texture*>(App->scene_intro->gameObjects[i]->CreateComponent(Component::TYPE::TEXTURE))->SetTexture(path); 

	}*/
	

	if (loaded_textures.find(path) != loaded_textures.end())
	{
		return loaded_textures[path];
	}

    if (ilLoadImage(path))
    {
		ilEnable(IL_FILE_OVERWRITE);
		ilSaveImage(path);

		ILuint ImgId = 0;
		ilGenImages(1, &ImgId);
		ilBindImage(ImgId);

		ilLoadImage(path);
		
		ImgId = ilutGLBindTexImage();
		
		ilBindImage(0);
		ilDeleteImages(1, &ImgId);
		
		loaded_textures[path] = ImgId;

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
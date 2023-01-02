#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "MeshLoader.h"
#include "TextureLoader.h"
#include "GameObject.h"
#include "C_Camera.h"



#include <iostream>
#include <filesystem>




ModuleAudio::ModuleAudio(bool start_enabled) : Module(start_enabled)
{

}

// Destructor
ModuleAudio::~ModuleAudio()
{
}

// Called before render is available
bool ModuleAudio::Init()
{
	bool ret = true;


	return ret;
}

bool ModuleAudio::Start()
{
	
	return true;
}

// Called every draw update
update_status ModuleAudio::PreUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}

update_status ModuleAudio::Update(float dt)
{
	
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	
	return true;
}

bool ModuleAudio::InitSoundEngine()
{
    //--------------------------------------------------------------------------------------------------------------------
	//Memory Manager
    AkMemSettings memSettings;
	AK::MemoryMgr::GetDefaultSettings(memSettings);

	if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
	{
		assert(!"Could not create the memory manager.");
		return false;
	}



    //----------------------------------------------------------------------------------------------------------------------------------
    //Streaming Manager
    
    // Create and initialize an instance of the default streaming manager. Note
    // that you can override the default streaming manager with your own. 
    
    AkStreamMgrSettings stmSettings;
    AK::StreamMgr::GetDefaultSettings(stmSettings);

    // Customize the Stream Manager settings here.


    if (!AK::StreamMgr::Create(stmSettings))
    {
        assert(!"Could not create the Streaming Manager");
        return false;
    }

   
    // Create a streaming device with blocking low-level I/O handshaking.
    // Note that you can override the default low-level I/O module with your own. 


    AkDeviceSettings deviceSettings;
    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

    // Customize the streaming device settings here.


    // CAkFilePackageLowLevelIOBlocking::Init() creates a streaming device
    // in the Stream Manager, and registers itself as the File Location Resolver.
    /*if (g_lowLevelIO.Init(deviceSettings) != AK_Success)
    {
        assert(!"Could not create the streaming device and Low-Level I/O system");
        return false;
    }*/


    //----------------------------------------------------------------------------------------------------------------------------------
    //Sound Engine

    // Create the Sound Engine
    // Using default initialization parameters


    AkInitSettings initSettings;
    AkPlatformInitSettings platformInitSettings;
    AK::SoundEngine::GetDefaultInitSettings(initSettings);
    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

    if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
    {
        assert(!"Could not initialize the Sound Engine.");
        return false;
    }

	return true;
}

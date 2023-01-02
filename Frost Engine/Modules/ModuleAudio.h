#pragma once
#include "Module.h"
#include "Globals.h"


#include <Wwise/include/AK/SoundEngine/Common/AkMemoryMgr.h>                  // Memory Manager interface

#include <Wwise/include/AK/SoundEngine/Common/AkModule.h>                     // Default memory manager


#include <Wwise/include/AK/SoundEngine/Common/AkStreamMgrModule.h>             // Streaming Manager

#include <Wwise/include/AK/Tools/Common/AkPlatformFuncs.h>                      // Thread defines


#include <Wwise/include/AK/SoundEngine/Common/AkSoundEngine.h>	                // SoundEngine

#include <Wwise/include/AK/MusicEngine/Common/AkMusicEngine.h>	                // MusicEngine


//#include <Wwise/include/AkFilePackageLowLevelIOBlocking.h>                    // Sample low-level I/O implementation


// We're using the default Low-Level I/O implementation that's part
// of the SDK's sample code, with the file package extension
//CAkFilePackageLowLevelIOBlocking g_lowLevelIO;


class ModuleAudio : public Module
{
public:
	
    ModuleAudio(bool start_enabled = true);
	~ModuleAudio();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	bool CleanUp();

	bool InitSoundEngine();
    
    

private:
    
};


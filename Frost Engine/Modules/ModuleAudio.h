#pragma once
#include "Module.h"
#include "Globals.h"


#include <Wwise/include/AK/SoundEngine/Common/AkMemoryMgr.h>                  // Memory Manager interface

#include <Wwise/include/AK/SoundEngine/Common/AkModule.h>                     // Default memory manager


#include <Wwise/include/AK/SoundEngine/Common/AkStreamMgrModule.h>             // Streaming Manager

#include <Wwise/include/AK/Tools/Common/AkPlatformFuncs.h>                      // Thread defines


#include <Wwise/include/AK/SoundEngine/Common/AkSoundEngine.h>	                // SoundEngine

#include <Wwise/include/AK/MusicEngine/Common/AkMusicEngine.h>	                // MusicEngine


#ifdef _DEBUG
// Input libraries
#pragma comment( lib, "Wwise/Debug(StaticCRT)/lib/AkSoundEngine.lib")
#pragma comment( lib, "Wwise/Debug(StaticCRT)/lib/AkMusicEngine.lib")
#pragma comment( lib, "Wwise/Debug(StaticCRT)/lib/AkMemoryMgr.lib")
#pragma comment( lib, "Wwise/Debug(StaticCRT)/lib/AkStreamMgr.lib")

// External library dependencies
#pragma comment( lib, "Wwise/dinput8.lib") // Microsoft DirectX DirectInput.Needed by Motion to support DirectInput devices.
#pragma comment( lib, "Wwise/dsound.lib")  // Microsoft DirectX DirectSound library
#pragma comment( lib, "Wwise/dxguid.lib")  // Microsoft DirectX Audio GUIDs
#pragma comment( lib, "Wwise/WinMM.Lib")  // Microsoft Multimedia API. Needed by Motion for internal device targeting management. 
#pragma comment( lib, "Wwise/WS2_32.Lib")  // Microsoft Winsock 2 library (used for Wwise profiling) 
#pragma comment( lib, "Wwise/XInput.lib")  // Microsoft XInput. Needed by Motion to support XInput devices (Xbox controller).
#else
#define AK_OPTIMIZED
// Input libraries
#pragma comment( lib, "Wwise/Release(StaticCRT)/lib/AkMusicEngine.lib")
#pragma comment( lib, "Wwise/Release(StaticCRT)/lib/AkMemoryMgr.lib")
#pragma comment( lib, "Wwise/Release(StaticCRT)/lib/AkStreamMgr.lib")
#pragma comment( lib, "Wwise/Release(StaticCRT)/lib/AkSoundEngine.lib")

// External library dependencies
#pragma comment( lib, "Wwise/dinput8.lib") // Microsoft DirectX DirectInput.Needed by Motion to support DirectInput devices.
#pragma comment( lib, "Wwise/dsound.lib")  // Microsoft DirectX DirectSound library
#pragma comment( lib, "Wwise/dxguid.lib")  // Microsoft DirectX Audio GUIDs
#pragma comment( lib, "Wwise/WinMM.Lib")  // Microsoft Multimedia API. Needed by Motion for internal device targeting management. 
//#pragma comment( lib, "Wwise/WS2_32.Lib")  // Microsoft Winsock 2 library (used for Wwise profiling) 
#pragma comment( lib, "Wwise/XInput.lib")  // Microsoft XInput. Needed by Motion to support XInput devices (Xbox controller).
#endif

//#include <Wwise/include/AkFilePackageLowLevelIOBlocking.h>                    // Sample low-level I/O implementation

// Include for communication between Wwise and the game -- Not needed in the release version
#ifndef AK_OPTIMIZED
#include <AK/Comm/AkCommunication.h>
#endif // AK_OPTIMIZED

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


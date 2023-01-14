#pragma once

#include "Module.h"
#include "Globals.h"
#include "AudioEvent.h"


#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/AkModule.h>

#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>  

#include <AK/SoundEngine/Common/AkSoundEngine.h>

//#include <AK/MusicEngine/Common/AkMusicEngine.h>
#include <AK/SpatialAudio/Common/AkSpatialAudio.h>

#include <AK/SoundEngine/Common/IAkPlugin.h>
//#include <AK/Plugin/AkRoomVerbFXFactory.h>

#include <AK/SoundEngine/Win32/AkFilePackageLowLevelIOBlocking.h>

#ifndef AK_OPTIMIZED
#include <AK/Comm/AkCommunication.h>
#endif



#define MAX_LISTENERS 1

class AudioEvent;


struct WwiseData
{
	std::vector<std::string> events;
	std::vector<std::string> banks;
};

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

	void ProcessAudio();

	void RegisterGameObject(unsigned int id);
	void UnregisterGameObject(unsigned int id);

	
	void PostEvent(AudioEvent* event, unsigned int id);
	void StopEvent(const AudioEvent* event, unsigned int id);


	void SetDefaultListener(const AkGameObjectID id);
	void AddListeners(unsigned int emitter_id, const AkGameObjectID listener_id);
	void SetListenerPos(GameObject* listener, unsigned int id);

	void GetAudioInfo();

private:
	CAkFilePackageLowLevelIOBlocking g_lowLevelIO;
	WwiseData wwiseData;
};


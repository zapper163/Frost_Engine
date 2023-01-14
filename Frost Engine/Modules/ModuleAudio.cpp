#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "MeshLoader.h"
#include "TextureLoader.h"
#include "GameObject.h"
#include "C_Camera.h"

#include <string>

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
    InitSoundEngine();

    
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
    ProcessAudio();

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
    LOG("Destroying 3D Renderer");
    App->editorGui->console.AddLog(__FILE__, __LINE__, "Destroying Module Audio");
   

    //AK::MusicEngine::Term();
    AK::SoundEngine::Term();

    if (AK::IAkStreamMgr::Get())
        AK::IAkStreamMgr::Get()->Destroy();

    //AK::MemoryMgr::Term();// --------------------------------------->Esto Crashea al cerrar
    
	return true;
}

bool ModuleAudio::InitSoundEngine()
{
	AkMemSettings memSettings;
	AK::MemoryMgr::GetDefaultSettings(memSettings);

	if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
	{
		LOG("Couldn't create the Memory Manager");
		return false;
	}

	AkStreamMgrSettings streamSettings;
	AK::StreamMgr::GetDefaultSettings(streamSettings);

	if (!AK::StreamMgr::Create(streamSettings))
	{
		LOG("Couldn't create the Stream Manager");
		return false;
	}

	AkDeviceSettings devSettings;
	AK::StreamMgr::GetDefaultDeviceSettings(devSettings);

	if (g_lowLevelIO.Init(devSettings) != AK_Success)
	{
		LOG("Couldn't create the streaming device and Low-Level I/O system");
		return false;
	}

	AkInitSettings initSettings;
	AkPlatformInitSettings platfInitSettings;
	AK::SoundEngine::GetDefaultInitSettings(initSettings);
	AK::SoundEngine::GetDefaultPlatformInitSettings(platfInitSettings);

	if (AK::SoundEngine::Init(&initSettings, &platfInitSettings) != AK_Success)
	{
		LOG("Couldn't initialize the sound engine");
		return false;
	}

	AkSpatialAudioInitSettings spatialSettings;

	if (AK::SpatialAudio::Init(spatialSettings) != AK_Success)
	{
		LOG("Couldn't initialize the spatial audio");
		return false;
	}


	GetAudioInfo();

	g_lowLevelIO.SetBasePath(AKTEXT("Assets/Wwise/"));

	AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(US)"));

	AkBankID bankID = 0;
	if (AK::SoundEngine::LoadBank(L"Init.bnk", bankID) != AK_Success)
	{
		LOG("Couldn't find the bank: Init.bnk");
		return false;
	}
	if (AK::SoundEngine::LoadBank(L"Main.bnk", bankID) != AK_Success)
	{
		LOG("Couldn't find the bank: Main.bnk");
		return false;
	}
	

	return true;
}

void ModuleAudio::ProcessAudio()
{
    // Process bank requests, events, positions, RTPC, etc.
    AK::SoundEngine::RenderAudio();
}


void ModuleAudio::RegisterGameObject(unsigned int id)
{
    AK::SoundEngine::RegisterGameObj(id);

}

void ModuleAudio::UnregisterGameObject(unsigned int id)
{
    AK::SoundEngine::UnregisterGameObj(id);
}

void ModuleAudio::SetDefaultListener(const AkGameObjectID id)
{
    AK::SoundEngine::SetDefaultListeners(&id, MAX_LISTENERS);
}

void ModuleAudio::AddListeners(unsigned int emitter_id, const AkGameObjectID listener_id)
{
    AK::SoundEngine::SetListeners(emitter_id, &listener_id, MAX_LISTENERS);
}


void ModuleAudio::SetListenerPos(GameObject* listener, unsigned int id)
{
    //Orientation
    AkVector front;
    front.X = listener->transform->GetVectorFront().x;
    front.Y = listener->transform->GetVectorFront().y;
    front.Z = listener->transform->GetVectorFront().z;

    //Top orientation
    AkVector top;
    top.X = listener->transform->GetVectorTop().x;
    top.Y = listener->transform->GetVectorTop().y;
    top.Z = listener->transform->GetVectorTop().z;

    //Position
    AkVector pos;
    pos.X = listener->transform->transform.position.x;
    pos.Y = listener->transform->transform.position.y;
    pos.Z = listener->transform->transform.position.z;

    AkSoundPosition listenerPosition;
    listenerPosition.SetPosition(pos.X, pos.Y, pos.Z);

    AK::SoundEngine::SetPosition(id, listenerPosition);
}

void ModuleAudio::PostEvent(const char* event, unsigned int id)
{
	AkPlayingID playingID;
    if (event != nullptr)
    {
		playingID = AK::SoundEngine::PostEvent(event, id);
		if (playingID == AK_INVALID_PLAYING_ID)
		{
			LOG("Post Event Failed")
		}
    }
}

void ModuleAudio::StopEvent(const AudioEvent* event, unsigned int id)
{
    if (event != nullptr)
    {
        AK::SoundEngine::ExecuteActionOnEvent(event->name.c_str(), AK::SoundEngine::AkActionOnEventType_Stop, id);

    }
}

void ModuleAudio::GetAudioInfo() 
{
	std::ifstream file("Assets/Wwise/Wwise_IDs.h");

	std::string line;

	while (std::getline(file, line))
	{
		if (line.find("EVENTS") != std::string::npos)
		{
			while (std::getline(file, line))
			{
				if (line.find("}") != std::string::npos)
				{
					break;
				}
				else if (line.find("AkUniqueID") != std::string::npos)
				{
					line = line.substr(0, line.find("=") - 1);
					line = line.substr(line.find_last_of(" ") + 1, line.length());

					wwiseData.events.push_back(line);
				}
			}
		}
		else if (line.find("BANKS") != std::string::npos)
		{
			while (std::getline(file, line))
			{
				if (line.find("}") != std::string::npos)
				{
					break;
				}
				else if (line.find("AkUniqueID") != std::string::npos)
				{
					line = line.substr(0, line.find("=") - 1);
					line = line.substr(line.find_last_of(" ") + 1, line.length());

					wwiseData.banks.push_back(line);
				}
			}
		}
	}
}

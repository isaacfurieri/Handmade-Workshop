#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <map>
#include <string>
#include <fmod.hpp>

class AudioManager
{

public:

	enum RemoveType { CUSTOM_AUDIO, ALL_AUDIO };
	enum AudioType  { SFX_AUDIO, MUSIC_AUDIO, VOICE_AUDIO };

public:

    static AudioManager* Instance();

public:

	FMOD::System* GetAudioSystem();
	FMOD::Sound* GetAudioData(AudioType audioType, const std::string& mapIndex);

public:

	bool Initialize();
	bool LoadFromFile(const std::string& filename, AudioType audioType, const std::string& mapIndex);

public:

	void Update();
	
public:

	void UnloadFromMemory(AudioType audioType, RemoveType removeType, const std::string& mapIndex = "");
	void ShutDown();

private:

	AudioManager();
	AudioManager(const AudioManager&);
	AudioManager& operator=(const AudioManager&);

private :

	FMOD::System* m_audioSystem;
	
	static std::map<std::string, FMOD::Sound*> s_sfxDataMap;
	static std::map<std::string, FMOD::Sound*> s_musicDataMap;	
	static std::map<std::string, FMOD::Sound*> s_voiceDataMap;	

};

#endif
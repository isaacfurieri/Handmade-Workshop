#include <iostream>
#include "AudioManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
AudioManager::AudioManager()
{

	m_audioSystem = 0;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns pointer to audio system
//------------------------------------------------------------------------------------------------------
FMOD::System* AudioManager::GetAudioSystem()
{

	return m_audioSystem;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns audio object based on audio map index passed 
//------------------------------------------------------------------------------------------------------
FMOD::Sound* AudioManager::GetAudioData(AudioType audioType, const std::string& mapIndex)
{

	switch (audioType)
	{
		case SFX_AUDIO   : return m_sfxDataMap[mapIndex]; break;
		case MUSIC_AUDIO : return m_musicDataMap[mapIndex]; break;
		case VOICE_AUDIO : return m_voiceDataMap[mapIndex]; break;
	}

	return 0;

}
//------------------------------------------------------------------------------------------------------
//function that initializes all audio subsystems 
//------------------------------------------------------------------------------------------------------
bool AudioManager::Initialize()
{

	//create audio subsystem and store handle in pointer	
	System_Create(&m_audioSystem);

	//initialize audio sub system with 100 channels and normal flag
	//if initialization failed, display error message and return false
	if(m_audioSystem->init(100, FMOD_INIT_NORMAL, 0) != FMOD_OK)
	{
		std::cout << "Audio sub-system did not initialize properly." << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that loads music, sfx and voice audio data from a raw audio file 
//------------------------------------------------------------------------------------------------------	
bool AudioManager::LoadFromFile(const std::string& filename, AudioType audioType, 
	                            const std::string& mapIndex)
{

	//temporary audio object pointer
	FMOD::Sound* audioData = 0;	

	//display text to state that file is being opened and read
	std::cout << "Opening and reading audio file : " << "\"" << filename << "\"" << std::endl;

	//if a music or voice file needs to be loaded create a stream to it, so that it 
	//is not loaded into memory, and set audio to 2D sound and loop it by default
	if(audioType == MUSIC_AUDIO || audioType == VOICE_AUDIO)
	{
		m_audioSystem->createStream(filename.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &audioData);
	}

	//otherwise if a sfx file needs to be loaded load it directly 
	//into memory set audio to 2D sound and do not loop it by default
	else if(audioType == SFX_AUDIO)
	{
		m_audioSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &audioData);
	}

	//if music loading failed, display error message 
	if(!audioData)
	{
		std::cout << "File could not be loaded." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	//if loading succeeded, add temporary audio data pointer to map accordingly
	switch (audioType)
	{
		case SFX_AUDIO   : m_sfxDataMap[mapIndex] = audioData; break;
		case MUSIC_AUDIO : m_musicDataMap[mapIndex] = audioData; break;
		case VOICE_AUDIO : m_voiceDataMap[mapIndex] = audioData; break;
	}
		
	//display text to state that file has been opened and read
	std::cout << "File opened and read successfully." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that updates audio system
//------------------------------------------------------------------------------------------------------
void AudioManager::Update()
{

	m_audioSystem->update();

}
//------------------------------------------------------------------------------------------------------
//function that unloads single or multiple audio objects from memory
//------------------------------------------------------------------------------------------------------
void AudioManager::UnloadFromMemory(AudioType audioType, 
	                                RemoveType removeType, const std::string& mapIndex)
{

	//temp pointer which will reference specific audio map
	std::map<std::string, FMOD::Sound*>* tempMap = 0;

	//assign whichever audio map needs to be removed from 
	//to temp pointer so that when looping through the map later, 
	//the pointer is used instead of looping through three different maps
	switch (audioType)
	{
		case SFX_AUDIO   : tempMap = &m_sfxDataMap; break;
		case MUSIC_AUDIO : tempMap = &m_musicDataMap; break;
		case VOICE_AUDIO : tempMap = &m_voiceDataMap; break;
	}

	//loop through entire audio map in order 
	//to remove a specific audio object or all audio objects
	for (auto it = tempMap->begin(); it != tempMap->end(); it++)
	{

		//if a flag is passed to remove a specific audio object
		//check if map index is the audio that needs to be removed
		//and remove it from both FMOD and the map
		if (removeType == CUSTOM_AUDIO)
		{

			if (it->first == mapIndex)
			{
				it->second->release();
				tempMap->erase(it);
				break;
			}

		}

		//otherwise if a flag is passed to remove all audio objects
		//remove the audio from FMOD
		else if (removeType == ALL_AUDIO)
		{
			it->second->release();
		}

	}

	//if all audio objects have been removed from FMOD, clear the 
	//entire map in one go, because the pointers in the map still remain
	if (removeType == ALL_AUDIO)
	{
		tempMap->clear();
	}

}
//------------------------------------------------------------------------------------------------------
//function that closes down audio system
//------------------------------------------------------------------------------------------------------
void AudioManager::ShutDown()
{

	m_audioSystem->release();

}
//------------------------------------------------------------------------------------------------------
//function that displays total size of all audio data maps
//------------------------------------------------------------------------------------------------------
void AudioManager::Output()
{

	system("cls");
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Total size of all audio maps : " << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Size of SFX Data Map   : " << m_sfxDataMap.size() << std::endl;
	std::cout << "Size of Music Data Map : " << m_musicDataMap.size() << std::endl;
	std::cout << "Size of Voice Data Map : " << m_voiceDataMap.size() << std::endl;
	std::cout << "------------------------------------" << std::endl;

}
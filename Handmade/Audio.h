#pragma once

/*===================================================================#
| 'Audio' source files last updated on 23 June 2021                  |
#===================================================================*/

#include <string>
#include <fmod.hpp>
#include "AudioManager.h"

//TODO - Create component class similar to 'Texture' class
//TODO - Blend older 'AudioManager' class with 'Audio' 
//component class and remove 'AudioManager' class entirely
//TODO - Test class fully with some audio samples

const float LEFT_PAN = -1.0;
const float RIGHT_PAN = 1.0f;

const float MIN_VOLUME = 0.0f;
const float MAX_VOLUME = 1.0f;

class Audio
{

public:

	enum class Loop
	{
		CUSTOM_LOOP = -2,
		ENDLESS_LOOP = -1,
		NO_LOOP = 0,
		ONCE_LOOP = 1
	};

	enum class Position
	{
		CUSTOM_POSITION = 0,
		START_POSITION = 1,
		END_POSITION = 2
	};

	enum class Interval
	{
		SEMITONE_INTERVAL = 0,
		OCTAVE_INTERVAL = 1
	};

	enum class AudioType
	{
		SFX_AUDIO,
		MUSIC_AUDIO,
		VOICE_AUDIO
	};

	Audio();
	~Audio() {}

	float GetPan();
	float GetVolume();
	float GetFrequency();

	unsigned int GetLength();
	unsigned int GetPosition();

	void SetPan(float pan);
	void SetVolume(float volume);
	void SetFrequency(float frequency);

	void IsMuted(bool flag);
	void SetLoopCount(Loop loopType, Loop loopCount = Loop::NO_LOOP);
	void SetAudioData(const std::string& mapIndex, AudioManager::AudioType audioType);
	void SetFrequencyRange(float minFrequency, float maxFrequency);
	void SetFrequencyInterval(Interval intervalType, float interval = 1.0f);

	bool Play();
	void Pause();
	void Resume();
	void Stop();

	void Apply();
	void Move(Position positionType, unsigned int position = 0);

private:

	float m_pan;
	float m_volume;
	float m_frequency;

	float m_minFrequency;
	float m_maxFrequency;
	
	bool m_isMuted;
	Loop m_loopCount;

	FMOD::Sound* m_audioData;
	FMOD::Channel* m_channel;
	FMOD::ChannelGroup* m_channelGroup;

};
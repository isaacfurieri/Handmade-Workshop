#pragma once

/*===================================================================#
| 'Audio' source files last updated on 19 May 2021                   |
#===================================================================*/

#include <string>
#include <fmod.hpp>
#include "AudioManager.h"

//TODO - Create component class similar to 'Texture' class
//TODO - Blend older 'AudioManager' class with 'Audio' 
//component class and remove 'AudioManager' class entirely

class Audio
{

public:

	enum Pan
	{
		LEFT_PAN = -1,
		CENTRE_PAN = 0,
		RIGHT_PAN = 1
	};

	enum Loop
	{
		CUSTOM_LOOP = -2,
		ENDLESS_LOOP = -1,
		NO_LOOP = 0,
		ONCE_LOOP = 1
	};

	enum Volume
	{
		MIN_VOLUME = 0,
		MAX_VOLUME = 1
	};

	enum Position
	{
		CUSTOM_POSITION = 0,
		START_POSITION = 1,
		END_POSITION = 2
	};

	enum Interval
	{
		SEMITONE_INTERVAL = 0,
		OCTAVE_INTERVAL = 1
	};

	enum AudioType
	{
		SFX_AUDIO,
		MUSIC_AUDIO,
		VOICE_AUDIO
	};

	Audio();
	~Audio() {}

	float& Pan();
	float& Volume();
	float& Frequency();

	unsigned int GetLength();
	unsigned int GetPosition();

	void SetMute(bool muteFlag);
	void SetLoopCount(Loop loopType, Loop loopCount = NO_LOOP);
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

	bool m_isMute;
	Loop m_loopCount;

	FMOD::Sound* m_audioData;
	FMOD::Channel* m_channel;
	FMOD::ChannelGroup* m_channelGroup;

};
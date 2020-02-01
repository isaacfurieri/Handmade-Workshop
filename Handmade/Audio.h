#ifndef AUDIO_H
#define AUDIO_H

/*==============================================================================================#
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade' game engine, for the |
| purposes of educating other fellow programmers, programming students and anyone else wishing  |
| to learn about game development, C++ and OOP. The engine, class design and overall structure  |
| is by no means perfect and there is certainly room for improvement. Feel free to use, copy,   |
| break, update and do as you wish with this code - it is there, free, for all!                 |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade', and wish to show your support, if you have any questions about the    |
| project, or if you just want to reach out, please find me on the following channels:          |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'Audio' source files last updated in February 2020									        |
#==============================================================================================*/

#include <string>
#include <fmod.hpp>
#include "AudioManager.h"

class Audio
{

public :
	
	enum Pan       { LEFT_PAN = -1, CENTRE_PAN = 0, RIGHT_PAN = 1 };
	enum Loop      { CUSTOM_LOOP = -2, ENDLESS_LOOP = -1, NO_LOOP = 0, ONCE_LOOP = 1 };
	enum Volume    { MIN_VOLUME = 0, MAX_VOLUME = 1 };
	enum Position  { CUSTOM_POSITION = 0, START_POSITION = 1, END_POSITION = 2 };
	enum Interval  { SEMITONE_INTERVAL = 0, OCTAVE_INTERVAL = 1 };
	enum AudioType { SFX_AUDIO, MUSIC_AUDIO, VOICE_AUDIO };

public :

	Audio();
	~Audio() {}

public :

	float& Pan();
	float& Volume();
	float& Frequency();

public :

	unsigned int GetLength();
	unsigned int GetPosition();

public :

	void SetMute(bool muteFlag);
	void SetLoopCount(Loop loopType, Loop loopCount = NO_LOOP);
	void SetAudioData(const std::string& mapIndex, AudioManager::AudioType audioType);
	void SetFrequencyRange(float minFrequency, float maxFrequency);
	void SetFrequencyInterval(Interval intervalType, float interval = 1.0f);

public :

	bool Play();			
	void Pause();
	void Resume();
	void Stop();

public :

	void Apply();
	void Move(Position positionType, unsigned int position = 0);

private :

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

#endif
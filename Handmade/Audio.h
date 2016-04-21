/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2016

  -----------------------------------------------------------------------------------------------

- This audio class is designed to encapsulate all the components needed to play audio files on the
  sound card. It contains all the necessary member variables that control the audio panning, volume,
  frequency, etc. The three main FMOD variables are there to get a handle on the audio channel, 
  channel group and the actual audio data. The latter pointer references the data by requesting it
  from the Audio Manager. The audio data can be played, paused, stopped, looped, and within the data,
  an arbitrary position of the audio can be found and moved to. This class acts as a component and 
  should exist within a game object.

- Six enum data types have been created to make audio manipulation and accessing easier. There is one
  for each of the basic audio features, like panning, volume, looping, frequency, etc. The AudioType
  enum is for accessing and using the correct audio map in the Audio Manager. 

- Three getter/setter combo functions have been created to return references of the three main member
  variables, pan, volume and frequency This makes accessing and assigning the containers easier in the 
  calling client code. The other two regular getter functions return the length and position of the
  audio (when being played). This measurement is in milliseconds. 

- The SetAudioData() function is used to assign the FMOD audio data to the audio object. This data is
  requested from the Audio Manager.

- The Play() function is main routine that will play the audio using the Audio Manager's FMOD audio 
  handle. Once the audio plays, it will generate a new channel and the channel handle can then be
  used to control the audio properties individually.

*/

#ifndef AUDIO_H
#define AUDIO_H

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
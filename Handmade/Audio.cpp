#include <iostream>
#include <math.h>
#include "Audio.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
Audio::Audio()
{

	m_pan = CENTRE_PAN;
	m_volume = 0.5f;
	m_frequency = 44100;

	m_minFrequency = 11025;
	m_maxFrequency = 176400;

	m_isMute = false;
	m_loopCount = NO_LOOP;

	m_channel = 0;
	m_audioData = 0;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns pan value reference
//------------------------------------------------------------------------------------------------------
float& Audio::Pan()
{

	return m_pan;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns volume value reference
//------------------------------------------------------------------------------------------------------
float& Audio::Volume()
{

	return m_volume;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns frequency value reference
//------------------------------------------------------------------------------------------------------
float& Audio::Frequency()
{

	return m_frequency;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns length of audio 
//------------------------------------------------------------------------------------------------------
unsigned int Audio::GetLength()
{

	//temp variable to hold length
	unsigned int length = 0;

	//if audio data is valid get length of
	//audio object and store in temp variable
	if(m_audioData)
	{
		m_audioData->getLength(&length, FMOD_TIMEUNIT_MS);
	}

	return length;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns specific position of audio 
//------------------------------------------------------------------------------------------------------
unsigned int Audio::GetPosition()
{

	//temp variable to hold position
	unsigned int tempPosition = 0;

	//if audio channel is valid get position
	//of audio data and store in temp variable
	if(m_channel)
	{
		m_channel->getPosition(&tempPosition, FMOD_TIMEUNIT_MS);
	}

	return tempPosition;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns mute flag 
//------------------------------------------------------------------------------------------------------
void Audio::SetMute(bool muteFlag)
{

	//assign flag variable
	m_isMute = muteFlag;

	//apply this change to audio channel
	Apply();
	
}
//------------------------------------------------------------------------------------------------------
//setter function that assigns loop value
//------------------------------------------------------------------------------------------------------
void Audio::SetLoopCount(Loop loopType, Loop loopCount)
{

	//if value is a custom value
	//assign value to loop count variable
	if(loopType == CUSTOM_LOOP)
	{
		m_loopCount = loopCount;
	}

	//otherwise if value is specifically ENDLESS or ONCE, assign that
	else if(loopType == ENDLESS_LOOP || loopType == NO_LOOP || loopType == ONCE_LOOP)
	{
		m_loopCount = loopType;
	}

	//apply this change to audio channel
	Apply();

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns FMOD pointer to audio object based on index value and audio type passed
//------------------------------------------------------------------------------------------------------
void Audio::SetAudioData(const std::string& mapIndex, AudioManager::AudioType audioType)
{

	m_audioData = TheAudio::Instance()->GetAudioData(audioType, mapIndex);

}
//------------------------------------------------------------------------------------------------------
//function that assigns min and max frequency ranges
//------------------------------------------------------------------------------------------------------
void Audio::SetFrequencyRange(float minFrequency, float maxFrequency)
{

	m_minFrequency = minFrequency;
	m_maxFrequency = maxFrequency;

}
//------------------------------------------------------------------------------------------------------
//function that changes frequency by a certain interval
//------------------------------------------------------------------------------------------------------
void Audio::SetFrequencyInterval(Interval intervalType, float interval)
{

	//temp variable
	float ratio = 0.0f;

	//if interval change is a semitone
	//calculate ratio - this is 2 to the power of 1/12
	if(intervalType == SEMITONE_INTERVAL)
	{
		ratio = pow(2.0f, 1.0f / 12.0f);
	}

	//if interval change is a octave
	//calculate ratio - this is double the frequency 
	else if(intervalType == OCTAVE_INTERVAL)
	{
		ratio = 2.0f;
	}
		
	//calculate how much the frequency should increase or decrease
	//this uses old frequency multiplied by ratio to the power of the interval
	m_frequency *= pow(ratio, interval);

	//apply this change to audio channel
	Apply();

}
//------------------------------------------------------------------------------------------------------
//function that plays the audio 
//------------------------------------------------------------------------------------------------------
bool Audio::Play()
{

	//if this is the first time the audio is being played or it's back at the start position
	//then use the audio manager to play the audio sound, as we don't want multiple sounds playing! 
	if (!m_channel || (GetPosition() == 0))
	{
		TheAudio::Instance()->
		GetAudioSystem()->playSound(m_audioData, m_channelGroup, false, &m_channel);
	}

	//if no channel was generated, display error message and return false
	if(!m_channel)
	{
		std::cout << "Audio could not be played through any channels." << std::endl;
		return false;
	}

	//set audio channel changes if any
	Apply();

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that pauses the audio
//------------------------------------------------------------------------------------------------------
void Audio::Pause()
{

	if(m_channel)
	{
		m_channel->setPaused(true);
	}

}
//------------------------------------------------------------------------------------------------------
//function that resumes the audio
//------------------------------------------------------------------------------------------------------
void Audio::Resume()
{

	if(m_channel)
	{
		m_channel->setPaused(false);
	}

}

//------------------------------------------------------------------------------------------------------
//function that stops the audio
//------------------------------------------------------------------------------------------------------
void Audio::Stop()
{

	if(m_channel)
	{
		m_channel->stop();
	}

	m_channel = 0;

}
//------------------------------------------------------------------------------------------------------
//function that applies values to channel properties
//------------------------------------------------------------------------------------------------------
void Audio::Apply()
{

	//check that pan value is in min/max range,
	//and assign pan value to audio channel
	if(m_pan < LEFT_PAN)  m_pan = LEFT_PAN;
	if(m_pan > RIGHT_PAN) m_pan = RIGHT_PAN;
	m_channel->setPan(m_pan);

	//check that volume value is in min/max range,
	//and assign volume value to audio channel
	if(m_volume < MIN_VOLUME) m_volume = MIN_VOLUME;
	if(m_volume > MAX_VOLUME) m_volume = MAX_VOLUME;
	m_channel->setVolume(m_volume);
	
	//check that frequency value is in min/max range,
	//and assign frequency value to audio channel
	if(m_frequency > m_maxFrequency) m_frequency = m_maxFrequency;
	if(m_frequency < m_minFrequency) m_frequency = m_minFrequency;
	m_channel->setFrequency(m_frequency);
	
	//set audio channel mute flag and looping value
	m_channel->setMute(m_isMute);
	m_channel->setLoopCount(m_loopCount);

}
//------------------------------------------------------------------------------------------------------
//function that moves audio to a specific position
//------------------------------------------------------------------------------------------------------
void Audio::Move(Position positionType, unsigned int position)
{

	//if audio channel is currently active, set its position value
	//the position set will be measured in milliseconds
	if(m_channel)
	{
		
		//if position moved is a custom value
		//directly move to the specified position in the channel
		if(positionType == CUSTOM_POSITION)
		{
			m_channel->setPosition(position, FMOD_TIMEUNIT_MS);
		}

		//if position moved to is the start of the audio
		//directly move to the start
		else if(positionType == START_POSITION)
		{
			m_channel->setPosition(0, FMOD_TIMEUNIT_MS);
		}

		//if position moved to is the end of the audio
		//directly move to the end
		else if(positionType == END_POSITION)
		{
			m_channel->setPosition(GetLength(), FMOD_TIMEUNIT_MS);
		}

	}

}
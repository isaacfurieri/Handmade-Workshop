#include <algorithm>
#include <math.h>
#include "Audio.h"
#include "Debug.h"

//======================================================================================================
Audio::Audio()
{
	m_pan = 0.0f;
	m_volume = 0.5f;
	m_frequency = 44100.0f;

	m_minFrequency = 11025.0f;
	m_maxFrequency = 176400.0f;

	m_isMuted = false;
	m_loopCount = Loop::NO_LOOP;

	m_channel = nullptr;
	m_audioData = nullptr;
	m_channelGroup = nullptr;
}
//======================================================================================================
float Audio::GetPan()
{
	return m_pan;
}
//======================================================================================================
float Audio::GetVolume()
{
	return m_volume;
}
//======================================================================================================
float Audio::GetFrequency()
{
	return m_frequency;
}
//======================================================================================================
unsigned int Audio::GetLength()
{
	unsigned int length = 0;

	if (m_audioData)
	{
		m_audioData->getLength(&length, FMOD_TIMEUNIT_MS);
	}

	return length;
}
//======================================================================================================
unsigned int Audio::GetPosition()
{
	unsigned int tempPosition = 0;

	if (m_channel)
	{
		m_channel->getPosition(&tempPosition, FMOD_TIMEUNIT_MS);
	}

	return tempPosition;
}
//======================================================================================================
void Audio::SetPan(float pan)
{
	m_pan = std::clamp(pan, LEFT_PAN, RIGHT_PAN);
}
//======================================================================================================
void Audio::SetVolume(float volume)
{
	m_volume = std::clamp(volume, MIN_VOLUME, MAX_VOLUME);
}
//======================================================================================================
void Audio::SetFrequency(float frequency)
{
	m_frequency = std::clamp(frequency, m_minFrequency, m_maxFrequency);
}
//======================================================================================================
void Audio::IsMuted(bool flag)
{
	m_isMuted = flag;
	Apply();
}
//======================================================================================================
void Audio::SetLoopCount(Loop loopType, Loop loopCount)
{
	if (loopType == Loop::CUSTOM_LOOP)
	{
		m_loopCount = loopCount;
	}

	else if (loopType == Loop::ENDLESS_LOOP || loopType == Loop::NO_LOOP || loopType == Loop::ONCE_LOOP)
	{
		m_loopCount = loopType;
	}

	Apply();
}
//======================================================================================================
void Audio::SetAudioData(const std::string& mapIndex, AudioManager::AudioType audioType)
{
	m_audioData = AudioManager::Instance()->GetAudioData(audioType, mapIndex);
}
//======================================================================================================
void Audio::SetFrequencyRange(float minFrequency, float maxFrequency)
{
	m_minFrequency = minFrequency;
	m_maxFrequency = maxFrequency;
}
//======================================================================================================
void Audio::SetFrequencyInterval(Interval intervalType, float interval)
{
	float ratio = 0.0f;

	if (intervalType == Interval::SEMITONE_INTERVAL)
	{
		ratio = pow(2.0f, 1.0f / 12.0f);
	}

	else if (intervalType == Interval::OCTAVE_INTERVAL)
	{
		ratio = 2.0f;
	}

	m_frequency *= pow(ratio, interval);
	Apply();
}
//======================================================================================================
bool Audio::Play()
{
	//If this is the first time the audio is being played or it's back at the start position
	//then use the audio manager to play the audio sound, as we don't want multiple sounds playing
	if (!m_channel || (GetPosition() == 0))
	{
		AudioManager::Instance()->
			GetAudioSystem()->playSound(m_audioData, m_channelGroup, false, &m_channel);
	}

	//TODO - Consider removing console messages and replace with assert/message boxes
	if (!m_channel)
	{
		Debug::Log("Audio could not be played through any channels.", Debug::WARNING);
		Debug::Log("===============================================================");
		Debug::PauseLog();
		return false;
	}

	Apply();
	return true;
}
//======================================================================================================
void Audio::Pause()
{
	if (m_channel)
	{
		m_channel->setPaused(true);
	}
}
//======================================================================================================
void Audio::Resume()
{
	if (m_channel)
	{
		m_channel->setPaused(false);
	}
}
//======================================================================================================
void Audio::Stop()
{
	if (m_channel)
	{
		m_channel->stop();
	}

	m_channel = nullptr;
}
//======================================================================================================
void Audio::Apply()
{
	//TODO - We assume the channel is valid, perhaps 
	//check for validity or place these in the setters
	m_channel->setPan(m_pan);
	m_channel->setVolume(m_volume);
	m_channel->setFrequency(m_frequency);
	m_channel->setMute(m_isMuted);
	m_channel->setLoopCount(static_cast<int>(m_loopCount));
}
//======================================================================================================
void Audio::Move(Position positionType, unsigned int position)
{
	if (m_channel)
	{
		if (positionType == Position::CUSTOM_POSITION)
		{
			m_channel->setPosition(position, FMOD_TIMEUNIT_MS);
		}

		else if (positionType == Position::START_POSITION)
		{
			m_channel->setPosition(0, FMOD_TIMEUNIT_MS);
		}

		else if (positionType == Position::END_POSITION)
		{
			m_channel->setPosition(GetLength(), FMOD_TIMEUNIT_MS);
		}
	}
}
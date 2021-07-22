#include <assert.h>
#include <algorithm>
#include <math.h>
#include "Audio.h"
#include "Utility.h"

FMOD::System* Audio::s_audioSystem = nullptr;
std::string Audio::s_rootFolder = "Assets/Audio/";
std::map<std::string, FMOD::Sound*> Audio::s_music;
std::map<std::string, FMOD::Sound*> Audio::s_sounds;

//======================================================================================================
bool Audio::Initialize()
{
	System_Create(&s_audioSystem);

	if (s_audioSystem->init(100, FMOD_INIT_NORMAL, 0) != FMOD_OK)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error initializing the FMOD audio system", Utility::Severity::Failure);
		return false;
	}

	return true;
}
//======================================================================================================
void Audio::Shutdown()
{
	s_audioSystem->release();
}
//======================================================================================================
void Audio::Update()
{
	s_audioSystem->update();
}
//======================================================================================================
bool Audio::Load(const std::string& filename, Type type, const std::string& tag)
{
	FMOD::Sound* audio = nullptr;

	//Sound effects are loaded directly into memory
	if (type == Type::Sound)
	{
		s_audioSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &audio);

		if (!audio)
		{
			Utility::Log(Utility::Destination::WindowsMessageBox,
				"Error loading sound file \"" + (s_rootFolder + filename) + "\"."
				"Possible causes could be a corrupt or missing file. It could also be "
				"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
			return false;
		}

		s_sounds[tag] = audio;
	}

	//Music is streamed directly 
	else
	{
		s_audioSystem->createStream(filename.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &audio);

		if (!audio)
		{
			Utility::Log(Utility::Destination::WindowsMessageBox,
				"Error loading music file \"" + (s_rootFolder + filename) + "\"."
				"Possible causes could be a corrupt or missing file. It could also be "
				"that the filename and/or path are incorrectly spelt.", Utility::Severity::Failure);
			return false;
		}

		s_music[tag] = audio;
	}

	return true;
}
//======================================================================================================
void Audio::Unload(const std::string& tag, Type type)
{
	if (!tag.empty())
	{
		auto& audioMap = (type == Type::Music) ? s_music : s_sounds;
		auto it = audioMap.find(tag);
		assert(it != audioMap.end());
		it->second->release();
		audioMap.erase(it);
	}

	else
	{
		for (const auto& music : s_music)
		{
			music.second->release();
		}

		for (const auto& sound : s_sounds)
		{
			sound.second->release();
		}

		s_music.clear();
		s_sounds.clear();
	}
}
//======================================================================================================
Audio::Audio()
{
	m_pan = 0.0f;
	m_volume = 0.5f;
	m_frequency = 44100.0f;

	m_minFrequency = 11025.0f;
	m_maxFrequency = 176400.0f;

	m_isMuted = false;
	m_loopCount = Loop::None;

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
	assert(m_channel != nullptr);
	m_channel->setPan(m_pan);
}
//======================================================================================================
void Audio::SetVolume(float volume)
{
	m_volume = std::clamp(volume, MIN_VOLUME, MAX_VOLUME);
	assert(m_channel != nullptr);
	m_channel->setVolume(m_volume);
}
//======================================================================================================
void Audio::SetFrequency(float frequency)
{
	m_frequency = std::clamp(frequency, m_minFrequency, m_maxFrequency);
	assert(m_channel != nullptr);
	m_channel->setFrequency(m_frequency);
}
//======================================================================================================
void Audio::IsMuted(bool flag)
{
	m_isMuted = flag;
	assert(m_channel != nullptr);
	m_channel->setMute(m_isMuted);
}
//======================================================================================================
void Audio::SetLoopCount(Loop loopType, Loop loopCount)
{
	if (loopType == Loop::Custom)
	{
		m_loopCount = loopCount;
	}

	else if (loopType == Loop::Endless || loopType == Loop::None || loopType == Loop::Single)
	{
		m_loopCount = loopType;
	}

	assert(m_channel != nullptr);
	m_channel->setLoopCount(static_cast<int>(m_loopCount));
}
//======================================================================================================
void Audio::SetAudio(const std::string& tag, Type type)
{
	auto& audioMap = (type == Type::Music) ? s_music : s_sounds;
	auto it = audioMap.find(tag);
	assert(it != audioMap.end());
	m_audioData = (*it).second;
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

	if (intervalType == Interval::Semitone)
	{
		ratio = pow(2.0f, 1.0f / 12.0f);
	}

	else if (intervalType == Interval::Octave)
	{
		ratio = 2.0f;
	}

	m_frequency *= pow(ratio, interval);
}
//======================================================================================================
bool Audio::Play()
{
	if (!m_channel || (GetPosition() == 0))
	{
		s_audioSystem->playSound(m_audioData, m_channelGroup, false, &m_channel);
	}

	if (!m_channel)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Audio could not be played through any channels.", Utility::Severity::Failure);
		return false;
	}

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
void Audio::Move(Position positionType, unsigned int position)
{
	if (m_channel)
	{
		if (positionType == Position::Custom)
		{
			m_channel->setPosition(position, FMOD_TIMEUNIT_MS);
		}

		else if (positionType == Position::Start)
		{
			m_channel->setPosition(0, FMOD_TIMEUNIT_MS);
		}

		else if (positionType == Position::End)
		{
			m_channel->setPosition(GetLength(), FMOD_TIMEUNIT_MS);
		}
	}
}
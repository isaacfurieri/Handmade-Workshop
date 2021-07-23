#pragma once

/*===================================================================#
| 'Audio' source files last updated on 23 July 2021                  |
#===================================================================*/

#include <map>
#include <string>
#include <fmod.hpp>

//TODO - Test class fully with some audio samples

const float LEFT_PAN = -1.0;
const float RIGHT_PAN = 1.0f;

const float MIN_VOLUME = 0.0f;
const float MAX_VOLUME = 1.0f;

typedef unsigned int Fuint;

class Audio
{

public:

	enum class Loop
	{
		None = 0,
		Single = 1,
		Endless = -1,
		Custom = -2
	};

	enum class Position
	{
		Start = 1,
		End = 2,
		Custom = 0
	};

	enum class Interval
	{
		Semitone = 0,
		Octave = 1
	};

	enum class Type
	{
		Music,
		Sound
	};

	static bool Initialize();
	static void Shutdown();
	static void Update();
	static bool Load(const std::string& filename, Type type, const std::string& tag);
	static void Unload(const std::string& tag = "", Type type = Type::Music);

	Audio();
	~Audio() {}

	float GetPan() const;
	float GetVolume() const;
	float GetFrequency() const;

	Fuint GetLength() const;
	Fuint GetPosition() const;

	void SetPan(float pan);
	void SetVolume(float volume);
	void SetFrequency(float frequency);

	void IsMuted(bool flag);
	void SetAudio(const std::string& tag, Type type);
	void SetLoopCount(Loop loopType, Loop loopCount = Loop::None);
	void SetFrequencyRange(float minFrequency, float maxFrequency);
	void SetFrequencyInterval(Interval intervalType, float interval = 1.0f);

	bool Play();
	void Pause();
	void Resume();
	void Stop();
	void Move(Position position, Fuint positionValue = 0);

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

	static std::string s_rootFolder;
	static FMOD::System* s_audioSystem;
	static std::map<std::string, FMOD::Sound*> s_music;
	static std::map<std::string, FMOD::Sound*> s_sounds;

};
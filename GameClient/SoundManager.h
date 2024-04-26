#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

enum eSound
{
	SOUND_CLOCK_TICK,
	SOUND_MENU_CLICK,
	SOUND_TIME_BOOM,
};

class CSoundManager
{
public:
	~CSoundManager() = default;

	void MakeSound(float Volume);
	void MakeSoundBuffer(uint16_t Index);

	void InitializeMenuMusic();

	void BuildSoundNameVector();
	CSoundManager();

private:
	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_sound;

	std::vector<std::string> m_soundNameVec;
};
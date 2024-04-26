#pragma once
#include <SFML/Audio.hpp>

class CSoundManager
{
public:
	~CSoundManager() = default;
	CSoundManager(const CSoundManager&) = delete;

	CSoundManager& Instance()
	{
		static CSoundManager s_Instance;
		return s_Instance;
	}

	
private:
	sf::SoundBuffer m_buffer;
	sf::SoundBuffer m_buff;
	sf::Sound m_sound;
	sf::Sound m_soundTick;

	CSoundManager() = default;

};
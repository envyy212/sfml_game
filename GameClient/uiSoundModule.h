#pragma once
#include "SFML/Audio/Sound.hpp"
#include "FileLoader.h"

class CSoundModule
{
public:
	CSoundModule() : m_Sound(nullptr) {};

	CSoundModule(sf::Sound* sound) : m_Sound(sound) {}

	~CSoundModule()
	{
		delete m_Sound;
	}

	void SetVolume(float volume);

private:
	sf::Sound* m_Sound;
	sf::SoundBuffer m_Buffer;
};
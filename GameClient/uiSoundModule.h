#pragma once
#include "SFML/Audio/Sound.hpp"
#include "FileLoader.h"

class CuiSoundModule
{
public:
	CuiSoundModule() : m_Sound(nullptr) {};

	CuiSoundModule(sf::Sound* sound) : m_Sound(sound) {}

	~CuiSoundModule()
	{
		delete m_Sound;
	}

	void SetVolume(float volume);

private:
	sf::Sound* m_Sound;
	sf::SoundBuffer m_Buffer;
};
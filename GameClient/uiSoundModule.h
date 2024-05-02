#pragma once
#include "DesignHelper.h"
#include "SFML/Audio/Sound.hpp"
#include "FileLoader.h"

class CSoundModule : CDesignHelper
{
public:
	CSoundModule() : m_Sound(nullptr) {};

	CSoundModule(sf::Sound* sound) : m_Sound(sound) {}

	~CSoundModule()
	{
		delete m_Sound;
	}

	void applyDesign(sf::RenderWindow& window, sf::Vector2f fPosition, float volume, sf::Sprite& sprite, sf::Texture& barTexture) override;
	void SetVolume(float volume);

private:
	sf::Sound* m_Sound;
	sf::SoundBuffer m_Buffer;
};
#pragma once
#include "DesignHelper.h"
#include "SFML/Audio/Music.hpp"
#include "FileLoader.h"

class CMusicModule : CDesignHelper
{
public:
	CMusicModule() : m_Music(nullptr) {} // Default constructor initializes the pointer to nullptr

	CMusicModule(sf::Music* music) : m_Music(music) {}

	~CMusicModule() {
		delete m_Music;
	}

	void applyDesign(sf::RenderWindow& window, sf::Vector2f fPosition, float volume, sf::Sprite& sprite, sf::Texture& barTexture/*, CMusicModule& module*/) override;

	void SetVolume(float volume);
private:
	sf::Music* m_Music;
	sf::SoundBuffer m_Buffer;

};


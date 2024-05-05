#pragma once
#include "SFML/Audio/Music.hpp"
#include "FileLoader.h"
#include "SFML/Graphics/Sprite.hpp"
#include "ResourceHolder.h"

class CuiBar
{
public:
	CuiBar() : m_SpriteBar() {};

	virtual ~CuiBar() = default;

	void SetFullVolumeBar(sf::RenderWindow& window, sf::Vector2f fPosition, float volume);
	void SetEmptyVolumeBar(sf::RenderWindow& window, sf::Vector2f fPosition);
	void OnClickVolumeBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, sf::Vector2f barPosition, float barWidth);
	void SetInitialValue(sf::Sound& sound, sf::Vector2f barPosition, float barWidth);
	sf::Vector2f RecalculateBarScale(sf::RenderWindow& window, sf::Mouse& mouse, sf::Vector2f barPosition, float barWidth);
	void OnOverlayBar(sf::RenderWindow& window, sf::Vector2f fPosition);
private:

	sf::Texture m_Texture;

	sf::SoundBuffer m_Buffer;
	sf::Sprite m_SpriteBar;

	sf::Sprite m_Overlay;
};


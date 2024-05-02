#pragma once
#include "ResourceIdentifier.h"
#include "SFML/Graphics/Sprite.hpp"

class CBar
{
public:
	CBar();

	void MakeBar(sf::RenderWindow& window, sf::Vector2f posVec, float xStep, float yStep, float scaleX, float scaleY);
	void OnFullBar(sf::RenderWindow& window, sf::Mouse mouse, sf::Sound& sound);
	void OnDefaultBar(sf::RenderWindow& window, sf::Mouse mouse, sf::Sound& sound);
	void OnClickBar(sf::RenderWindow& window, sf::Mouse mouse, sf::Sound& sound, float barPosition, float barWidth);

private:
	TextureBarHolder m_TextureBarHolder;
	sf::Sprite m_SpriteBar;
	sf::Texture m_BarTexture;
};


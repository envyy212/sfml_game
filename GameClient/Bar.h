#pragma once
#include "ResourceIdentifier.h"
#include "SFML/Graphics/Sprite.hpp"

class CBar
{
public:
	CBar();

	void MakeBar(sf::RenderWindow& window, sf::Vector2f posVec, float xStep, float yStep, float scaleX, float scaleY);
	void OnFullBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float volume, sf::Vector2f fPosition);
	void OnDefaultBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, sf::Vector2f fPosition);
	void OnClickBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, sf::Vector2f barPosition, float barWidth);
	void RenderVolumeBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float volume, bool isFullBar, sf::Vector2f fPosition);

private:
	TextureBarHolder m_TextureBarHolder;

	sf::Sprite m_SpriteBg;
	sf::Sprite m_SpriteBar;
	sf::Sprite m_SpriteBarOverlay;

	sf::Texture m_TextureBg;
	sf::Texture m_BarTexture;
	sf::Texture m_BarTextureOverLay;

};


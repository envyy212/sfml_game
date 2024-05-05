#pragma once
#include "ResourceIdentifier.h"
#include "SFML/Graphics/Sprite.hpp"

#include "uiBar.h"
#include "uiSoundModule.h"
#include "FileLoader.h"
#include <iostream>

class CBar 
{
public:
	CBar() = default;

	void OnFullBar(sf::RenderWindow& window, sf::Sound& sound, float& volume, sf::Vector2f fPosition);
	void OnDefaultBar(sf::RenderWindow& window, sf::Vector2f fPosition);
	void OnClickBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, sf::Vector2f barPosition, float barWidth);
	void RenderVolumeBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float& volume, bool isFullBar, sf::Vector2f fPosition);


private:
	std::unique_ptr<CuiBar>m_pBar = std::make_unique<CuiBar>();

	TextureBarHolder m_TextureBarHolder;

	sf::Sprite m_SpriteBg;
	sf::Sprite m_SpriteBarOverlay;

	sf::Texture m_TextureBg;
	sf::Texture m_BarTextureOverLay;
private:
	FileLoader loader;
};


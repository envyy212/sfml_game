#pragma once
#include "DesignHelper.h"
#include "ResourceIdentifier.h"
#include "SFML/Graphics/Sprite.hpp"

#include "uiMusicModule.h"
#include "uiSoundModule.h"
#include "FileLoader.h"
#include <iostream>

class CBar
{
public:
	CBar();

	void OnFullBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float& volume, sf::Vector2f fPosition);
	void OnDefaultBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Vector2f fPosition);
	void OnClickBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, sf::Vector2f barPosition, float barWidth);
	void RenderVolumeBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float& volume, bool isFullBar, sf::Vector2f fPosition);

	void SetDesign(std::unique_ptr<CMusicModule> pDesign)
	{
		m_pMusicDesign = std::move(pDesign);
	}

	void OnFullBar(sf::RenderWindow& window, sf::Mouse& mouse, float volume, sf::Vector2f fPosition/*,CMusicModule& musicModule*/)
	{
		if (m_pMusicDesign)
		{
			m_pMusicDesign->applyDesign(window, fPosition, volume, m_SpriteBar, m_BarTexture/*,musicModule*/);
		}
	}

private:
	std::unique_ptr<CMusicModule> m_pMusicDesign;
	sf::Sprite m_SpriteBar;
	sf::Texture m_BarTexture;


	TextureBarHolder m_TextureBarHolder;

	sf::Sprite m_SpriteBg;
	sf::Sprite m_SpriteBarOverlay;

	sf::Texture m_TextureBg;
	sf::Texture m_BarTextureOverLay;
private:
	FileLoader loader;
};


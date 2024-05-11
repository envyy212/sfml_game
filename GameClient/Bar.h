#pragma once
#include "ResourceIdentifier.h"
#include "SFML/Graphics/Sprite.hpp"

#include "uiBar.h"
#include "FileLoader.h"
#include <iostream>

class CBar 
{
public:
	CBar() = default;

	void OnFullBar(sf::RenderWindow& window, sf::Sound& sound, float& volume);
	void OnDefaultBar(sf::RenderWindow& window);
	void OnClickBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float barWidth, float& currentVolumeIndex);
	void RenderVolumeBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float& volume, bool isFullBar, sf::Vector2f fPosition);
	void SetPosition(sf::Vector2f fPosition);

	void SetVolume(float fVolume);
	inline float GetVolume() const { return m_fVolume; }

public:
	inline sf::Vector2f GetPosition() const { return m_fPosition; }
	void UpdateSound(sf::Vector2f fPosition);
private:
	std::unique_ptr<CuiBar>m_pBar = std::make_unique<CuiBar>();

	TextureBarHolder m_TextureBarHolder;

	sf::Sprite m_SpriteBg;
	sf::Sprite m_SpriteBarOverlay;

	sf::Texture m_TextureBg;
	sf::Texture m_BarTextureOverLay;
private:
	FileLoader loader;
private:
	sf::Vector2f m_fPosition;
	sf::Sound m_Sound;

	float m_fVolume;
};


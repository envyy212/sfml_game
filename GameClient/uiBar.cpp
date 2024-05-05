#include "uibar.h"
#include "FileLoader.h"
#include <iostream>

void CuiBar::SetFullVolumeBar(sf::RenderWindow& window, sf::Vector2f fPosition, float scale)
{
	TextureBarHolder& textureBarHolder = FileLoader::Instance().GetTextureBarHolder();
	m_Texture = textureBarHolder.get(TextureProperties::TEXTURE_BAR_FULL);

	m_SpriteBar.setTexture(m_Texture);

	m_SpriteBar.setPosition(fPosition.x + 2, fPosition.y + 4);

	m_SpriteBar.setScale(scale / 100.0f, 1.0f);

	sf::IntRect textureRect(0, 0, static_cast<int>(scale * m_Texture.getSize().x / 100), m_Texture.getSize().y);//1% of volume corresponds to 2.66 pixels
	m_SpriteBar.setTextureRect(textureRect);

	window.draw(m_SpriteBar);
}

void CuiBar::SetEmptyVolumeBar(sf::RenderWindow& window, sf::Vector2f fPosition)
{
	TextureBarHolder& textureBarHolder = FileLoader::Instance().GetTextureBarHolder();
	m_Texture = textureBarHolder.get(TextureProperties::TEXTURE_BAR_EMPTY);

	m_SpriteBar.setTexture(m_Texture);
	m_SpriteBar.setPosition(fPosition.x, fPosition.y);

	window.draw(m_SpriteBar);
}

void CuiBar::OnClickVolumeBar(sf::RenderWindow& window, sf::Mouse& mouse,sf::Sound& sound, sf::Vector2f barPosition, float barWidth)
{

	sf::Vector2i windowPos = window.getPosition();
	sf::Vector2i mousePos = mouse.getPosition();
	sf::Vector2f relativeMousePos = sf::Vector2f(mousePos.x - windowPos.x, mousePos.y - windowPos.y);

	sf::Vector2f newPos = m_SpriteBar.getPosition();
	float clickX = relativeMousePos.x;
	float barEnd = barPosition.x + barWidth;

	m_SpriteBar.setScale(sound.getVolume() / 100.0f, 1.0f);
	if (clickX < barPosition.x)
	{
		newPos.x = barPosition.x;
	}
	else if (clickX > barEnd)
	{
		newPos.x = barEnd;
	}
	else
	{
		newPos.x = clickX;
	}

	float volume = (newPos.x - barPosition.x) / barWidth * 100;
	sound.setVolume(volume);

	// Update the texture rectangle to reflect the new volume level
	sf::IntRect textureRect(0, 0, static_cast<int>(volume * 2.66f), 29); // Assuming 1% of volume corresponds to 2.66 pixels
	m_SpriteBar.setTextureRect(textureRect);

	m_SpriteBar.setPosition(newPos);
	m_SpriteBar.setScale(volume / 100.0f, 1.0f);
}

void CuiBar::OnOverlayBar(sf::RenderWindow& window, sf::Vector2f fPosition)
{
	TextureBarHolder& textureBarHolder = FileLoader::Instance().GetTextureBarHolder();
	m_Texture = textureBarHolder.get(TextureProperties::TEXTURE_BAR_LAYER);

	m_Overlay.setTexture(m_Texture);
	m_Overlay.setPosition(fPosition.x - 2, fPosition.y - 8);
	m_Overlay.setScale(1.0, 1.0);

	window.draw(m_Overlay);
}

void CuiBar::SetInitialValue(sf::Sound& sound, sf::Vector2f barPosition, float barWidth)
{
	float currentVolume = sound.getVolume();
	float initialPos = barPosition.x + (currentVolume / 100.0f) * barWidth;

	std::cout << "current volume:" << currentVolume << "\n";

	sf::Vector2f newPos = m_SpriteBar.getPosition();
	newPos.x = initialPos;

	// Update the texture rectangle to reflect the initial volume level
	sf::IntRect textureRect(0, 0, static_cast<int>(currentVolume / 100.0f * 2.66f), 29); // Assuming 1% of volume corresponds to 2.66 pixels
	m_SpriteBar.setTextureRect(textureRect);

	m_SpriteBar.setPosition(newPos);
	m_SpriteBar.setScale(currentVolume / 100.0f, 1.0f);
}

sf::Vector2f CuiBar::RecalculateBarScale(sf::RenderWindow& window, sf::Mouse& mouse, sf::Vector2f barPosition, float barWidth)
{
	sf::Vector2i windowPos = window.getPosition();
	sf::Vector2i mousePos = mouse.getPosition();
	sf::Vector2f relativeMousePos = sf::Vector2f(mousePos.x - windowPos.x, mousePos.y - windowPos.y);

	sf::Vector2f newPos = m_SpriteBar.getPosition();
	float clickX = relativeMousePos.x;
	float barEnd = barPosition.x + barWidth;

	if (clickX < barPosition.x)
		newPos.x = barPosition.x;
	else if (clickX > barEnd)
		newPos.x = barEnd;
	else
		newPos.x = clickX;

	float scale = (newPos.x - barPosition.x) / barWidth * 100;


	return sf::Vector2f(newPos.x, scale);
}
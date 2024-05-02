#include "Bar.h"
#include "SFML/Audio/Sound.hpp"


CBar::CBar()
{
}

void CBar::OnDefaultBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Vector2f fPosition)
{
	TextureBarHolder& textureHolder = FileLoader::Instance().GetTextureBarHolder();
	sf::Texture& buttonTexture = textureHolder.get(TextureProperties::TEXTURE_BAR_EMPTY);

	m_SpriteBg.setTexture(buttonTexture);
	m_SpriteBg.setPosition(fPosition.x, fPosition.y);

	window.draw(m_SpriteBg);
}

void CBar::OnFullBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float& volume, sf::Vector2f fPosition)
{
	TextureBarHolder& textureHolder = FileLoader::Instance().GetTextureBarHolder();
	sf::Texture& buttonTexture = textureHolder.get(TextureProperties::TEXTURE_BAR_FULL);
	m_SpriteBar.setTexture(buttonTexture);

	m_SpriteBar.setPosition(fPosition.x + 2, fPosition.y + 4);


	sound.setVolume(volume);

	m_SpriteBar.setScale(volume / 100.0f, 1.0f);

	// Update the texture rectangle to reflect the new volume level
	sf::IntRect textureRect(0, 0, static_cast<int>(volume * 2.66f), 29); // Assuming 1% of volume corresponds to 2.66 pixels
	m_SpriteBar.setTextureRect(textureRect);

	window.draw(m_SpriteBar);
}

void CBar::OnClickBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, sf::Vector2f barPosition, float barWidth)
{
	sf::Vector2i windowPos = window.getPosition();
	sf::Vector2i mousePos = mouse.getPosition();
	sf::Vector2f relativeMousePos = sf::Vector2f(mousePos.x - windowPos.x, mousePos.y - windowPos.y);

	sf::Vector2f newPos = m_SpriteBar.getPosition();
	float clickX = relativeMousePos.x;
	float barEnd = barPosition.x + barWidth;

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

void CBar::RenderVolumeBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float& volume, bool isFullBar, sf::Vector2f fPosition)
{
	OnDefaultBar(window, mouse, fPosition);

	if (mouse.isButtonPressed(mouse.Button::Left))
		OnClickBar(window, mouse, sound, fPosition, 200);

	if (isFullBar)
		OnFullBar(window, mouse, sound, volume, fPosition);


	TextureBarHolder& textureHolder = FileLoader::Instance().GetTextureBarHolder();
	sf::Texture& buttonTexture = textureHolder.get(TextureProperties::TEXTURE_BAR_LAYER);


	m_SpriteBarOverlay.setTexture(buttonTexture);
	m_SpriteBarOverlay.setPosition(fPosition.x - 2, fPosition.y - 8);
	m_SpriteBarOverlay.setScale(1.0, 1.0);

	window.draw(m_SpriteBarOverlay);
}
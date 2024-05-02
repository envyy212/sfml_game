#include "uiMusicModule.h"

void CMusicModule::SetVolume(float volume)
{
	m_Music->setVolume(volume);
}

void CMusicModule::applyDesign(sf::RenderWindow& window, sf::Vector2f fPosition, float volume, sf::Sprite& sprite, sf::Texture& barTexture/*, CMusicModule& module*/)
{
	sprite.setTexture(barTexture);
	sprite.setPosition(fPosition.x + 2, fPosition.y + 4);
	sprite.setScale(volume / 100.0f, 1.0f);
	sf::IntRect textureRect(0, 0, static_cast<int>(volume * 2.66f), 29);
	sprite.setTextureRect(textureRect);
	window.draw(sprite);
}
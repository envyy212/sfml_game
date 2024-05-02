#include "Bar.h"
#include "SFML/Audio/Sound.hpp"


CBar::CBar()
{
	m_TextureBarHolder.load(TextureProperties::TEXTURE_BAR_EMPTY, "fonts/Fiendish.ttf");
	m_TextureBarHolder.load(TextureProperties::TEXTURE_BAR_FULL, "fonts/tuffy.ttf");
}

void CBar::OnDefaultBar(sf::RenderWindow& window, sf::Mouse mouse, sf::Sound& sound)
{
	float volume = 0.0f;
	sound.setVolume(volume);

	m_SpriteBar.setScale(volume / 100.0f, 1.0f);
}

void CBar::OnFullBar(sf::RenderWindow& window, sf::Mouse mouse, sf::Sound& sound)
{
	float volume = 100.0f;
	sound.setVolume(volume);

	m_SpriteBar.setScale(volume / 100.0f, 1.0f);
}

void CBar::OnClickBar(sf::RenderWindow& window, sf::Mouse mouse,sf::Sound& sound, float barPosition, float barWidth)
{
	if (mouse.getPosition(window).x >= barPosition)
	{
		float volume = static_cast<float>(mouse.getPosition(window).x - barPosition) / barWidth * 100;
		sound.setVolume(volume);

		m_SpriteBar.setScale(volume / 100.0f, 1.0f);
	}
}

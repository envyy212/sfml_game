#include "Bar.h"

void OnDefaultBar(sf::RenderWindow& window, sf::Mouse mouse, sf::Sprite& volumeBarSprite)
{
	float volume = 0.0f;
	sound.setVolume(volume);

	// Update the visual display of the volume bar
	volumeBarSprite.setScale(volume / 100.0f, 1.0f);
}

void OnFullBar(sf::RenderWindow& window, sf::Mouse mouse, sf::Sprite& volumeBarSprite)
{
	float volume = 100.0f;
	sound.setVolume(volume);

	volumeBarSprite.setScale(volume / 100.0f, 1.0f);
}

void OnClickBar(sf::RenderWindow& window, sf::Mouse mouse, sf::Sprite& volumeBarSprite, float barPosition, float barWidth) {
	if (mouse.getPosition(window).x >= barPosition)
	{
		float volume = static_cast<float>(mouse.getPosition(window).x - barPosition) / barWidth * 100;
		sound.setVolume(volume);

		volumeBarSprite.setScale(volume / 100.0f, 1.0f);
	}
}

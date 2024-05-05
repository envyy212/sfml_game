#include "Bar.h"
#include "SFML/Audio/Sound.hpp"
#include "uiBar.h"

void CBar::OnDefaultBar(sf::RenderWindow& window, sf::Vector2f fPosition)
{
	if (m_pBar)
		m_pBar->SetEmptyVolumeBar(window, fPosition);
}

void CBar::OnFullBar(sf::RenderWindow& window, sf::Sound& sound, float& volume, sf::Vector2f fPosition)
{
	if(m_pBar)
		m_pBar->SetFullVolumeBar(window, fPosition, volume);

	float volumae = sound.getVolume();
	std::cout << "CBAR::OnFullBar " << volumae << "passed volume OnFullBar" << volume << "\n";
//	sound.setVolume(volume);
}

void CBar::OnClickBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, sf::Vector2f barPosition, float barWidth)
{
//	sf::Vector2i windowPos = window.getPosition();
//	sf::Vector2i mousePos = mouse.getPosition();
//	sf::Vector2f relativeMousePos = sf::Vector2f(mousePos.x - windowPos.x, mousePos.y - windowPos.y);
//
//	sf::Vector2f newPos = m_SpriteBg.getPosition();
//	float clickX = relativeMousePos.x;
//	float barEnd = barPosition.x + barWidth;
//
//	m_SpriteBg.setScale(sound.getVolume() / 100.0f, 1.0f);
//	if (clickX < barPosition.x)
//	{
//		newPos.x = barPosition.x;
//	}
//	else if (clickX > barEnd)
//	{
//		newPos.x = barEnd;
//	}
//	else
//	{
//		newPos.x = clickX;
//	}
//
//	float volume = (newPos.x - barPosition.x) / barWidth * 100;
//	sound.setVolume(volume);
//
//	// Update the texture rectangle to reflect the new volume level
//	sf::IntRect textureRect(0, 0, static_cast<int>(volume * 2.66f), 29); // Assuming 1% of volume corresponds to 2.66 pixels
//	m_SpriteBg.setTextureRect(textureRect);
//
//	m_SpriteBg.setPosition(newPos);
//	m_SpriteBg.setScale(volume / 100.0f, 1.0f);

	if (m_pBar)
	{
		m_pBar->OnClickVolumeBar(window, mouse, sound, barPosition, barWidth);
		float volume = sound.getVolume();
		std::cout << "CBAR::OnClickBar " << volume << "\n";
//		float volume = m_pBar->RecalculateBarScale(window, mouse, barPosition, barWidth).x;
//		sound.setVolume(volume);
	}
}

void CBar::RenderVolumeBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float& volume, bool isFullBar, sf::Vector2f fPosition)
{
	OnDefaultBar(window, fPosition);

	if (mouse.isButtonPressed(mouse.Button::Left))
		OnClickBar(window, mouse, sound, fPosition, 200);

	m_pBar->SetInitialValue(sound, fPosition, 200);

	if (isFullBar)
		OnFullBar(window, sound, volume, fPosition);

	if (m_pBar)
	{
		float volume = sound.getVolume();
		m_pBar->OnOverlayBar(window, fPosition);
		std::cout << "CBAR::RenderVolumeBar " << volume << "passed volume rendervolumebar" << volume << "\n";
	}
}
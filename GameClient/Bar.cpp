#include "Bar.h"
#include "SFML/Audio/Sound.hpp"
#include "uiBar.h"

void CBar::OnDefaultBar(sf::RenderWindow& window)
{
	if (m_pBar)
		m_pBar->SetEmptyVolumeBar(window, m_fPosition);
}

void CBar::OnFullBar(sf::RenderWindow& window, sf::Sound& sound, float& volume)
{
	if(m_pBar)
		m_pBar->SetFullVolumeBar(window, m_fPosition, volume);

	float volumae = sound.getVolume();
	std::cout << "CBAR::OnFullBar " << volumae << "passed volume OnFullBar" << volume << "\n";
//	sound.setVolume(volume);
}

void CBar::OnClickBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float barWidth)
{
	if (m_pBar)
	{
		m_pBar->OnClickVolumeBar(window, mouse, sound, m_fPosition, barWidth);
//		float volume = sound.getVolume();
		float volume = m_pBar->RecalculateBarScale(window, mouse, m_fPosition, barWidth).y;

		std::cout << "CBAR::OnClickBar " << volume << "\n";
		sound.setVolume(volume);
	}
}
void CBar::SetPosition(sf::Vector2f fPosition)
{
	m_fPosition = fPosition;
}

void CBar::RenderVolumeBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float& volume, bool isFullBar, sf::Vector2f fPosition)
{

	SetPosition(fPosition);
	OnDefaultBar(window);

	if (mouse.isButtonPressed(mouse.Button::Left))
		OnClickBar(window, mouse, sound, 200);

	if (isFullBar)
		OnFullBar(window, sound, volume);

	if (m_pBar)
	{
		float volume = sound.getVolume();
		m_pBar->OnOverlayBar(window, fPosition);
		std::cout << "CBAR::RenderVolumeBar " << volume << "passed volume rendervolumebar" << volume << "\n";
	}
	m_Sound = sound;
}

void CBar::UpdateSound(sf::Vector2f fPosition)
{
	m_pBar->SetInitialValue(m_Sound, m_fPosition, 200);
}

float CBar::CalculateVolume(sf::Vector2f clickPosition, sf::Vector2f barPosition, float barWidth)
{
	float volume = (clickPosition.x - barPosition.x) / barWidth;
	volume = std::clamp(volume, 0.0f, 1.0f);
	return volume;
}
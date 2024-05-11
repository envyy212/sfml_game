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

void CBar::SetVolume(float fVolume)
{
	m_fVolume = fVolume;
}

void CBar::OnClickBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float barWidth, float& curretVolumeIndex)
{
	if (m_pBar)
	{
		m_pBar->OnClickVolumeBar(window, mouse, sound, m_fPosition, barWidth);
		curretVolumeIndex = sound.getVolume();
//		float curretVolumeIndex = m_pBar->RecalculateBarScale(window, mouse, m_fPosition, barWidth).y;

		std::cout << "CBAR::OnClickBar " << curretVolumeIndex << "\n";

		SetVolume(curretVolumeIndex);
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
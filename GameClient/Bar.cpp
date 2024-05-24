#include "Bar.h"
#include "SFML/Audio/Sound.hpp"
#include "uiBar.h"

void CBar::OnDefaultBar(sf::RenderWindow& window)
{
	if (!m_pBar)
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "CBar::OnDefaultBar m_pBar is null.");

	m_pBar->SetEmptyVolumeBar(window, m_fPosition);
}

void CBar::OnFullBar(sf::RenderWindow& window, sf::Sound& sound, float& volume)
{
	if(!m_pBar)
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "CBar::OnFullBar m_pBar is null.");

	m_pBar->SetFullVolumeBar(window, m_fPosition, volume);
}

void CBar::SetVolume(float fVolume)
{
	m_fVolume = fVolume;
}

void CBar::OnClickBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float barWidth, float& curretVolumeIndex)
{
	if (!m_pBar)
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "CBar::OnClickBar m_pBar is null.");

	m_pBar->OnClickVolumeBar(window, mouse, sound, m_fPosition, barWidth);
	curretVolumeIndex = sound.getVolume();

	SetVolume(curretVolumeIndex);
}
void CBar::SetPosition(sf::Vector2f fPosition)
{
	m_fPosition = fPosition;
}

void CBar::RenderVolumeBar(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, float& volume, bool isFullBar, sf::Vector2f fPosition)
{
	if(!m_pBar)
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "CBar::RenderVolumeBar m_pBar is null.");

	SetPosition(fPosition);
	OnDefaultBar(window);

	if (isFullBar)
		OnFullBar(window, sound, volume);


	float fVolume = sound.getVolume();
	m_pBar->OnOverlayBar(window, fPosition);

	Log::Instance().TraceLog(eLogType::LOG_TYPE_LOG, "CBAR::RenderVolumeBar %d passed volume %d.", fVolume, volume);

	m_Sound = sound;
}

void CBar::UpdateSound(sf::Vector2f fPosition)
{
	m_pBar->SetInitialValue(m_Sound, m_fPosition, 200);
}
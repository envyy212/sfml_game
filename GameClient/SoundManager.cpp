#include "SoundManager.h"

CSoundManager::CSoundManager()
{
	m_soundNameVec = { "clock_tick", "menu_click", "time_boom"};

	for (auto it = 0; it < m_soundNameVec.size(); ++it)
	{
		m_soundNameVec[it] = "audio/" + m_soundNameVec[it];
		m_soundNameVec[it] += ".flac";
	}
}

void CSoundManager::MakeSoundBuffer(uint16_t Index)
{
	if (!m_soundBuffer.loadFromFile(m_soundNameVec[Index]))
		return;
}

void CSoundManager::MakeSound(float Volume)
{
	m_sound.setBuffer(m_soundBuffer);
	m_sound.setVolume(Volume);
	m_sound.play();
}

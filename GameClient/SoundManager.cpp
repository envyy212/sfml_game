#include "SoundManager.h"
#include <SFML/Audio.hpp>

CSoundManager::CSoundManager()
	: m_SoundBuffers()
	, m_soundNameList()
{
//	SoundBufferHolder& mutableSoundBuffers = const_cast<SoundBufferHolder&>(m_SoundBuffers);

	m_SoundBuffers.load(SoundEffect::SOUND_CLOCK_TICK, "audio/clock_tick.flac");
	m_SoundBuffers.load(SoundEffect::SOUND_TIME_BOOM, "audio/time_boom.flac");
	m_SoundBuffers.load(SoundEffect::SOUND_MENU_CLICK, "audio/menu_click.flac");
}

void CSoundManager::PlaySounds(SoundEffect::eSound effect)
{
	m_soundNameList.push_back(sf::Sound());
	sf::Sound& sound = m_soundNameList.back();

	sound.setBuffer(m_SoundBuffers.get(effect));
	sound.play();
}

void CSoundManager::RemoveReplayedSound()
{
	m_soundNameList.remove_if([](const sf::Sound& s)
		{
			return s.getStatus() == sf::Sound::Stopped;
		});
}

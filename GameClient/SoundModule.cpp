#include "SoundModule.h"
#include <SFML/Audio.hpp>
#include "FileLoader.h"

CSoundModule::CSoundModule()
	: m_SoundBuffers()
	, m_soundNameList()
{
//	SoundBufferHolder& mutableSoundBuffers = const_cast<SoundBufferHolder&>(m_SoundBuffers);

}

void CSoundModule::PlaySounds(SoundEffect::eSound effect)
{
	SoundBufferHolder& soundBufferHolder = FileLoader::Instance().GetSoundBufferHolder();
	m_SoundBuffers = soundBufferHolder.get(effect);

	m_soundNameList.push_back(sf::Sound());
	sf::Sound& sound = m_soundNameList.back();

	sound.setBuffer(m_SoundBuffers);
	sound.play();
}

void CSoundModule::RemoveReplayedSound()
{
	m_soundNameList.remove_if([](const sf::Sound& s)
		{
			return s.getStatus() == sf::Sound::Stopped;
		});
}

#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/NonCopyable.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include <list>

class CSoundManager : private sf::NonCopyable
{
public:

	CSoundManager();
	~CSoundManager() = default;

	void PlaySounds(SoundEffect::eSound effect);
	void RemoveReplayedSound();

private:
	SoundBufferHolder m_SoundBuffers;
	std::list<sf::Sound> m_soundNameList;
};
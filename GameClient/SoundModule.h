#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/NonCopyable.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include <list>

class CSoundModule : private sf::NonCopyable
{
public:
	CSoundModule();
	~CSoundModule() = default;

	void PlaySounds(SoundEffect::eSound effect);
	void RemoveReplayedSound();
private:
	sf::SoundBuffer m_SoundBuffers;
	std::list<sf::Sound> m_soundNameList;
};
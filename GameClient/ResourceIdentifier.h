#pragma once
#include "ResourceHolder.h"
#include "ResourceHolderInc.h"

namespace SoundEffect
{
	enum eSound
	{
		SOUND_CLOCK_TICK,
		SOUND_MENU_CLICK,
		SOUND_TIME_BOOM,
	};
}

namespace Images
{
	enum eImage
	{

	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::SoundBuffer, SoundEffect::eSound> SoundBufferHolder;
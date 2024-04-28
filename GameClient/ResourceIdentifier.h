#pragma once
#include "ResourceHolder.h"
#include "ResourceHolderInc.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics.hpp>

namespace SoundEffect
{
	enum eSound
	{
		SOUND_CLOCK_TICK,
		SOUND_MENU_CLICK,
		SOUND_TIME_BOOM
	};
}

namespace Images
{
	enum eImage
	{
		IMAGE_MENU_FRAME
	};
}

namespace TextProperties
{
	enum eTextFont
	{
		TEXT_FONT_ARIAL,		/*common font*/
		TEXT_FONT_FIENDISH,		/*bloody splash */
		TEXT_FONT_TUFFY			/*  */
	};

	enum eTextSize
	{
		TEXT_EXTRA_SMALL = 16,
		TEXT_SMALL = 20,
		TEXT_MEDIUM = 24,
		TEXT_LOWER_BIG = 28,
		TEXT_BIG = 32,
		TEXT_EXTRA_BIG = 36,
		TEXT_LARGE = 72
	};

	enum eTextType
	{
		TEXT_NORMAL,
		TEXT_BUTTON,
	};

	enum eTextState
	{
		TEXT_STATE_DEFAULT,
		TEXT_STATE_OVER,
		TEXT_STATE_CLICKED,
		TEXT_STATE_LOCKED, /*text as button locked (disabled)*/
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Font, TextProperties::eTextFont> TextHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::eSound> SoundBufferHolder;
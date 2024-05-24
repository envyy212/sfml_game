#pragma once
#include "ResourceHolder.h"
#include "ResourceHolderInc.h"

#include <SFML/Audio/Music.hpp>
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

namespace MusicProperties
{
	enum eMusic
	{
		MUSIC_MENU,
	};
}

namespace Images
{
	enum eImage
	{
		IMAGE_MENU_FRAME
	};
}

namespace TextureProperties
{
	enum eTexturesButtonBack
	{
		TEXTURE_BUTTON_NORMAL,
		TEXTURE_BUTTON_OVER,
		TEXTURE_BUTTON_CLICKED,
	};

	enum eTextureBar
	{
		TEXTURE_BAR_LAYER,
		TEXTURE_BAR_EMPTY,
		TEXTURE_BAR_FULL,
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
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Font, TextProperties::eTextFont> TextHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::eSound> SoundBufferHolder;
typedef ResourceHolder<sf::Texture, TextureProperties::eTexturesButtonBack> TextureHolder;
typedef ResourceHolder<sf::Texture, TextureProperties::eTextureBar> TextureBarHolder;

typedef ResourceHolder<sf::Music, MusicProperties::eMusic> MusicHolder;
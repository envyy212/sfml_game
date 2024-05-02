#include "FileLoader.h"

FileLoader::FileLoader()
	: m_TextureHolder()
	, m_TextureBarHolder()
	, m_TextFontHolder()
	, m_SoundBufferHolder()

{

}

void FileLoader::LoadMenuImages()
{
	/*button back*/
	m_TextureHolder.load(TextureProperties::TEXTURE_BUTTON_NORMAL, "ui/keys/Outline/Double/normal/arrow_w.png");
	m_TextureHolder.load(TextureProperties::TEXTURE_BUTTON_OVER, "ui/keys/Outline/Double/over/arrow_w.png");
	m_TextureHolder.load(TextureProperties::TEXTURE_BUTTON_CLICKED, "ui/keys/Outline/Double/pressed/arrow_w.png");
}

void FileLoader::LoadMenuBars()
{
	m_TextureBarHolder.load(TextureProperties::TEXTURE_BAR_LAYER, "ui/bars/ProgressBar_07/BarV7_ProgressBarBorder.png");
	m_TextureBarHolder.load(TextureProperties::TEXTURE_BAR_EMPTY, "ui/bars/ProgressBar_07/BarV7_Bar.png");
	m_TextureBarHolder.load(TextureProperties::TEXTURE_BAR_FULL, "ui/bars/ProgressBar_07/BarV7_ProgressBar.png");
}

void FileLoader::LoadMenuFonts()
{
	m_TextFontHolder.load(TextProperties::TEXT_FONT_ARIAL, "fonts/arial.ttf");
	m_TextFontHolder.load(TextProperties::TEXT_FONT_FIENDISH, "fonts/Fiendish.ttf");
	m_TextFontHolder.load(TextProperties::TEXT_FONT_TUFFY, "fonts/tuffy.ttf");
}

void FileLoader::LoadMenuSounds()
{
	m_SoundBufferHolder.load(SoundEffect::SOUND_CLOCK_TICK, "audio/clock_tick.flac");
	m_SoundBufferHolder.load(SoundEffect::SOUND_TIME_BOOM, "audio/time_boom.flac");
	m_SoundBufferHolder.load(SoundEffect::SOUND_MENU_CLICK, "audio/menu_click.flac");
}

void FileLoader::RegisterLoadingMenuProccess()
{
	LoadMenuImages();
	LoadMenuBars();
	LoadMenuFonts();
	LoadMenuSounds();
}

TextureHolder& FileLoader::GetTextureHolder()
{
	return m_TextureHolder;
}

TextureBarHolder& FileLoader::GetTextureBarHolder()
{
	return m_TextureBarHolder;
}

TextHolder& FileLoader::GetTextFontHolder()
{
	return m_TextFontHolder;
}

SoundBufferHolder& FileLoader::GetSoundBufferHolder()
{
	return m_SoundBufferHolder;
}
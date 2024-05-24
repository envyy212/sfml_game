#include "FileLoader.h"

FileLoader::FileLoader()
	: m_textureHolder()
	, m_textureBarHolder()
	, m_textFontHolder()
	, m_soundBufferHolder()
{

}

void FileLoader::LoadMenuImages()
{
	/*button back*/
	m_textureHolder.load(TextureProperties::TEXTURE_BUTTON_NORMAL, "ui/keys/Outline/Double/normal/arrow_w.png");
	m_textureHolder.load(TextureProperties::TEXTURE_BUTTON_OVER, "ui/keys/Outline/Double/over/arrow_w.png");
	m_textureHolder.load(TextureProperties::TEXTURE_BUTTON_CLICKED, "ui/keys/Outline/Double/pressed/arrow_w.png");
}

void FileLoader::LoadMenuBars()
{
	m_textureBarHolder.load(TextureProperties::TEXTURE_BAR_LAYER, "ui/bars/ProgressBar_07/BarV7_ProgressBarBorder.png");
	m_textureBarHolder.load(TextureProperties::TEXTURE_BAR_EMPTY, "ui/bars/ProgressBar_07/BarV7_Bar.png");
	m_textureBarHolder.load(TextureProperties::TEXTURE_BAR_FULL, "ui/bars/ProgressBar_07/BarV7_ProgressBar.png");
}

void FileLoader::LoadMenuFonts()
{
	m_textFontHolder.load(TextProperties::TEXT_FONT_ARIAL, "fonts/arial.ttf");
	m_textFontHolder.load(TextProperties::TEXT_FONT_FIENDISH, "fonts/Fiendish.ttf");
	m_textFontHolder.load(TextProperties::TEXT_FONT_TUFFY, "fonts/tuffy.ttf");
}

void FileLoader::LoadMenuSounds()
{
	m_soundBufferHolder.load(SoundEffect::SOUND_CLOCK_TICK, "audio/clock_tick.flac");
	m_soundBufferHolder.load(SoundEffect::SOUND_TIME_BOOM, "audio/time_boom.flac");
	m_soundBufferHolder.load(SoundEffect::SOUND_MENU_CLICK, "audio/menu_click.flac");
}

void FileLoader::RegisterLoadingMenuProccess()
{
	LoadMenuImages();
	LoadMenuBars();
	LoadMenuFonts();
	LoadMenuSounds();
//	LoadMusic();
}

TextureHolder& FileLoader::GetTextureHolder()
{
	return m_textureHolder;
}

TextureBarHolder& FileLoader::GetTextureBarHolder()
{
	return m_textureBarHolder;
}

TextHolder& FileLoader::GetTextFontHolder()
{
	return m_textFontHolder;
}

SoundBufferHolder& FileLoader::GetSoundBufferHolder()
{
	return m_soundBufferHolder;
}

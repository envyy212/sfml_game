#pragma once
#include <SFML/System/NonCopyable.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <SFML/Graphics/Texture.hpp>

class FileLoader : private sf::NonCopyable
{
public:
	FileLoader();

	FileLoader(const FileLoader&) = delete;

	static FileLoader& Instance()
	{
		static FileLoader s_Instance;
		return s_Instance;
	}

	void LoadMenuImages();
	void LoadMenuBars();
	void LoadMenuFonts();
	void LoadMenuSounds();
//	void LoadMusic();
	void RegisterLoadingMenuProccess();


	TextureHolder& GetTextureHolder();
	TextureBarHolder& GetTextureBarHolder();
	TextHolder& GetTextFontHolder();
	SoundBufferHolder& GetSoundBufferHolder();
private:
	TextureHolder m_textureHolder;
	TextureBarHolder m_textureBarHolder;
	TextHolder m_textFontHolder;
	SoundBufferHolder m_soundBufferHolder;	
	//	std::unique_ptr<TextureHolder> m_TextureHolder = std::make_unique<TextureHolder>();
//	std::unique_ptr<TextureBarHolder> m_TextureBarHolder = std::make_unique<TextureBarHolder>();
//	std::unique_ptr<TextHolder> m_TextFontHolder = std::make_unique<TextHolder>();
//	std::unique_ptr<SoundBufferHolder> m_SoundBufferHolder = std::make_unique<SoundBufferHolder>();


//	TextureHolder* m_TextureHolder;
//	TextureBarHolder m_TextureBarHolder;

};


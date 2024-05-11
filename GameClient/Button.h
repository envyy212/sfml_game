#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "ResourceIdentifier.h"
#include "FileLoader.h"


class CButton
{
public:
	enum ButtonState
	{
		BUTTON_STATE_NORMAL,
		BUTTON_STATE_OVER,
		BUTTON_STATE_PRESSED,
	};
public:
	CButton() : m_FileLoader(*new FileLoader()) {}

	~CButton() = default;
	CButton(FileLoader& fileLoader) : m_FileLoader(fileLoader)
	{
		m_FileLoader.LoadMenuImages();
	}

	void MakeButton(sf::RenderWindow& window, sf::Vector2f posVec, float xStep, float yStep, float scaleX, float scaleY);
	void OnDefaultButton(sf::RenderWindow& window, sf::Mouse mouse);
	void OnOverButton(sf::RenderWindow& window, sf::Mouse mouse);
	void OnClickButton(sf::RenderWindow& window, sf::Mouse mouse);
	void HandleClickEvent(sf::RenderWindow& window, sf::Mouse mouse, uint16_t& index);
private:
	FileLoader& m_FileLoader;

	TextureHolder m_TextureHolder;
	sf::Texture m_Texture;
	sf::Sprite m_buttonImage;

	bool m_IsClickable = true;
};

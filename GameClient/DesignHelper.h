#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class CDesignHelper
{
public:
	CDesignHelper() = default;
	virtual ~CDesignHelper() = default;
	virtual void applyDesign(sf::RenderWindow& window, sf::Vector2f fPosition, float volume, sf::Sprite& sprite, sf::Texture& barTexture) = 0;
};
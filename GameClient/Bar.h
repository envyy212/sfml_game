#pragma once
#include "ResourceIdentifier.h"

class CBar
{
public:
	void MakeBar(sf::RenderWindow& window, sf::Vector2f posVec, float xStep, float yStep, float scaleX, float scaleY);
	void OnDefaultBar(sf::RenderWindow& window, sf::Mouse mouse);
	void OnFullBar(sf::RenderWindow& window, sf::Mouse mouse);
	void OnClickBar(sf::RenderWindow& window, sf::Mouse mouse);

private:
	TextureBarHolder m_TextureBarHolder;
};


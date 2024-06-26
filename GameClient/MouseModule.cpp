#include "MouseModule.h"
#include "TextModule.h"

void MouseModule::HandleMouseClick(sf::RenderWindow& window, sf::Text& text, std::function<void(void)> funcToCall)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			sf::FloatRect textBounds = text.getGlobalBounds();
			if (textBounds.contains(mousePos))
			{
				funcToCall();
			}
		}
	}
}

#pragma once
#include <functional>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics.hpp>


class MouseModule
{
public:
	MouseModule() = default;
	~MouseModule() = default;

	void HandleMouseClick(sf::RenderWindow& window, sf::Text& text, std::function<void(void)> funcToCall);

private:
};
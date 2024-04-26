#include "Game.h"
#include "SettingsModule.h"
#include "MainMenu.h"
#include <SFML/Audio.hpp>

bool CGame::IsRunning()
{
	sf::Music music;
	if (!music.openFromFile("BGM.flac"))
		return -1; // error
	music.setVolume(80);
	music.play();

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("menu_click.flac"))
		return -1;

	sf::Sound sound;
	sound.setBuffer(buffer);


	std::unique_ptr<CSettingsModule> pModule = std::make_unique<CSettingsModule>();
	pModule->ProccessData();

	m_bState = true;
	if (m_sWidth > static_cast<uint16_t>(WindowConfig::WINDOW_MAX_WIDTH))
	{
		std::cout << "Given parameter for width is too large maximum width is " << static_cast<uint16_t>(WindowConfig::WINDOW_MAX_WIDTH);
		return false;
	}

	if (m_sHeight > static_cast<uint16_t>(WindowConfig::WINDOW_MAX_HEIGHT))
	{
		std::cout << "Given parameter for height is too large maximum height is " << static_cast<uint16_t>(WindowConfig::WINDOW_MAX_HEIGHT);
		return false;
	}

	sf::RenderWindow window(sf::VideoMode(m_sWidth, m_sHeight), "Snake Game #xd12564", sf::Style::Fullscreen);
	CMainMenu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Key::Up)
				{
					menu.MoveDirection(static_cast<uint16_t>(sf::Keyboard::Key::Up));
					sound.setVolume(80);
					sound.play();
				}
				if (event.key.code == sf::Keyboard::Key::Down)
				{
					menu.MoveDirection(static_cast<uint16_t>(sf::Keyboard::Key::Down));
					sound.play();
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					if (menu.GetSelectedItemIndex() == 0);
					{
						std::cout << "play";
					}
					if (menu.GetSelectedItemIndex() == 1);
					{
						std::cout << "Options";
					}
					if (menu.GetSelectedItemIndex() == 2);
					{
						std::cout << "Ranking";
					}
					if (menu.GetSelectedItemIndex() == 3);
					{
						std::cout << "About";
					}
					if (menu.GetSelectedItemIndex() == 4);
					{
						window.close();
					}
				}
			}

		}
		window.clear();
		menu.MakeWindow(window);
		window.display();
	}
	return m_bState ? true : false;
}

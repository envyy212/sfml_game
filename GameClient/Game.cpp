#include "Game.h"
#include "SettingsModule.h"
#include "MainMenu.h"
#include <SFML/Audio.hpp>
#include "SoundManager.h"

bool CGame::IsRunning()
{
	sf::Music music;
	CSoundManager soundMgr;
	if (!music.openFromFile("audio/BGM.flac"))
		return -1;
	music.setVolume(80);
	music.play();


	std::unique_ptr<CSettingsModule> pModule = std::make_unique<CSettingsModule>();
	pModule->ProccessData();

	m_bState = true;

	sf::RenderWindow window(sf::VideoMode(m_sWidth, m_sHeight), "Survivor. v0.0.1", sf::Style::Fullscreen);

	CMainMenu menu(window.getSize().x, window.getSize().y);

	uint16_t index = 1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Key::Up)
				{
					index--;
					menu.MoveDirection(static_cast<uint16_t>(sf::Keyboard::Key::Up));
					soundMgr.PlaySounds(SoundEffect::SOUND_MENU_CLICK);
				}
				if (event.key.code == sf::Keyboard::Key::Down)
				{
					index++;
					menu.MoveDirection(static_cast<uint16_t>(sf::Keyboard::Key::Down));
					soundMgr.PlaySounds(SoundEffect::SOUND_MENU_CLICK);
				}
			}
		}
		std::cout << index;
		window.clear();
		menu.MakeWindow(window, index);
		window.display();
	}
	return m_bState ? true : false;
}

/* register game state */
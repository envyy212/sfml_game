#include "Game.h"
#include "SettingsModule.h"
#include "MainMenu.h"
#include <SFML/Audio.hpp>
#include "SoundManager.h"
#include "TextModule.h"
#include "MouseModule.h"
#include "FileLoader.h"
#include <TheCore/GameStateHandle.h>

void CGame::Run()
{
	sf::Music music;
	CSoundManager soundMgr;
	sf::Keyboard keyboard;


	TextModule* ctext = new TextModule;
	if (!music.openFromFile("audio/BGM.flac"))
		return;
	music.setVolume(80);
	music.play();

	GameStateHandle state;
	state.test();

	sf::Mouse mouse;

	std::unique_ptr<CSettingsModule> pModule = std::make_unique<CSettingsModule>();

	pModule->ProccessData();

	/* load all menu assets with start up as there are just few small ones */
	FileLoader& loader = FileLoader::Instance();
	loader.RegisterLoadingMenuProccess();
	/* end loading */

	sf::RenderWindow window(sf::VideoMode(m_sWidth, m_sHeight), "Survivor. v0.0.1", sf::Style::Fullscreen);

	CMainMenu* pMenu = new CMainMenu(window.getSize().x, window.getSize().y);

	uint16_t currentMenuIndex = pMenu->GetLastSetIndex(); // Store the last set index value
	sf::Sound sound;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				ctext->HandleClickEvent(window, mouse, currentMenuIndex); // Update the index value when a button is clicked
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::Up)
				{
					pMenu->MoveDirection(static_cast<uint16_t>(sf::Keyboard::Key::Up));
				}
				else if (event.key.code == sf::Keyboard::Key::Down)
				{
					pMenu->MoveDirection(static_cast<uint16_t>(sf::Keyboard::Key::Down));
				}
			}
		}

		window.clear();
		pMenu->MakeWindow(window, mouse, sound, music, currentMenuIndex);
		currentMenuIndex = pMenu->GetLastSetIndex();
		window.display();
	}
}

/* register game state */
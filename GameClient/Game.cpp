#include "Game.h"
#include "SettingsModule.h"
#include "MainMenu.h"
#include <SFML/Audio.hpp>
#include "SoundManager.h"
#include "TextModule.h"
#include "MouseModule.h"

void CGame::Run()
{
	sf::Music music;
	CSoundManager soundMgr;
	sf::Keyboard keyboard;
	TextModule ctext;
	if (!music.openFromFile("audio/BGM.flac"))
		return;
	music.setVolume(80);
	music.play();

	sf::Mouse mouse;
	MouseModule mousemodule;

	std::unique_ptr<CSettingsModule> pModule = std::make_unique<CSettingsModule>();
	pModule->ProccessData();

	sf::RenderWindow window(sf::VideoMode(m_sWidth, m_sHeight), "Survivor. v0.0.1", sf::Style::Fullscreen);

	CMainMenu menu(window.getSize().x, window.getSize().y);

	uint16_t index = 1;
	SetIndex(index);

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
					SetIndex(index);
					menu.MoveDirection(static_cast<uint16_t>(sf::Keyboard::Key::Up));
					soundMgr.PlaySounds(SoundEffect::SOUND_MENU_CLICK);
				}
				if (event.key.code == sf::Keyboard::Key::Down)
				{
					index++;
					SetIndex(index);
					menu.MoveDirection(static_cast<uint16_t>(sf::Keyboard::Key::Down));
					soundMgr.PlaySounds(SoundEffect::SOUND_MENU_CLICK);
				}
			}

//			module.SetTextStateByMouseAction(mouse);
		}
		window.clear();

		auto functionToCall = [this, &index]() {
			SetIndex(3);
			};

		std::string stra = ctext.GetClickedText().getString();
		sf::Text txt;
		txt.setString(stra);
		std::cout << GetIndex();
		std::cout << "\n" << "clicked:" << stra;


		mousemodule.HandleMouseClick(window, txt, functionToCall);
		menu.MakeWindow(window, GetIndex());
		window.display();
	}
}

/* register game state */
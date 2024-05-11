#include "Game.h"

#include "SettingsModule.h"
#include "FileLoader.h"

CGame::CGame()
{
	FileLoader& loader = FileLoader::Instance();
	loader.RegisterLoadingMenuProccess();

	InitWindow();
	InitMenu();

	m_pMusic = std::make_unique<sf::Music>();
	m_pText = std::make_unique<TextModule>();
	m_pSoundBar = std::make_unique<CBar>();

	if (!m_pMusic->openFromFile("audio/BGM.flac"))
		return;
	m_pMusic->setVolume(1);
	m_pMusic->play();
}

CGame::~CGame()
{
}

void CGame::Run()
{

	/* load all menu assets with start up as there are just few small ones */

	while (m_pWindow->isOpen())
	{
		UpdateDeltaTime();
		Update();
		Render();
	}
}

void CGame::InitMenu()
{
	m_pMenu = std::make_unique<CMainMenu>(1920.0f, 1080.0f);
}

void CGame::InitWindow()
{
	m_pWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Survivor. v0.0.1", sf::Style::Default);
}

void CGame::RegisterState()
{
//	this->m_stackStates.push();
}

void CGame::Render()
{
	m_pWindow->clear();
	m_pMenu->MakeWindow(*m_pWindow, m_mouse, m_sound, *m_pMusic, currentMenuIndex);
	currentMenuIndex = m_pMenu->GetLastSetIndex();
	m_currentVolumeIndex = m_pSoundBar->GetVolume();

	m_pWindow->display();
}

void CGame::Update()
{
	UpdateEvents();
}

void CGame::UpdateEvents()
{
	GameStateHandle state;
	state.test();
	m_barPosition = m_pSoundBar->GetPosition();
	std::cout << "Bar position" << m_barPosition.x << " " << m_barPosition.y <<"\n";

	while (m_pWindow->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
		{
			m_pWindow->close();
		}
		else if (m_event.type == sf::Event::MouseButtonPressed)
		{
			m_pText->HandleClickEvent(*m_pWindow, m_mouse, currentMenuIndex); // Update the index value when a button is clicked
			m_pSoundBar->OnClickBar(*m_pWindow, m_mouse, m_sound, 200, m_currentVolumeIndex);
		}
		else if (m_event.type == sf::Event::KeyPressed)
		{
			if (m_event.key.code == sf::Keyboard::Key::Up)
			{
				m_pMenu->MoveDirection(static_cast<uint16_t>(sf::Keyboard::Key::Up));
			}
			else if (m_event.key.code == sf::Keyboard::Key::Down)
			{
				m_pMenu->MoveDirection(static_cast<uint16_t>(sf::Keyboard::Key::Down));
			}
		}
	}
	m_pSoundBar->UpdateSound(m_barPosition);
}

void CGame::UpdateDeltaTime()
{
	m_fDeltaTime = m_deltaTimeClock.restart().asSeconds();
}


/* register game state */
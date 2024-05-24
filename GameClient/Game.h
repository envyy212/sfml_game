#pragma once
#include "../TheCore/pch.h"

#include "MainMenu.h"
#include "SoundModule.h"
#include "TextModule.h"
#include "uiBar.h"

#include <TheCore/GameStateHandle.h>

#include <stack>

class CGame
{
public:
	CGame();
	~CGame();

	void Run();

	inline const uint16_t GetWidth() const { return m_sWidth; }
	inline const uint16_t GetHeight() const { return m_sHeight; }

	inline void SetWidth(uint16_t Width) { m_sWidth = Width; }
	inline void SetHeight(uint16_t Height) { m_sHeight = Height; }
	inline void SetIndex(uint16_t index) { m_selectedIndex = index; }
	inline const uint16_t GetIndex() const { return m_selectedIndex; }

public: 
	void RegisterState();
	void Render();
	void Update();
	void UpdateEvents();
	void UpdateDeltaTime();

	void InitWindow();
	void InitMenu();

	std::stack<GameStateHandle*> m_stackStates;
private:
	sf::Clock m_deltaTimeClock;
	float m_fDeltaTime;

	std::unique_ptr<CMainMenu> m_pMenu; // Explicitly specify the type here

	std::unique_ptr<TextModule> m_pText;
	std::unique_ptr<sf::RenderWindow> m_pWindow;
	std::unique_ptr<sf::Music> m_pMusic;
	std::unique_ptr<CBar> m_pSoundBar;

	/* sf:: */


	sf::Mouse m_mouse;
	sf::Event m_event;
	sf::Sound m_sound;
private:
	/* window and menu */

	uint16_t m_sHeight;
	uint16_t m_sWidth;

	uint16_t m_selectedIndex;
	uint16_t currentMenuIndex;

	float m_currentVolumeIndex;
private:
	sf::Vector2f m_barPosition;
};

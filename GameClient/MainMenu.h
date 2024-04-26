#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <windows.h>
#include <chrono>
#include <SFML/Audio.hpp>

typedef struct MainMenu
{
	static const int textMaxItems = 5;
	std::string formattedTime;
	uint16_t selectedIndex;
	sf::Font m_font;
	sf::Font m_timeFont;
	sf::Text m_text[textMaxItems];
	bool displayMilliseconds;
	std::chrono::time_point<std::chrono::system_clock> displayMillisecondsStartTime;
}TMainMenu;

class CMainMenu
{
public:
	CMainMenu(float Width, float Height);
	~CMainMenu() = default;

	uint16_t GetSelectedItemIndex();
	void SetSelectedItemIndex(uint16_t ItemIndex);

	void MoveDirection(uint16_t Direction);
	void MakeWindow(sf::RenderWindow& window);
	std::vector<std::string> menuItemsVec;
	void GetDisplayedTimeHandle();
private:
	std::unique_ptr<TMainMenu> m_pMenu = std::make_unique<TMainMenu>();
	sf::Text m_versionText;
	sf::Text m_timeText;
	sf::Text m_millisecondsText;
	sf::Text m_mainText;

	sf::SoundBuffer m_buffer;
	sf::SoundBuffer m_buff;
	sf::Sound m_sound;
	sf::Sound m_soundTick;
};

#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <windows.h>
#include <chrono>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>
#include "SoundManager.h"

enum ePageState
{
	PAGE_STATE_DEFAULT,
	PAGE_STATE_MAIN_MENU,
	PAGE_STATE_PLAY,
	PAGE_STATE_SETTINGS,
	PAGE_STATE_RANKING,
	PAGE_STATE_ABOUT,
	PAGE_STATE_EXIT
};

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

typedef struct Options
{
	static const int optionTextMaxItems = 3;
	sf::Text optionsText[optionTextMaxItems];
	uint16_t selectedOptionIndex;
}TOptions;

typedef struct About
{
	static const int optionTextAboutMaxItems = 10;
	sf::Text textAbout[optionTextAboutMaxItems];
}TAbout;

typedef struct PlayerRanking
{
	uint32_t dwID;
	std::vector<std::string> playerNameStr;
	uint64_t llPlayerScore;

	static const int rankingMaxRows = 9;
	sf::Text textRankingRow[rankingMaxRows];
}TPlayerRanking;

class CMainMenu
{
public:
	CMainMenu(float Width, float Height);
	~CMainMenu() = default;

	uint16_t GetSelectedItemIndex();
	uint16_t GetSelectedPageIndex();
	void SetSelectedItemIndex(uint16_t ItemIndex);

	void MoveDirection(uint16_t Direction);
	void MakeWindow(sf::RenderWindow& window, uint16_t PageIndex);
	void GetDisplayedTimeHandle();
	void DisplayMenuByPageIndex(sf::RenderWindow& window, uint16_t PageIndex);
	void BuildMenu(sf::RenderWindow& window);

	void BuildSettings(sf::RenderWindow& window);
	void BuildAbout(sf::RenderWindow& window);
	void BuildRankingData(sf::RenderWindow& window);
	void BuildRanking(sf::RenderWindow& window);
	void BuildBackgroundText(float Width, float Height);
private:
	std::unique_ptr<TMainMenu> m_pMenu = std::make_unique<TMainMenu>();
	std::unique_ptr<TOptions> m_pOptions = std::make_unique<TOptions>();
	std::unique_ptr<TAbout> m_pAbout = std::make_unique<TAbout>();
	std::unique_ptr<TPlayerRanking> m_pPlayerRanking = std::make_unique<TPlayerRanking>();
	TPlayerRanking pRanking;

	std::vector<std::string> menuItemsVec;
	sf::Text m_versionText;
	sf::Text m_timeText;
	sf::Text m_millisecondsText;
	sf::Text m_mainText;

	sf::SoundBuffer m_buffer;
	sf::SoundBuffer m_buff;
	sf::Sound m_sound;
	sf::Sound m_soundTick;
	CSoundManager soundMgr;
private:
	std::vector<std::string> m_rankingTextVec;
	sf::Texture image;
	sf::Sprite imageSprite;

	uint16_t m_pageIndex;
	std::vector<std::string> m_optionsTextVec;
	std::vector<std::string> m_aboutTextVec;
	sf::Text m_RankingHeaderText[3];
	std::map<uint64_t, TPlayerRanking*> playerRankingMap;
};

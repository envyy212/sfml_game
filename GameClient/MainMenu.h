#pragma once
#include <map>
#include <windows.h>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>

#include "SoundModule.h"
#include "TextModule.h"
#include "Bar.h"

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
	void MakeWindow(sf::RenderWindow& window,sf::Mouse& mouse, sf::Sound& sound, sf::Music& music, uint16_t PageIndex);
	void GetDisplayedTimeHandle();
	void DisplayMenuByPageIndex(sf::RenderWindow& window,sf::Mouse& mouse,sf::Sound& sound,sf::Music& music, uint16_t PageIndex);
	void BuildMenu(sf::RenderWindow& window);

	void BuildSettings(sf::RenderWindow& window, sf::Mouse& mouse, sf::Sound& sound, sf::Music& music);
	void BuildAbout(sf::RenderWindow& window);
	void BuildRankingData(sf::RenderWindow& window);
	void BuildRanking(sf::RenderWindow& window);
	void BuildBackgroundText(sf::RenderWindow& window);
	void BuildVersionText(sf::RenderWindow& window);

	void SetIndex(uint16_t index) { lastSetIndex = index; }
	uint16_t GetLastSetIndex() const;

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

	std::unique_ptr<CSoundModule> m_pSoundModule;
private:
	CBar m_Bar; 
	CBar m_MusicBar;

	uint16_t lastSetIndex;
	uint16_t lastSetSubIndex;

	std::vector<std::string> m_rankingTextVec;
	sf::Texture image;
	sf::Texture img1;
	sf::Texture img2;
	sf::Texture img3;
	sf::Texture img4;

	sf::Sprite imageSprite;
	sf::Sprite imageSprite1;
	sf::Sprite imageSprite2;
	sf::Sprite imageSprite3;
	sf::Sprite imageSprite4;


	sf::Mouse mouse;
	sf::Keyboard keyboard;
	float m_centerX;
	float m_centerY;

	uint16_t m_pageIndex;
	std::vector<std::string> m_optionsTextVec;
	std::vector<std::string> m_aboutTextVec;
	sf::Text m_RankingHeaderText[3];
	std::map<uint64_t, TPlayerRanking*> playerRankingMap;
	std::unique_ptr<TextModule> m_pTextModule;
};


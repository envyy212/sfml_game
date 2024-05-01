#include "MainMenu.h"
#include "Log.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include "MouseModule.h"
#include "Button.h"


CMainMenu::CMainMenu(float Width, float Height)
{
	menuItemsVec = { "Play", "Options", "Ranking", "About", "Exit" };
	m_optionsTextVec = { "Sound", "Background music", "Resolution"};
	m_rankingTextVec = { "Rank", "Name", "Score" };
	m_aboutTextVec = { "Survivor. Game"
	, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
		"Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. ",
		"Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.",
		"Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
		"Lorem Ipsum is simply dummy text of the printing and typesetting industry.",
		"Lorem Ipsum has been the industry's standard dummy text ever since the 1500s,",
		"when an unknown printer took a galley of type and scrambled it to make a type specimen book.",
		"It has survived not only five centuries, ",
		"but also the leap into electronic typesetting, remaining essentially unchanged."};

	txtModule = new TextModule;

//	PlayerRanking* m_pPlayerRanking = new PlayerRanking(); // Allocate memory for a PlayerRanking instance
//	std::map<unsigned int, PlayerRanking*> playerRankingMap;

	if (!image.loadFromFile("ui/Default/Divider Fade/divider-fade-001.png"))
		return;

	if (!img2.loadFromFile("ui/Default/Divider Line/Divider_Line_001.png"))
		return;

	if (!img1.loadFromFile("ui/Default/Divider Fade/divider-fade-001.png"))
		return;

	imageSprite2.setTexture(img2);
	imageSprite2.setScale(sf::Vector2f(4.5f, 1.0f));
	imageSprite2.setPosition(sf::Vector2f(Width / 2.4 - imageSprite2.getLocalBounds().width / 2, Height / 5 - imageSprite2.getLocalBounds().height / 2));

	imageSprite.setTexture(image);
	imageSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	imageSprite.setPosition(sf::Vector2f(Width/1.50 - imageSprite.getLocalBounds().width / 2, Height/ 4.53 - imageSprite.getLocalBounds().height/2));

	imageSprite1.setTexture(img1);
	imageSprite1.setScale(sf::Vector2f(1.0f, 1.0f));
	imageSprite1.setPosition(sf::Vector2f(Width / 2.65 - imageSprite1.getLocalBounds().width / 2, Height / 5 - imageSprite.getLocalBounds().height / 2));
	imageSprite.setRotation(180);

	/* always displayed items in constructor - the rest is handled by page states */

	/* page index 0 reserved for constructor - default state */
	m_pOptions->selectedOptionIndex = 1;
}

void CMainMenu::MakeWindow(sf::RenderWindow& window, uint16_t PageIndex)
{
	DisplayMenuByPageIndex(window, PageIndex);
	/* always display */
	GetDisplayedTimeHandle();
	BuildBackgroundText(window);
	BuildVersionText(window);
	window.draw(m_timeText);

	window.draw(m_millisecondsText);


	window.draw(imageSprite);
	window.draw(imageSprite1);
	window.draw(imageSprite2);
	soundMgr.RemoveReplayedSound();
}

void CMainMenu::DisplayMenuByPageIndex(sf::RenderWindow& window, uint16_t PageIndex)
{
	m_pOptions->selectedOptionIndex = PageIndex;//arrow movement related

	switch (PageIndex)
	{
	case PAGE_STATE_MAIN_MENU:
		BuildMenu(window);
		break;
	case PAGE_STATE_PLAY:
		break;
	case PAGE_STATE_SETTINGS:
		BuildSettings(window);
		break;
	case PAGE_STATE_RANKING:
		BuildRanking(window);
		break;
	case PAGE_STATE_ABOUT:
		BuildAbout(window);
		break;
	case PAGE_STATE_EXIT:
		window.close();
		break;
	}
}

void CMainMenu::BuildMenu(sf::RenderWindow& window)
{
	MouseModule mousemodule;
	uint16_t index = GetLastSetIndex();

	for (int i = 0; i < menuItemsVec.size(); i++)
	{
		float centerX = (window.getSize().x / 2.0f) - (txtModule->GetBoundingBoxFromStrings(menuItemsVec).width / 2.0f);
		float centerY = (window.getSize().y / 3.0f + window.getSize().y / 18.0f);

		txtModule->WriteText(window, sf::Vector2f(centerX, centerY),
			TextProperties::TEXT_FONT_ARIAL, TextProperties::TEXT_BUTTON, menuItemsVec[i].c_str(), TextProperties::TEXT_LOWER_BIG, 0, i * 70);

		sf::Text txt;
		txt.setString(menuItemsVec[i].c_str());

		txtModule->HandleClickEvent(window, mouse, index);
	}
	SetIndex(index);
}

void CMainMenu::BuildSettings(sf::RenderWindow& window)
{
	CButton button;

	uint16_t mainMenuIndex = GetLastSetIndex();

	for (int i = 0; i < m_optionsTextVec.size(); i++)
	{
		float centerX = (window.getSize().x / 2.0f) - (txtModule->GetBoundingBoxFromStrings(menuItemsVec).width / 2.0f);
		float centerY = (window.getSize().y / 3 + window.getSize().y / 20);

		txtModule->WriteText(window, sf::Vector2f(centerX, centerY),
			TextProperties::TEXT_FONT_ARIAL, TextProperties::TEXT_NORMAL, m_optionsTextVec[i].c_str(), TextProperties::TEXT_MEDIUM, 0, i*70);

		txtModule->HandleClickEvent(window, mouse, mainMenuIndex);
	}

	float centerBtnX = window.getSize().x / 2.7f;
	float centerBtnY = window.getSize().y / 2.23f;

	button.MakeButton(window, sf::Vector2f(centerBtnX, centerBtnY), 0, 0,1.0f, 1.0f);
	button.HandleClickEvent(window, mouse, mainMenuIndex);

	SetIndex(mainMenuIndex);
}

void CMainMenu::BuildRanking(sf::RenderWindow& window)
{
	CButton button;

	for (int i = 0; i < m_rankingTextVec.size(); i++)
	{
		float centerX = (window.getSize().x / 3.0f);
		float centerY = window.getSize().y / 3.5f;

		txtModule->WriteText(window, sf::Vector2f(centerX, centerY),
			TextProperties::TEXT_FONT_ARIAL, TextProperties::TEXT_NORMAL, m_rankingTextVec[i].c_str(), TextProperties::TEXT_MEDIUM, i*319, 0);

		txtModule->PerformTextEventByMouseAction(window, mouse, keyboard);
	}
	uint16_t index = GetLastSetIndex();

	float centerBtnX = window.getSize().x / 2.7f;
	float centerBtnY = window.getSize().y / 2.23f;

	button.MakeButton(window, sf::Vector2f(centerBtnX, centerBtnY), 0, 0, 1.0f, 1.0f);
	button.HandleClickEvent(window, mouse, index);
	SetIndex(index);

	BuildRankingData(window);
}

/* rewrite after - trash */
void CMainMenu::BuildRankingData(sf::RenderWindow& window)
{
	PlayerRanking* pRanking = new PlayerRanking(); // Allocate memory for each instance of PlayerRanking

	for (int i = 0; i < pRanking->rankingMaxRows; ++i)
	{
		pRanking->dwID = i;
		pRanking->llPlayerScore = 12000;
		pRanking->playerNameStr.push_back("NoName" + std::to_string(i)); // Convert integer to string before concatenation
		playerRankingMap.insert(std::make_pair(pRanking->dwID, pRanking));
	}

	for (auto& it : playerRankingMap)
	{
		m_pPlayerRanking->textRankingRow[it.first].setCharacterSize(24);
		m_pPlayerRanking->textRankingRow[it.first].setFont(m_pMenu->m_font);
		m_pPlayerRanking->textRankingRow[it.first].setFillColor(sf::Color::White);

		std::string rankString = std::to_string(it.first + 1);

		std::stringstream ss;
		ss << rankString << std::setw(35) << it.second->playerNameStr[m_pPlayerRanking->playerNameStr.size()] << std::setw(35) << it.second->llPlayerScore;

		m_pPlayerRanking->textRankingRow[it.first].setString(ss.str());

		m_pPlayerRanking->textRankingRow[it.first].setPosition(
			sf::Vector2f((window.getSize().x / 2.0f) - m_pPlayerRanking->textRankingRow[it.first].getLocalBounds().width / 2,
				window.getSize().y / 2.5 + window.getSize().y / 20 * it.first)
		);

		window.draw(m_pPlayerRanking->textRankingRow[it.first]);
	}
}

void CMainMenu::BuildAbout(sf::RenderWindow& window)
{
	CButton button;

	for (int i = 0; i < m_aboutTextVec.size(); i++)
	{
		float centerX = (window.getSize().x / 2.0f) - (txtModule->GetBoundingBoxFromStrings(m_aboutTextVec).width / 2.0f);
		float centerY = window.getSize().y / 3 + window.getSize().y / 20 * i;

		txtModule->WriteText(window, sf::Vector2f(centerX, centerY),
			TextProperties::TEXT_FONT_ARIAL, TextProperties::TEXT_NORMAL, m_aboutTextVec[i].c_str(), TextProperties::TEXT_SMALL, 0, 0);
	}
	uint16_t mainMenuIndex = GetLastSetIndex();

	float centerBtnX = window.getSize().x / 4.7f;
	float centerBtnY = window.getSize().y / 2.23f;

	button.MakeButton(window, sf::Vector2f(centerBtnX, centerBtnY), 0, 0, 1.0f, 1.0f);
	button.HandleClickEvent(window, mouse, mainMenuIndex);
	SetIndex(mainMenuIndex);

	BuildRankingData(window);
}

void CMainMenu::BuildBackgroundText(sf::RenderWindow& window)
{
	/*app name*/
	std::string applicationName = "Survivor.";

	m_centerX = window.getSize().x / 2.0f;
	m_centerY = window.getSize().y / 8;

	txtModule->WriteText(window, sf::Vector2f(m_centerX, m_centerY),
	TextProperties::TEXT_FONT_ARIAL, TextProperties::TEXT_NORMAL, applicationName.c_str(), TextProperties::TEXT_LARGE, 0, 0);
	/*app name*/
}

void CMainMenu::BuildVersionText(sf::RenderWindow& window)
{
	/*version*/
	std::string version = "2024-04-266:42 v0.0.1 - https://github.com/xd12564/";
	m_centerX = window.getSize().x / 8.0f;
	m_centerY = window.getSize().y / 1.015;

	txtModule->WriteText(window, sf::Vector2f(m_centerX, m_centerY),
		TextProperties::TEXT_FONT_ARIAL, TextProperties::TEXT_NORMAL, version.c_str(), TextProperties::TEXT_EXTRA_SMALL, 0, 0);
	/*version*/
}

void CMainMenu::GetDisplayedTimeHandle()
{
	if (!m_pMenu->m_timeFont.loadFromFile("fonts/Fiendish.ttf"))
	{
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "CMainMenu::CMainMenu could not load font.");
	}

	static int previousMinute = -1;

	m_timeText.setFont(m_pMenu->m_timeFont);
	m_timeText.setCharacterSize(48);
	m_timeText.setFillColor(sf::Color::Red);
	m_timeText.setPosition(1920 / 1.7, 1080 / 1.1);

	m_millisecondsText.setFont(m_pMenu->m_timeFont);
	m_millisecondsText.setCharacterSize(36);
	m_millisecondsText.setFillColor(sf::Color::Red);
	m_millisecondsText.setPosition(1920 / 1.080, 1080 / 1.085);
	 
	std::time_t currentTime = std::time(nullptr);
	std::tm* timeInfo = std::localtime(&currentTime);
	std::stringstream timeStream;

	// Update the formatted time with milliseconds
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
	timeStream << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
	m_pMenu->formattedTime = timeStream.str();

	auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - m_pMenu->displayMillisecondsStartTime).count();

	if (previousMinute == -1)
		previousMinute = timeInfo->tm_min;

	if (previousMinute != timeInfo->tm_min)
	{
		soundMgr.PlaySounds(SoundEffect::SOUND_TIME_BOOM);
		soundMgr.PlaySounds(SoundEffect::SOUND_CLOCK_TICK);
		previousMinute = timeInfo->tm_min;
		m_pMenu->displayMillisecondsStartTime = std::chrono::system_clock::now();
	}

	if (elapsedSeconds <= 3)
	{
		std::stringstream millisecondsStream;
		millisecondsStream << ":" << std::setfill('0') << std::setw(3) << milliseconds;
		m_timeText.setString(timeStream.str());
		m_millisecondsText.setString(millisecondsStream.str());
	}
	else
	{
		m_timeText.setString(timeStream.str());
		m_millisecondsText.setString("");
	}
}

uint16_t CMainMenu::GetLastSetIndex()
{

	if (!lastSetIndex)
		return 1;
	return lastSetIndex;
}

/* move menu with arrows related */
uint16_t CMainMenu::GetSelectedPageIndex()
{
	return m_pOptions->selectedOptionIndex;
}

uint16_t CMainMenu::GetSelectedItemIndex()
{
	return m_pMenu->selectedIndex;
}

void CMainMenu::SetSelectedItemIndex(uint16_t ItemIndex)
{
	m_pMenu->selectedIndex = ItemIndex;
}
/* move menu with arrows related */

/* rewrite -> move menu with keys implementation */
void CMainMenu::MoveDirection(uint16_t Direction)
{
	switch (Direction)
	{
	case sf::Keyboard::Key::Up:
		if (m_pMenu->selectedIndex -1 >= 0)
		{
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.0f);
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::White);
			m_pMenu->selectedIndex--;
			SetSelectedItemIndex(m_pMenu->selectedIndex);
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.65f);
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::Yellow);
			if (m_pMenu->selectedIndex == -1)
			{
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.0f);
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::White);
				m_pMenu->selectedIndex = 4;
				SetSelectedItemIndex(m_pMenu->selectedIndex);

				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.65f);
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::Yellow);
			}
		}
		break;
	case sf::Keyboard::Key::Down:
		if (m_pMenu->selectedIndex + 1 <= m_pMenu->textMaxItems)
		{
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.0f);
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::White);
			m_pMenu->selectedIndex++;
			SetSelectedItemIndex(m_pMenu->selectedIndex);

			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.65f);
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::Yellow);
			if (m_pMenu->selectedIndex == 5)
			{
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.0f);
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::White);
				m_pMenu->selectedIndex = 0;
				SetSelectedItemIndex(m_pMenu->selectedIndex);
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.65f);
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::Yellow);
			}
		}
		break;
	}
}
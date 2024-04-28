#include "MainMenu.h"
#include "Log.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include "SoundManager.h"

CMainMenu::CMainMenu(float Width, float Height)
{
	menuItemsVec = { "Play", "Options", "Ranking", "About", "Exit" };
	m_optionsTextVec = { "Sound", "Background music", "Resolution"};
	m_rankingTextVec = { "Ranking", "Rank", "Name", "Score" };
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

//	PlayerRanking* m_pPlayerRanking = new PlayerRanking(); // Allocate memory for a PlayerRanking instance
//	std::map<unsigned int, PlayerRanking*> playerRankingMap;


	if (!m_buffer.loadFromFile("audio/time_boom.flac"))
		return;

	if (!m_buff.loadFromFile("audio/clock_tick.flac"))
		return;
	m_sound.setBuffer(m_buffer);
	m_soundTick.setBuffer(m_buff);

	/* always displayed items in constructor - the rest is handled by page states */

	/* page index 0 reserved for constructor - default state */
	m_pOptions->selectedOptionIndex = 1;
}

void CMainMenu::DisplayMenuByPageIndex(sf::RenderWindow& window, uint16_t PageIndex, float Width, float Height)
{
	m_pOptions->selectedOptionIndex = PageIndex;

	switch (PageIndex)
	{
	case PAGE_STATE_MAIN_MENU:
		BuildMenu(window);
		break;
	case PAGE_STATE_PLAY:
		break;
	case PAGE_STATE_SETTINGS:
		BuildSettings(window, Width, Height);
		break;
	case PAGE_STATE_RANKING:
		BuildRanking(window);
		break;
	case PAGE_STATE_ABOUT:
		BuildAbout(window);
		break;
	case PAGE_STATE_EXIT:
		break;
	}
}

void CMainMenu::BuildMenu(sf::RenderWindow& window)
{
	if (!m_pMenu->m_font.loadFromFile("fonts/arial.ttf"))
	{
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "CMainMenu::CMainMenu could not load font.");
	}

	//if (m_UpdateAvailable)
//
//	menuItemsVec.push_back("Patch notes");
//
	for (int i = 0; i < menuItemsVec.size(); i++)
	{
		if (i == 0)
		{
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.65f);
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::Yellow);
		}
		m_pMenu->m_text[i].setFont(m_pMenu->m_font);
		m_pMenu->m_text[i].setFillColor(sf::Color::White);
		m_pMenu->m_text[i].setString(menuItemsVec[i]);
		m_pMenu->m_text[i].setPosition(sf::Vector2f((window.getSize().x / 2.0f) - m_pMenu->m_text[i].getLocalBounds().width / 2, window.getSize().y / 3 + window.getSize().y / 16 * i));

		window.draw(m_pMenu->m_text[i]);
	}
}

void CMainMenu::BuildSettings(sf::RenderWindow& window, float Width, float Height)
{
	for (int i = 0; i < m_optionsTextVec.size(); ++i)
	{
		m_pOptions->optionsText[i].setFont(m_pMenu->m_font);
		m_pOptions->optionsText[i].setFillColor(sf::Color::White);
		m_pOptions->optionsText[i].setString(m_optionsTextVec[i]);
		m_pOptions->optionsText[i].setPosition(sf::Vector2f((Width / 2.0f) - m_pOptions->optionsText[i].getLocalBounds().width / 2, Height / 3 + Height / 16 * i));

		window.draw(m_pOptions->optionsText[i]);
	}
}

void CMainMenu::BuildRanking(sf::RenderWindow& window)
{

	for (int i = 0; i < m_rankingTextVec.size(); ++i)
	{
		m_RankingHeaderText[i].setCharacterSize(26);
		m_RankingHeaderText[i].setFont(m_pMenu->m_font);
		m_RankingHeaderText[i].setFillColor(sf::Color::White);
		m_RankingHeaderText[i].setString(m_rankingTextVec[i]);
		if(i == 0)
			m_RankingHeaderText[i].setPosition(sf::Vector2f(((window.getSize().x / 7)) + window.getSize().x / 3, window.getSize().y / 6 + window.getSize().y / 15));
		else
			m_RankingHeaderText[i].setPosition(sf::Vector2f(((window.getSize().x / 7) * i) + window.getSize().x / 5, window.getSize().y / 5 + window.getSize().y / 15));

		window.draw(m_RankingHeaderText[i]);
	}
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
				window.getSize().y / 3 + window.getSize().y / 20 * (it.first))
		);

		window.draw(m_pPlayerRanking->textRankingRow[it.first]);
	}
}

void CMainMenu::BuildAbout(sf::RenderWindow& window)
{
	for (int i = 0; i < m_aboutTextVec.size(); ++i)
	{
		m_pAbout->textAbout[i].setFont(m_pMenu->m_font);
		m_pAbout->textAbout[i].setCharacterSize(18);

		m_pAbout->textAbout[i].setFillColor(sf::Color::White);
		m_pAbout->textAbout[i].setString(m_aboutTextVec[i]);
		m_pAbout->textAbout[i].setPosition(sf::Vector2f((window.getSize().x / 2.0f) - m_pAbout->textAbout[i].getLocalBounds().width / 2, window.getSize().y / 3 + window.getSize().y / 20 * i));
		window.draw(m_pAbout->textAbout[i]);
	}
}

void CMainMenu::BuildBackgroundText(float Width, float Height)
{
	m_mainText.setFont(m_pMenu->m_font);
	m_mainText.setCharacterSize(72);
	m_mainText.setFillColor(sf::Color::White);
	m_mainText.setString("Survivor.");
	m_mainText.setPosition(sf::Vector2f((Width / 2.0f) - m_mainText.getLocalBounds().width / 2, Height / 8));

	m_versionText.setFont(m_pMenu->m_font);
	m_versionText.setCharacterSize(12);
	m_versionText.setFillColor(sf::Color::White);
	m_versionText.setString("2024-04-266:42 v0.0.1 - https://github.com/xd12564/");
	m_versionText.setPosition(m_versionText.getLocalBounds().width - m_versionText.getLocalBounds().width / 1.2, Height - m_versionText.getLocalBounds().height * 4);
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

	// Get current Windows time
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
		m_sound.setVolume(100);
		m_sound.play();

		m_soundTick.setVolume(100);
		m_soundTick.play();
		previousMinute = timeInfo->tm_min;
		m_pMenu->displayMillisecondsStartTime = std::chrono::system_clock::now(); // Start time for displaying milliseconds
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
		m_timeText.setString(timeStream.str()); // Display time without milliseconds
		m_millisecondsText.setString(""); // Clear milliseconds text
	}
}

void CMainMenu::MakeWindow(sf::RenderWindow& window, uint16_t PageIndex)
{
	DisplayMenuByPageIndex(window, PageIndex, window.getSize().x, window.getSize().y);

	/* always display */
	GetDisplayedTimeHandle();
	BuildBackgroundText(window.getSize().x, window.getSize().y);
	window.draw(m_timeText);
	window.draw(m_versionText);
	window.draw(m_mainText);
	window.draw(m_millisecondsText);
}

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

/* fix this shit later */
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
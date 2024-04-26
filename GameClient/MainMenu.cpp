#include "MainMenu.h"
#include "Log.h"
#include <iomanip>
#include <ctime>
#include <sstream>

CMainMenu::CMainMenu(float Width, float Height)
{
	if (!m_pMenu->m_font.loadFromFile("arial.ttf"))
	{
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "CMainMenu::CMainMenu could not load font.");
	}

	menuItemsVec = {"Play", "Options", "Ranking", "About", "Exit"};
	if (!m_buffer.loadFromFile("time_boom.flac"))
		return;

	if (!m_buff.loadFromFile("clock_tick.flac"))
		return;
	m_sound.setBuffer(m_buffer);
	m_soundTick.setBuffer(m_buff);
	//if (m_UpdateAvailable)
	//
	//	menuItemsVec.push_back("Patch notes");
	//
	m_mainText.setFont(m_pMenu->m_font);
	m_mainText.setCharacterSize(72);
	m_mainText.setFillColor(sf::Color::White);
	m_mainText.setString("I still dont know yet...");
	m_mainText.setPosition(sf::Vector2f((Width / 2.0f) - m_mainText.getLocalBounds().width / 2, Height / 8));

	m_versionText.setFont(m_pMenu->m_font);
	m_versionText.setCharacterSize(12);
	m_versionText.setFillColor(sf::Color::White);
	m_versionText.setString("2024-04-266:42 v0.0.1 - https://github.com/xd12564/");
	m_versionText.setPosition(m_versionText.getLocalBounds().width - m_versionText.getLocalBounds().width / 1.2, Height - m_versionText.getLocalBounds().height * 4);

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
		m_pMenu->m_text[i].setPosition(sf::Vector2f((Width / 2.0f) - m_pMenu->m_text[i].getLocalBounds().width / 2, Height / 3 + Height / 16 * i));
	}
}

void CMainMenu::GetDisplayedTimeHandle()
{
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
		previousMinute = timeInfo->tm_min; // Set previousMinute for the first time

	if (previousMinute != timeInfo->tm_min)
	{
		m_sound.setVolume(100);
		m_sound.play();

		m_soundTick.setVolume(100);
		m_soundTick.play();
		previousMinute = timeInfo->tm_min; // Update previousMinute when a new minute starts
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

void CMainMenu::MakeWindow(sf::RenderWindow& window)
{
	for (auto i = 0; i < m_pMenu->textMaxItems; ++i)
	{
		window.draw(m_pMenu->m_text[i]);
	}
	if (!m_pMenu->m_timeFont.loadFromFile("Fiendish.ttf"))
	{
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "CMainMenu::CMainMenu could not load font.");

	}

	GetDisplayedTimeHandle();
	window.draw(m_timeText);
	window.draw(m_versionText);
	window.draw(m_mainText);
	window.draw(m_millisecondsText);
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
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.65f);
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::Yellow);
			if (m_pMenu->selectedIndex == -1)
			{
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.0f);
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::White);
				m_pMenu->selectedIndex = 4;
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
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.65f);
			m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::Yellow);
			if (m_pMenu->selectedIndex == 5)
			{
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.0f);
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::White);
				m_pMenu->selectedIndex = 0;
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineThickness(0.65f);
				m_pMenu->m_text[m_pMenu->selectedIndex].setOutlineColor(sf::Color::Yellow);
			}
		}
		break;
	}
}
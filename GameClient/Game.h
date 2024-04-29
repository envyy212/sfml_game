#pragma once
#include <SFML/Window.hpp>
#include <iostream>
#include "SoundManager.h"

class CGame
{
public:
	CGame()
	{
		m_bState = false;
		m_sHeight = static_cast<uint16_t>(WindowConfig::WINDOW_MAX_HEIGHT);
		m_sWidth = static_cast<uint16_t>(WindowConfig::WINDOW_MAX_WIDTH);
	}
	~CGame()
	{

	}

	void Run();
	void ProcessSettingsInput();

	inline uint16_t GetWidth() { return m_sWidth; }
	inline uint16_t GetHeight() { return m_sHeight; }

	inline void SetWidth(uint16_t Width) { m_sWidth = Width; }
	inline void SetHeight(uint16_t Height) { m_sHeight = Height; }
	void SetIndex(uint16_t index) { m_selectedIndex = index; }
	uint16_t GetIndex() { return m_selectedIndex; }
	/* mby overload this */
	enum class WindowConfig
	{
		WINDOW_MAX_WIDTH = 1920,
		WINDOW_MAX_HEIGHT = 1080,
	};
private:
	uint16_t m_selectedIndex;
	bool m_bState;
	uint16_t m_sHeight;
	uint16_t m_sWidth;
};

#pragma once

#include "ResourceIdentifier.h"
#include "ResourceHolder.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Text.hpp>

#include "SoundModule.h"

#include <unordered_map>


class TextModule : private sf::NonCopyable
{
public:
	TextModule();
	~TextModule() = default;

	void WriteText(sf::RenderWindow& window, sf::Vector2f posVec, TextProperties::eTextFont TextFormat, TextProperties::eTextType TextType, const char* TextString, TextProperties::eTextSize TextSize, float xStep, float yStep);
	void OnOverText(sf::RenderWindow& window,sf::Mouse mouse);
	void OnClickText(sf::RenderWindow& window,sf::Mouse mouse);
	void OnDefaultText(sf::RenderWindow& window,sf::Mouse mouse);

	sf::FloatRect GetBoundingBoxFromStrings(const std::vector<std::string>& textStrings);
	sf::FloatRect GetBoundingBoxFromStrings(const std::string& textStr);

	void SetClickedText(sf::Text& clickedText);
	inline sf::Text GetClickedText() {
		return m_clickedText;
	}

	void HandleClickEvent(sf::RenderWindow& window, sf::Mouse mouse, uint16_t& index);

	void PerformTextEventByMouseAction(sf::RenderWindow& window, sf::Mouse mouse, sf::Keyboard keyboard);
private:

	std::unordered_map<std::string, uint16_t>m_textIndexMap;

	std::unique_ptr<CSoundModule> m_pSoundModule;

	TextHolder m_FontBuffers;
	sf::Font m_font;
	std::vector<sf::Text> m_TextVec;
	sf::Text m_text;

	sf::Text m_clickedText;

	bool m_IsClickable;
};
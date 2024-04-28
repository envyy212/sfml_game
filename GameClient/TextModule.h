#pragma once

#include "ResourceIdentifier.h"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Text.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"

class TextModule : private sf::NonCopyable
{
public:
	TextModule();
	~TextModule() = default;

	void WriteText(TextProperties::eTextFont TextFormat, std::string& TextString, TextProperties::eTextSize TextSize);
	void OnOverText(sf::Mouse mouse);
	void PerformActionByTextState(TextProperties::eTextState textState, sf::Mouse mouse);
	void OnClickText(sf::Mouse mouse);
	void OnDefaultText(sf::Mouse mouse);

	sf::Vector2i GetTextPosition(sf::Text& text);

	//	void FreeTextVector();
private:
	TextHolder m_FontBuffers;
	std::vector<sf::Text> m_TextVec;
	sf::Text m_text;
	TextProperties::eTextState textState;
	bool m_IsClickable;
};
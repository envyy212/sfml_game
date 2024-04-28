#include "TextModule.h"

TextModule::TextModule()
	: m_FontBuffers(), m_TextVec()
{
	m_FontBuffers.load(TextProperties::TEXT_FONT_ARIAL, "fonts/arial.ttf");
	m_FontBuffers.load(TextProperties::TEXT_FONT_FIENDISH, "fonts/Fiendish.ttf");
	m_FontBuffers.load(TextProperties::TEXT_FONT_TUFFY, "fonts/tuffy.ttf");
}

void TextModule::WriteText(TextProperties::eTextFont TextFormat, std::string& TextString, TextProperties::eTextSize TextSize)
{
	m_TextVec.push_back(sf::Text());
	sf::Text& m_text = m_TextVec.back();
	 
	m_text.setString(TextString);
	m_text.setCharacterSize(TextSize);
}

sf::Vector2i TextModule::GetTextPosition(sf::Text& text)
{
	return static_cast<sf::Vector2i>(text.getLocalBounds().getPosition());
}

void TextModule::OnOverText(sf::Mouse mouse)
{
	if (mouse.getPosition() == GetTextPosition(m_text))
	{
		m_text.setOutlineThickness(0.65f);
		m_text.setOutlineColor(sf::Color::Yellow);
	}
}

void TextModule::OnDefaultText(sf::Mouse mouse)
{
	if (mouse.getPosition() != GetTextPosition(m_text))
	{
		m_text.setOutlineThickness(0.0f);
		m_text.setOutlineColor(sf::Color::White);
	}
}

void TextModule::PerformActionByTextState(TextProperties::eTextState textState, sf::Mouse mouse)
{
	switch (textState)
	{
	case TextProperties::TEXT_STATE_DEFAULT:
		OnDefaultText(mouse);
		break;
	case TextProperties::TEXT_STATE_OVER:
		OnOverText(mouse);
		break;
	case TextProperties::TEXT_STATE_CLICKED:
		OnClickText(mouse);
		break;
	}
}

void TextModule::OnClickText(sf::Mouse mouse)
{
	if (mouse.getPosition() == GetTextPosition(m_text))
	{
		m_text.setOutlineThickness(0.85f);
		m_text.setOutlineColor(sf::Color::Yellow);
	}
}
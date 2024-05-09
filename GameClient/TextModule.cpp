#include <iostream>
#include <functional>

#include "TextModule.h"
#include "FileLoader.h"


TextModule::TextModule()
	: m_FontBuffers(), m_TextVec(), m_text(), m_IsClickable()
{
	m_textIndexMap = {
		{"Play", 2},
		{"Options", 3},
		{"Ranking", 4},
		{"About", 5},
		{"Exit", 6},
	};

//	m_pSoundModule = std::make_unique<CSoundModule>();

	m_IsClickable = false;
}

void TextModule::WriteText(sf::RenderWindow& window, sf::Vector2f posVec, TextProperties::eTextFont TextFormat, TextProperties::eTextType TextType, const char* TextString, TextProperties::eTextSize TextSize, float xStep, float yStep)
{
	TextHolder& loader = FileLoader::Instance().GetTextFontHolder();
	m_font = loader.get(TextFormat);

	if (TextType == TextProperties::TEXT_BUTTON)
		m_IsClickable = true;

	m_TextVec.push_back(sf::Text());
	sf::Text& m_textx = m_text;
	m_textx = m_TextVec.back();

	m_text.setFont(m_font);

	if (xStep > 0.0f)
		posVec.x += xStep;

	if (yStep > 0.0f)
		posVec.y += yStep;

	m_text.setPosition(posVec.x, posVec.y);

	m_text.setCharacterSize(TextSize);
	m_text.setFillColor(sf::Color::White);
	m_text.setString(TextString);

	sf::FloatRect localBounds = m_text.getLocalBounds();
	m_text.setOrigin(localBounds.left + localBounds.width / 2.0f, localBounds.top + localBounds.height / 2.0f);

	window.draw(m_text);
}

void TextModule::HandleClickEvent(sf::RenderWindow& window, sf::Mouse mouse, uint16_t& index)
{
	sf::FloatRect textBounds = GetBoundingBoxFromStrings(m_text.getString());

	if (m_IsClickable)
	{
		if (textBounds.contains(static_cast<sf::Vector2f>(mouse.getPosition(window))))
		{
			if (mouse.isButtonPressed(sf::Mouse::Button::Left))
			{
				auto it = m_textIndexMap.find(m_text.getString());

				if (it != m_textIndexMap.end())
					index = it->second;
				else
					index = 0;

				OnClickText(window, mouse);
			}
			else
				OnOverText(window, mouse);
		}
		else
			OnDefaultText(window, mouse);
	}
}

sf::FloatRect TextModule::GetBoundingBoxFromStrings(const std::vector<std::string>& textStrings)
{
	sf::Vector2f minPosition(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	sf::Vector2f maxPosition(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());

	for (const auto& textString : textStrings)
	{
		sf::Text text;
		text.setString(textString);

		sf::FloatRect localBounds = text.getLocalBounds();

		minPosition.x = std::min(minPosition.x, localBounds.left);
		minPosition.y = std::min(minPosition.y, localBounds.top);
		maxPosition.x = std::max(maxPosition.x, localBounds.left + localBounds.width);
		maxPosition.y = std::max(maxPosition.y, localBounds.top + localBounds.height);
	}

	float width = maxPosition.x - minPosition.x;
	float height = maxPosition.y - minPosition.y;

	return sf::FloatRect(minPosition.x, minPosition.y, width, height);
}

sf::FloatRect TextModule::GetBoundingBoxFromStrings(const std::string& textStr)
{
	sf::FloatRect globalBounds = m_text.getGlobalBounds();
	sf::FloatRect localBounds = m_text.getLocalBounds();

	float centerX = globalBounds.left + globalBounds.width / 2.0f;
	float x = centerX - localBounds.width / 2.0f;

	float y = globalBounds.top + localBounds.top * 0.2f;

	float width = localBounds.width;
	float height = localBounds.height;

	return sf::FloatRect(x, y, width, height);
}

void TextModule::OnDefaultText(sf::RenderWindow& window, sf::Mouse mouse)
{
	m_text.setOutlineThickness(0.0f);
	m_text.setOutlineColor(sf::Color::White);
	window.draw(m_text);
}

void TextModule::OnOverText(sf::RenderWindow& window, sf::Mouse mouse)
{
	m_text.setOutlineThickness(0.65f);
	m_text.setOutlineColor(sf::Color::Yellow);
	window.draw(m_text);
}

void TextModule::OnClickText(sf::RenderWindow& window, sf::Mouse mouse)
{

//	m_pSoundModule->PlaySounds(SoundEffect::SOUND_MENU_CLICK);
	m_text.setOutlineThickness(0.85f);
	m_text.setOutlineColor(sf::Color::Yellow);

	window.draw(m_text);
}

void TextModule::SetClickedText(sf::Text& clickedText)
{
	m_clickedText = clickedText;
}

void TextModule::PerformTextEventByMouseAction(sf::RenderWindow& window, sf::Mouse mouse, sf::Keyboard keyboard)
{
	sf::FloatRect textBounds = GetBoundingBoxFromStrings(m_text.getString());

	if (m_IsClickable)
	{
		if (textBounds.contains(static_cast<sf::Vector2f>(mouse.getPosition(window))))
		{
			OnOverText(window, mouse);

			if (mouse.isButtonPressed(sf::Mouse::Button::Left))
				OnClickText(window, mouse);
		}
	}

	OnDefaultText(window, mouse);
}


//void TextModule::FlushBounding()
//{
////	memset(&, 0x00, sizeof());
//
//	m_text.setOrigin(0, 0);
//	m_text.setPosition(0, 0);
//
//}

//void TextModule::FreeTextVector()
//{
//	m_TextVec.erase(std::remove_if(m_TextVec.begin(), m_TextVec.end(), m_IsClickable)
//}
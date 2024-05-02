#include "Button.h"
#include "SoundManager.h"

void CButton::MakeButton(sf::RenderWindow& window, sf::Vector2f posVec, float xStep, float yStep, float scaleX, float scaleY)
{
	if (xStep > 0.0f)
		posVec.x += xStep;

	if (yStep > 0.0f)
		posVec.y += yStep;

	m_buttonImage.setPosition(posVec.x, posVec.y);
	m_buttonImage.setScale(scaleX, scaleY);

	TextureHolder& textureHolder = FileLoader::Instance().GetTextureHolder();
	sf::Texture& buttonTexture = textureHolder.get(TextureProperties::TEXTURE_BUTTON_NORMAL);

	m_buttonImage.setTexture(buttonTexture);

	sf::FloatRect localBounds = m_buttonImage.getLocalBounds();
	m_buttonImage.setOrigin(localBounds.left + localBounds.width / 2.0f, localBounds.top + localBounds.height / 2.0f);

	window.draw(m_buttonImage);
}

void CButton::OnDefaultButton(sf::RenderWindow& window, sf::Mouse mouse)
{
	TextureHolder& textureHolder = FileLoader::Instance().GetTextureHolder();
	sf::Texture& buttonTexture = textureHolder.get(TextureProperties::TEXTURE_BUTTON_NORMAL);

	m_buttonImage.setTexture(buttonTexture);
	window.draw(m_buttonImage);
}

void CButton::OnOverButton(sf::RenderWindow& window, sf::Mouse mouse)
{
	TextureHolder& textureHolder = FileLoader::Instance().GetTextureHolder();
	sf::Texture& buttonTexture = textureHolder.get(TextureProperties::TEXTURE_BUTTON_OVER);

	m_buttonImage.setTexture(buttonTexture);
	window.draw(m_buttonImage);
}

void CButton::OnClickButton(sf::RenderWindow& window, sf::Mouse mouse)
{
	CSoundManager* pSoundMgr = new CSoundManager;
	pSoundMgr->PlaySounds(SoundEffect::SOUND_MENU_CLICK);

	TextureHolder& textureHolder = FileLoader::Instance().GetTextureHolder();
	sf::Texture& buttonTexture = textureHolder.get(TextureProperties::TEXTURE_BUTTON_CLICKED);

	m_buttonImage.setTexture(buttonTexture);
	window.draw(m_buttonImage);
}

void CButton::HandleClickEvent(sf::RenderWindow& window, sf::Mouse mouse, uint16_t& index)
{
	sf::FloatRect buttonBounds = m_buttonImage.getGlobalBounds();

	if (m_IsClickable)
	{
		if (buttonBounds.contains(static_cast<sf::Vector2f>(mouse.getPosition(window))))
		{
			if (mouse.isButtonPressed(sf::Mouse::Button::Left))
			{
				index = 1;
				OnClickButton(window, mouse);
			}
			else
				OnOverButton(window, mouse);
		}
		else
			OnDefaultButton(window, mouse);
	}
}
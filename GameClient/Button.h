#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace UI
{
	class Button
	{
	public:
		enum ButtonState
		{
			BUTTON_STATE_NORMAL,
			BUTTON_STATE_OVER,
			BUTTON_STATE_PRESSED,
		};
	public:
		Button();
	private:

	};
}
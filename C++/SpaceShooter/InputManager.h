#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <SFML/Graphics.hpp>

namespace ADS
{
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
		bool isKeyPressed(sf::Keyboard::Key key);

		sf::Vector2i getMousePosition(sf::RenderWindow& window);

	};
}

#endif // !_INPUTMANAGER_H_


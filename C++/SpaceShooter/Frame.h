#ifndef _FRAME_H_
#define _FRAME_H_

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Singleton.h"

namespace ADS
{
	class Frame
	{
	public:
		Frame(sf::Vector2i size = sf::Vector2i(0, 0), sf::Color color = sf::Color::White);

		Frame(sf::Texture const& texture, sf::IntRect area, sf::Color color = sf::Color::White);

		sf::Texture const* texture;	// The texture of the frame
		sf::IntRect area;			// the area of tghe texture to be rendered
		sf::Color color;			// the color of the frame

	private:
		struct DummyTexture { sf::Texture texture; };
		static sf::Texture& getDummyTexture();
	};		
}

#endif // !_FRAME_H_


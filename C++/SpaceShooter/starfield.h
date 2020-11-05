#ifndef _STARFIELD_H_
#define _STARFIELD_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"

namespace ADS
{
	class Starfield
	{
	public:
		Starfield(GameDataRef data);

		void moveStarfield(float dt);
		void drawStarfield();

		const std::vector<sf::Sprite>& getSprites() const;

	private:
		GameDataRef mData;
		std::vector<sf::Sprite> mStarfieldSprites;
	};
}

#endif // !_STARFIELD_H_


#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <SFML/Graphics.hpp>

namespace ADS
{
	class Collision
	{
	public:
		Collision();

		bool checkSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2);
		bool checkSpriteCollision(sf::Sprite sprite1, float scale1, sf::Sprite sprite2, float scale2);

	};
}

#endif // !_COLLISION_H_


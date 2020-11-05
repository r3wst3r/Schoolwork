#ifndef _HEROWEAPON_H_
#define _HEROWEAPON_H_

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "weapon.h"

namespace ADS
{
	class HeroWeapon : public Weapon
	{
	public:
		HeroWeapon(GameDataRef data);
		~HeroWeapon();

		void draw() override;
		void update(float dt) override;
	};
}


#endif // !_HEROWEAPON_H_


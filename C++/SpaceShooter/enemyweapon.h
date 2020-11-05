#ifndef _ENEMYWEAPON_H_
#define _ENEMYWEAPON_H_

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "weapon.h"
#include "enemyship.h"

namespace ADS
{
	class EnemyWeapon : public Weapon
	{
	public:
		EnemyWeapon(GameDataRef data, float speed,
			EnemyShipType enemyShipType);
		~EnemyWeapon();

		void draw() override;
		void update(float dt) override;
		int getDamage() const override;
				
	private:
		float mSpeed;
		EnemyShipType mEnemyShipType;
		int mDamage;
	};
}

#endif

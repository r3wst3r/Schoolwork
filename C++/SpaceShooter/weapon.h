#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <SFML/Graphics.hpp>
#include "Game.h"

namespace ADS
{
	enum class WeaponType
	{
		Hero,
		Enemy
	};

	class Weapon
	{
	public:
		Weapon(GameDataRef data, ADS::WeaponType weaponType);
		virtual ~Weapon();

		virtual void setPosition(sf::Vector2f position);
		virtual sf::Vector2f getPosition() const;
		virtual ADS::WeaponType getWeaponType() const;

		virtual int getDamage() const;

		const sf::Sprite& getSprite() const;

		virtual void draw() = 0;
		virtual void update(float) = 0;

	protected:
		GameDataRef mData;

		sf::Sprite mWeaponSprite;
		sf::Vector2f mPosition;
		ADS::WeaponType mWeaponType;
	};
}


#endif // !_WEAPON_H_


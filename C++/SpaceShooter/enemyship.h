#ifndef _ENEMYSHIP_H_
#define _ENEMYSHIP_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "definitions.h"
#include "weapon.h"
#include "Game.h"

namespace ADS
{
	enum class EnemyShipType
	{
		One = 1,
		Two,
		Three,
		Four,
		Five
	};

	struct EnemyShipProps
	{
		std::string spriteName;
		EnemyShipType shipType;
		EnemyShipProps(std::string spriteName, EnemyShipType shipType)
			: spriteName(spriteName), shipType(shipType) {}
	};

	class EnemyShip
	{
	public:
		EnemyShip(GameDataRef data, EnemyShipProps props);
		virtual ~EnemyShip();

		void draw();
		void update(float dt);
		void fireWeapon(std::vector<Weapon*>& weapons);

		void reset();
		sf::Vector2f getPosition() const;
		void setPosition(sf::Vector2f position);
		int getValue() const;
		const sf::Sprite& getSprite() const;

		virtual float getHeight() const;
		virtual float getWidth() const;
		
	private:
		GameDataRef mData;

		sf::Sprite mEnemySprite;
		sf::Vector2f mPosition;
		sf::Clock mWeaponFireClock;
		EnemyShipProps mEnemyShipProps;
		sf::Sound mWeaponSound;

		float mShipSpeed;
		float mMissileSpeed;
		int mWeaponFireProbability;
		float mWeaponFireFrequency;
		int mValue;		// Points player gets for destroying
	};
}

#endif // !_ENEMYSHIP_H_


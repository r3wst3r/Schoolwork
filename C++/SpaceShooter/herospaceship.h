#ifndef _HEROSPACESHIP_H_
#define _HEROSPACESHIP_H_

#include <SFML/Graphics.hpp>
#include "definitions.h"
#include "Game.h"
#include "weapon.h"

namespace ADS
{
	class HeroSpaceShip
	{
	public:
		HeroSpaceShip(GameDataRef data);
		~HeroSpaceShip();

		void draw();
		void update(float dt);
		void handleInput(sf::Event event, 
			             std::vector<Weapon*>& weapons);

		void reset();
		void setVisible(bool visible);
		sf::Vector2f getPosition() const;
		int getLives() const;
		int decreaseLives();
		void setPoints(int deltaPoints);
		int getPoints() const;

		void setHullIntegrity(int deltaHullIntegrity);
		int getHullIntegrity() const;

		const sf::Sprite& getSprite() const;

	private:
		enum class HeroShipMoveState
		{
			Left,
			Right,
			Stop
		};

		enum class HeroWeaponFireStatus
		{
			Abled,
			Disabled
		} mHeroWeaponStatus;

		GameDataRef mData;

		sf::Sprite mHeroSprite;

		sf::Vector2f mPosition;

		HeroShipMoveState mMoveState;

		sf::Clock mWeaponClock;

		float mShipSpeed;

		bool isVisible;

		int mLives;

		int mPoints;

		int mHullIntegrity;

		sf::Sound mWeaponSound;
	};
}


#endif // !_HEROSPACESHIP_H_


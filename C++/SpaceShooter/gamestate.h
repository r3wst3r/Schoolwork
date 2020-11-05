#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <vector>

#include "State.h"
#include "Game.h"
#include "starfield.h"
#include "herospaceship.h"
#include "enemyship.h"
#include "weapon.h"
#include "Collision.h"
#include "explosion.h"
#include "hud.h"

namespace ADS
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void init() override;
		void handleInput() override;
		void update(float dt) override;
		void draw(float dt) override;

	private:
		// methods
		void initEnemyShips();
		void buildEnemyShips();

	private:
		// variables
		GameDataRef mData;

		Starfield* mStarfield;
		HeroSpaceShip* mHeroSpaceship;
		Explosion* mExplosion;
		HUD* mHUD;
		ExplosionProperties mExplosionProperties;
		ExplosionProperties mHeroExplosionProperties;
		ExplosionProperties mSmallExplosionProperties;

		Collision collision;
		
		EGameStates mEGameState;

		sf::Clock mClock;
		sf::Clock mEnemyWaveClock;

		std::vector<Weapon*> mWeapons;
		std::vector<EnemyShip*> mEnemyShips;
		std::vector<Explosion*> mExplosions;
		EnemyShipProps** mEnemyShipProps;

		sf::Music mBackgroundMusic;
		sf::Sound mEnemyExplosion;
		sf::Sound mHeroExplosion;
		sf::Sound mSmallExplosion;

	};
}

#endif // !_GAMESTATE_H_


#ifndef _HUD_H_
#define _HUD_H_

#include <SFML\Graphics.hpp>
#include "definitions.h"
#include "Game.h"

namespace ADS
{
	class HUD
	{
	public:
		HUD(GameDataRef data);

		void draw();
		void updateScore(int score);
		void updateLives(int lives);
		void updateHullIntegrity(int hullIntegrity);

	private:
		GameDataRef mData;

		sf::Text mScoreText;
		sf::Text mHullIntegrityText;
		int mLives;
		int mHullIntegrity;

		sf::RectangleShape mHullIntegrityBackground;
		sf::RectangleShape mHullIntegrityBar;

		sf::Sprite mSmallShip;

	};
}

#endif // !_HUD_H_

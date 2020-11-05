#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace ADS
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	using GameDataRef = std::shared_ptr<GameData>;

	class Game
	{
	public:
		Game(int width, int height, std::string title);

	private:
		void run();

	private:
		const float dt = 1.0f / 60.0f;

		sf::Clock mClock;
		GameDataRef mData; // = std::make_shared<GameData>();


	};
}

#endif // !_GAME_H_


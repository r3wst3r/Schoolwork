#include "Game.h"
//#include "SplashState.h"

#include <cstdlib>
#include <ctime>

#include "GameState.h"

ADS::Game::Game(int width, int height, std::string title)
{
	std::srand(unsigned int(std::time(0)));
	mData = std::make_shared<GameData>();
	mData->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	// Load your first state here
	mData->machine.addState(StateRef(new GameState(mData)));
	// Need to start a state
	run();
}

void ADS::Game::run()
{
	float newTime, frameTime, interpolation;
	float currentTime = mClock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (mData->window.isOpen())
	{
		mData->machine.processStateChanges();

		newTime = mClock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			mData->machine.getActiveState()->handleInput();
			mData->machine.getActiveState()->update(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		mData->machine.getActiveState()->draw(interpolation);
	}
}

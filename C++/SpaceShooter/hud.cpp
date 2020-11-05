#include "hud.h"

ADS::HUD::HUD(GameDataRef data) : mData(data)
{
	mScoreText.setFont(mData->assets.getFont("Regular Font"));
	mScoreText.setString("Score: 0");
	mScoreText.setCharacterSize(24);
	mScoreText.setFillColor(sf::Color::Red);
	mScoreText.setOrigin(mScoreText.getGlobalBounds().width / 2,
		mScoreText.getGlobalBounds().height / 2);
	mScoreText.setPosition(mData->window.getSize().x -
		(mScoreText.getString().getSize() * 14),
		10);

	mHullIntegrityText.setFont(mData->assets.getFont("Regular Font"));
	mHullIntegrityText.setString("Hull Integrity:");
	mHullIntegrityText.setCharacterSize(24);
	mHullIntegrityText.setFillColor(sf::Color::White);
	mHullIntegrityText.setOrigin(mHullIntegrityText.getGlobalBounds().width / 2,
		mHullIntegrityText.getGlobalBounds().height / 2);
	mHullIntegrityText.setPosition(mHullIntegrityText.getGlobalBounds().width / 2 + 10, 50);

	mHullIntegrity = HERO_SPACESHIP_MAX_HULL_INTEGRITY;
	mHullIntegrityBar.setFillColor(sf::Color::Green);
	mHullIntegrityBar.setSize(sf::Vector2f(2.5 * mHullIntegrity, 20));
	mHullIntegrityBar.setPosition(10, 75);

	mSmallShip.setTexture(mData->assets.getTexture("Player Life"));
}

void ADS::HUD::draw()
{
	mData->window.draw(mScoreText);

	for (int i = 0; i < mLives; i++)
	{
		mSmallShip.setPosition(i * mSmallShip.getGlobalBounds().width + 10, 10);
		mData->window.draw(mSmallShip);
	}

	mData->window.draw(mHullIntegrityText);
	mData->window.draw(mHullIntegrityBar);
}

void ADS::HUD::updateScore(int score)
{
	std::string strScore = "Score: " + std::to_string(score);
	mScoreText.setString(strScore);
	mScoreText.setPosition(mData->window.getSize().x -
		(mScoreText.getString().getSize() * 14),
		10);
}

void ADS::HUD::updateLives(int lives)
{
	mLives = lives;
}

void ADS::HUD::updateHullIntegrity(int hullIntegrity)
{
	mHullIntegrity = hullIntegrity;

	if (mHullIntegrity >= 0.75 * HERO_SPACESHIP_MAX_HULL_INTEGRITY)
		mHullIntegrityBar.setFillColor(sf::Color::Green);
	else if(mHullIntegrity >= 0.25 * HERO_SPACESHIP_MAX_HULL_INTEGRITY)
		mHullIntegrityBar.setFillColor(sf::Color::Yellow);
	else
		mHullIntegrityBar.setFillColor(sf::Color::Red);

	mHullIntegrityBar.setSize(sf::Vector2f(2.5 * mHullIntegrity, 20));
}

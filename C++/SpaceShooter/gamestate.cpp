#include "gamestate.h"
#include "definitions.h"
#include "heroweapon.h"


ADS::GameState::GameState(GameDataRef data) : mData(data)
{}

void ADS::GameState::init()
{
	// Load background
	mData->assets.loadTexture("Starfield", GAME_BACKGROUND_FILEPATH);

	// Load sprites
	mData->assets.loadTexture("Hero Ship", HERO_SPACESHIP_FILEPATH);
	mData->assets.loadTexture("Hero Weapon", HERO_WEAPON_FILEPATH);
	mData->assets.loadTexture("Enemy Weapon Level 1", ENEMY_WEAPON_LEVEL_1_FILEPATH);
	mData->assets.loadTexture("Enemy Weapon Level 2", ENEMY_WEAPON_LEVEL_2_FILEPATH);
	mData->assets.loadTexture("Enemy Weapon Level 3", ENEMY_WEAPON_LEVEL_3_FILEPATH);
	mData->assets.loadTexture("Enemy Weapon Level 4", ENEMY_WEAPON_LEVEL_4_FILEPATH);
	mData->assets.loadTexture("Enemy Weapon Level 5", ENEMY_WEAPON_LEVEL_5_FILEPATH);
	mData->assets.loadTexture("Enemy Explosion", EXPLOSION_FILEPATH);
	mData->assets.loadTexture("Small Explosion", SMALL_EXPLOSION_FILEPATH);
	mData->assets.loadTexture("Hero Explosion", HERO_EXPLOSION_FILEPATH);
	mData->assets.loadTexture("Player Life", PLAYER_LIFE_FILEPATH);
	mData->assets.loadTexture("Button", BUTTON_FILEPATH);

	// Load sounds and music
	mData->assets.loadSound("Hero Weapon Sound", HERO_WEAPON_SOUND_FILEPATH);
	mData->assets.loadSound("Enemy Weapon Sound", ENEMY_WEAPON_SOUND_FILEPATH);
	mData->assets.loadSound("Enemy Explosion Sound", ENEMY_EXPLOSION_SOUND_FILEPATH);
	mData->assets.loadSound("Hero Explosion Sound", HERO_EXPLOSION_SOUND_FILEPATH);
	mData->assets.loadSound("Small Explosion Sound", SMALL_EXPLOSION_SOUND_FILEPATH);

	mBackgroundMusic.openFromFile(GAME_BACKGROUND_MUSIC_FILEPATH);

	// Load fonts
	mData->assets.loadFont("Regular Font", REGULAR_FONT_FILEPATH);

	// Setup Enemy Ships
	initEnemyShips();

	// Instantiate objects
	mStarfield = new Starfield(mData);
	mHeroSpaceship = new HeroSpaceShip(mData);
	mHUD = new HUD(mData);
	// Setup animations
	mExplosionProperties.name = "Enemy Explosion";
	mExplosionProperties.frameCount = sf::Vector2u(4, 4);
	mExplosionProperties.frameSize = sf::Vector2i(64, 64);
	mExplosionProperties.frameTime = sf::milliseconds(150);

	mHeroExplosionProperties.name = "Hero Explosion";
	mHeroExplosionProperties.frameCount = sf::Vector2u(4, 4);
	mHeroExplosionProperties.frameSize = sf::Vector2i(128, 128);
	mHeroExplosionProperties.frameTime = sf::milliseconds(250);

	mSmallExplosionProperties.name = "Small Explosion";
	mSmallExplosionProperties.frameCount = sf::Vector2u(4, 4);
	mSmallExplosionProperties.frameSize = sf::Vector2i(64, 64);
	mSmallExplosionProperties.frameTime = sf::milliseconds(100);
	
	// Setup sounds
	mEnemyExplosion.setBuffer(mData->assets.getSound("Enemy Explosion Sound"));
	mHeroExplosion.setBuffer(mData->assets.getSound("Hero Explosion Sound"));
	mSmallExplosion.setBuffer(mData->assets.getSound("Small Explosion Sound"));
	mBackgroundMusic.setLoop(true);
	mBackgroundMusic.play();

	// Setup HUD
	mHUD->updateScore(mHeroSpaceship->getPoints());
	mHUD->updateLives(mHeroSpaceship->getLives());

	mEGameState = EGameStates::ePlaying;
	//buildEnemyShips();
	mEnemyWaveClock.restart();
}

void ADS::GameState::handleInput()
{
	sf::Event event;

	while (mData->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mData->window.close();
		}

		if (mEGameState == EGameStates::ePlaying &&
			(event.type == sf::Event::KeyPressed ||
				event.type == sf::Event::KeyReleased))
		{
			mHeroSpaceship->handleInput(event, mWeapons);
		}
	}
}

void ADS::GameState::update(float dt)
{
	if (mEGameState == EGameStates::eGameOver &&
		mClock.getElapsedTime().asSeconds() > GAMEOVER_PAUSE)
	{
		int points = mHeroSpaceship->getPoints();

		// Change to game over screen

		delete mStarfield;
		return;
	}

	// Update the starfield
	mStarfield->moveStarfield(dt);

	// Update hero ship
	mHeroSpaceship->update(dt);

	// Update enemy ships
	// See if we are building more ships
	if (mEGameState == EGameStates::ePlaying &&
		mEnemyWaveClock.getElapsedTime().asSeconds() > 
		                                  ENEMY_WAVE_FREQUENCY)
	{
		buildEnemyShips();
		mEnemyWaveClock.restart();
	}

	// Move the ships that are already built
	for (std::vector<EnemyShip*>::iterator it = mEnemyShips.begin();
		it != mEnemyShips.end();)
	{
		if ((*it)->getPosition().y > SCREEN_HEIGHT + (*it)->getHeight() / 2)
		{
			// destroy the ship
			delete (*it);
			it = mEnemyShips.erase(it);
		}
		else
		{
			(*it)->update(dt);
			(*it)->fireWeapon(mWeapons);
			it++;
		}
	}

	// Update weapons
	for (std::vector<Weapon*>::iterator it = mWeapons.begin();
		it != mWeapons.end();)
	{
		if ((*it)->getPosition().y < 0 - (*it)->getSprite().getGlobalBounds().height / 2 ||
			(*it)->getPosition().y > SCREEN_HEIGHT + (*it)->getSprite().getGlobalBounds().height / 2)
		{
			// destroy the weapon
			delete(*it);
			it = mWeapons.erase(it);
		}
		else
		{
			(*it)->update(dt);
			it++;
		}
	}

	// Update explosions
	for (std::vector<Explosion*>::iterator it = mExplosions.begin();
		it != mExplosions.end();)
	{
		if ((*it)->getAnimationStatus() 
			       == ADS::AnimationStatus::Stop)
		{
			// destroy explosion
			delete(*it);
			it = mExplosions.erase(it);
			if (mEGameState == EGameStates::eStop 
				               && mExplosions.empty())
			{
				mHeroSpaceship->reset();
				mHeroSpaceship->setVisible(true);
				mHUD->updateHullIntegrity(mHeroSpaceship->getHullIntegrity());
				mEGameState = EGameStates::ePlaying;
			}
		}
		else
		{
			(*it)->update(dt);
			it++;
		}
	}

	// Collision detection
	bool didCollide = false;
	if (mEGameState != EGameStates::ePlaying)
	{
		return;
	}
	for (std::vector<Weapon*>::iterator wit = mWeapons.begin(); 
		   wit != mWeapons.end();)
	{
		if ((*wit)->getWeaponType() == ADS::WeaponType::Hero)
		{
			for (std::vector<EnemyShip*>::iterator esit = mEnemyShips.begin(); esit != mEnemyShips.end();)
			{
				if (collision.checkSpriteCollision((*esit)->getSprite(), 1.0f, (*wit)->getSprite(), 1.0f))
				{
					// Increase score
					mHeroSpaceship->setPoints((*esit)->getValue());
					
					// Update HUD
					mHUD->updateScore(mHeroSpaceship->getPoints());

					// Create an explosion
					mExplosions.push_back(new Explosion(mData, mExplosionProperties, (*esit)->getSprite().getPosition()));

					// Animate explosion
					mEnemyExplosion.play();

					// remove enemy
					esit = mEnemyShips.erase(esit);

					// remove weapon
					wit = mWeapons.erase(wit);
					didCollide = true;
					break;
				}
				else
				{
					esit++;
				}
			}
		}
		else if ((*wit)->getWeaponType() == ADS::WeaponType::Enemy)
		{
			if (collision.checkSpriteCollision(mHeroSpaceship->getSprite(), 1.0f, (*wit)->getSprite(), 1.0f))
			{
				// do damage to ship
				mHeroSpaceship->setHullIntegrity(-(*wit)->getDamage());
				sf::Vector2f smallExplosionPosition = (*wit)->getPosition();
				mHUD->updateHullIntegrity(mHeroSpaceship->getHullIntegrity());

				// remove weapon
				if (!mWeapons.empty())
					wit = mWeapons.erase(wit);
				didCollide = true;

				if (mHeroSpaceship->getHullIntegrity() <= 0)
				{
					// remove hero ship
					mHeroSpaceship->setVisible(false);
					mEGameState = EGameStates::eStop;

					// make explosion
					mExplosions.push_back(new Explosion(mData, mHeroExplosionProperties, mHeroSpaceship->getSprite().getPosition()));
					mHeroExplosion.play();

					// decrease lives
					mHeroSpaceship->decreaseLives();
					mHUD->updateLives(mHeroSpaceship->getLives());

					// if lives <= 0 then game is over
					if (mHeroSpaceship->getLives() <= 0)
					{						
						mEGameState = EGameStates::eGameOver;
						mEnemyShips.clear();
						mWeapons.clear();
						mClock.restart();
						break;
					}
					// else
					// remove all enemy ships and missiles from game
					// reset the hero ship
					else
					{
						mEnemyShips.clear();
						mWeapons.clear();

						// remove this later when we code the explosions
						//mHeroSpaceship->reset();
						//mHeroSpaceship->setVisible(true);
						//mEGameState = EGameStates::ePlaying;

						break;
					}
				}
				else
				{
					// Do a small explosion
					mExplosions.push_back(new Explosion(mData, mSmallExplosionProperties, smallExplosionPosition));
					mSmallExplosion.play();
				}

			}
		}
		if (!didCollide)
			wit++;
		else
			didCollide = false;
	}

}

void ADS::GameState::draw(float dt)
{
	// Clear the screen
	mData->window.clear(sf::Color::Red);

	// Draw some really cool stuff here
	// Draw the starfield
	mStarfield->drawStarfield();

	// draw weapons
	for (Weapon* weapon : mWeapons)
		weapon->draw();

	// draw space ship
	if (mEGameState == EGameStates::ePlaying)
		mHeroSpaceship->draw();

	// draw enemies
	for (EnemyShip* enemyShip : mEnemyShips)
		enemyShip->draw();

	// draw explosions
	for (Explosion* exp : mExplosions)
		exp->draw();

	// draw asteroids

	// draw UFO

	// draw HUD
	mHUD->draw();

	// Display the screen
	mData->window.display();		
}

void ADS::GameState::initEnemyShips()
{
	mEnemyShipProps = new EnemyShipProps*[NUM_ENEMY_SHIPS];
	std::string shipColors[]{ "Black", "Blue", "Red", "Green" };
	for (int i = 0; i < NUM_ENEMY_SHIPS; i++)
	{
		std::string shipName = "enemy" + shipColors[i / 5] +
							   std::to_string(i % 5 + 1);
		std::string shipFile = "resource/bitmaps/" + shipName + ".png";
		mData->assets.loadTexture(shipName, shipFile);
		mEnemyShipProps[i] = new EnemyShipProps(shipName,
			                  static_cast<EnemyShipType>(i % 5 + 1));
	}
}

void ADS::GameState::buildEnemyShips()
{
	int shipNumbers[]{ 1,1,1,1,1,2,2,2,2,3,3,3,4,4,5 };
	int shipPositionXWidth = SCREEN_WIDTH / 5;
	std::vector<int> shipPositionX = { 0, shipPositionXWidth, 
		shipPositionXWidth * 2, shipPositionXWidth * 3, 
		shipPositionXWidth * 4 };

	std::string shipColors[]{ "Black", "Blue", "Red", "Green" };

	int buildShipProb = rand() % 100;
	// Do we create any ships?
	if (buildShipProb < ENEMY_SPAWN_PROBABILITY)
	{
		// Yes, how many
		int numEnemyShips = shipNumbers[rand() % 15];
		int shipColor = rand() % 4;
		int shipPropIndex = 0;
		for (int i = 0; i < numEnemyShips; i++)
		{
			int shipTypeProb = rand() % 100;
			if (shipTypeProb < 50) // Type one ship
			{
				shipPropIndex = shipColor * 5 + 0;
			}
			else if (shipTypeProb < 70) // Type two ship
			{
				shipPropIndex = shipColor * 5 + 1;
			}
			else if (shipTypeProb < 85) // Type three ship
			{
				shipPropIndex = shipColor * 5 + 2;
			}
			else if (shipTypeProb < 95) // Type four ship
			{
				shipPropIndex = shipColor * 5 + 3;
			}
			else // Type five ship
			{
				shipPropIndex = shipColor * 5 + 4;
			}
			EnemyShip* enemyShip = new EnemyShip(mData, 
				                   *mEnemyShipProps[shipPropIndex]);
			//float xPos = rand() % static_cast<int>(SCREEN_WIDTH - enemyShip->getSprite().getGlobalBounds().width) + enemyShip->getSprite().getGlobalBounds().width / 2;
			int index = rand() % shipPositionX.size();
			float xPos = shipPositionX[index] + 
			    enemyShip->getSprite().getGlobalBounds().width / 2 + 
				rand() % static_cast<int>(shipPositionXWidth - 
					enemyShip->getSprite().getGlobalBounds().width);

			shipPositionX.erase(shipPositionX.begin() + index);
			float yPos = -enemyShip->getSprite().getGlobalBounds().height - (rand() % 10 + 10);
			enemyShip->setPosition(sf::Vector2f(xPos, yPos));
			mEnemyShips.push_back(enemyShip);
		}

	}
}

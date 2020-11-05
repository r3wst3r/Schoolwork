#include "herospaceship.h"
#include "heroweapon.h"

ADS::HeroSpaceShip::HeroSpaceShip(GameDataRef data) : mData(data)
{
	mHeroSprite.setTexture(mData->assets.getTexture("Hero Ship"));
	mHeroSprite.setPosition(mData->window.getSize().x / 2 - mHeroSprite.getGlobalBounds().width / 2,
		                    mData->window.getSize().y - mHeroSprite.getGlobalBounds().height * 1.1);
	sf::Vector2f origin = sf::Vector2f(mHeroSprite.getGlobalBounds().width / 2,
									   mHeroSprite.getGlobalBounds().height / 2);
	mHeroSprite.setOrigin(origin);

	mMoveState = HeroShipMoveState::Stop;
	mShipSpeed = HERO_SPACESHIP_SPEED;

	mPosition = mHeroSprite.getPosition();

	mHeroWeaponStatus = HeroWeaponFireStatus::Abled;

	isVisible = true;

	mLives = LIVES;

	mPoints = 0;

	mHullIntegrity = HERO_SPACESHIP_MAX_HULL_INTEGRITY;

	mWeaponSound.setBuffer(mData->assets.getSound("Hero Weapon Sound"));
}

ADS::HeroSpaceShip::~HeroSpaceShip() {}

void ADS::HeroSpaceShip::draw()
{
	if (isVisible)
		mData->window.draw(mHeroSprite);
}

void ADS::HeroSpaceShip::update(float dt)
{
	float xPos = mHeroSprite.getPosition().x;
	float yPos = mHeroSprite.getPosition().y;

	switch (mMoveState)
	{
	case HeroShipMoveState::Stop:
		break;

	case HeroShipMoveState::Left:
		xPos -= mShipSpeed * dt;
		break;

	case HeroShipMoveState::Right:
		xPos += mShipSpeed * dt;
		break;
	}

	// clamp to screen
	if (xPos < mHeroSprite.getGlobalBounds().width / 2)
	{
		xPos = mHeroSprite.getGlobalBounds().width / 2;
	}
	else if (xPos > mData->window.getSize().x - 
		     mHeroSprite.getGlobalBounds().width / 2)
	{
		xPos = mData->window.getSize().x -
			mHeroSprite.getGlobalBounds().width / 2;
	}

	mHeroSprite.setPosition(xPos, yPos);
	mPosition.x = xPos;
}

void ADS::HeroSpaceShip::handleInput(sf::Event event, 
	                                 std::vector<Weapon*>& weapons)
{
	// event should be a KeyPress or KeyRelease
	switch (event.type)
	{
	case sf::Event::KeyPressed: // first outer case
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			mMoveState = HeroShipMoveState::Left;
			break;
		case sf::Keyboard::Right:
			mMoveState = HeroShipMoveState::Right;
			break;
		case sf::Keyboard::Space:
			if (mHeroWeaponStatus == HeroWeaponFireStatus::Abled &&
				mWeaponClock.getElapsedTime().asSeconds() > HERO_WEAPON_FREQUENCY)
			{
				// Fire weapon
				HeroWeapon* weapon = new HeroWeapon(mData);
				weapon->setPosition(getPosition());
				weapons.push_back(weapon);
				mWeaponClock.restart();
				mHeroWeaponStatus = HeroWeaponFireStatus::Disabled;
				mWeaponSound.play();
			}
			break;
		} // end of nested switch
		break;

	case sf::Event::KeyReleased:	// second outer case
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
		case sf::Keyboard::Right:
			mMoveState = HeroShipMoveState::Stop;
			break;
		case sf::Keyboard::Space:
			mHeroWeaponStatus = HeroWeaponFireStatus::Abled;
			break;
		}
		break;
	}
}

void ADS::HeroSpaceShip::reset()
{
	mHeroSprite.setPosition(mData->window.getSize().x / 2 - mHeroSprite.getGlobalBounds().width / 2,
		mData->window.getSize().y - mHeroSprite.getGlobalBounds().height * 1.1);
	mMoveState = HeroShipMoveState::Stop;
	mHullIntegrity = HERO_SPACESHIP_MAX_HULL_INTEGRITY;
}

void ADS::HeroSpaceShip::setVisible(bool visible)
{
	isVisible = visible;
}

sf::Vector2f ADS::HeroSpaceShip::getPosition() const
{
	return mPosition;
}

int ADS::HeroSpaceShip::getLives() const
{
	return mLives;
}

int ADS::HeroSpaceShip::decreaseLives()
{
	return --mLives;
}

void ADS::HeroSpaceShip::setPoints(int deltaPoints)
{
	mPoints += deltaPoints;
}

int ADS::HeroSpaceShip::getPoints() const
{
	return mPoints;
}

void ADS::HeroSpaceShip::setHullIntegrity(int deltaHullIntegrity)
{
	mHullIntegrity += deltaHullIntegrity;
	if (mHullIntegrity < 0) mHullIntegrity = 0;
	if (mHullIntegrity > HERO_SPACESHIP_MAX_HULL_INTEGRITY)
		mHullIntegrity = HERO_SPACESHIP_MAX_HULL_INTEGRITY;
}

int ADS::HeroSpaceShip::getHullIntegrity() const
{
	return mHullIntegrity;
}

const sf::Sprite & ADS::HeroSpaceShip::getSprite() const
{
	return mHeroSprite;
}

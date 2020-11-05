#include "enemyship.h"
#include "enemyweapon.h"

ADS::EnemyShip::EnemyShip(GameDataRef data, EnemyShipProps props)
	: mData(data), mEnemyShipProps(props)
{
	mEnemySprite.setTexture(mData->assets.getTexture(mEnemyShipProps.spriteName));
	mEnemySprite.setPosition(mData->window.getSize().x / 2 - getWidth() / 2,
							 -getHeight());
	sf::Vector2f origin = sf::Vector2f(mEnemySprite.getGlobalBounds().width / 2,
									   mEnemySprite.getGlobalBounds().height / 2);
	mEnemySprite.setOrigin(origin);

	switch (mEnemyShipProps.shipType)
	{
	case EnemyShipType::One:
		mMissileSpeed = ENEMY_MISSILE_SLOW_SPEED;
		mShipSpeed = ENEMY_SPACESHIP_SLOW_SPEED;
		mWeaponFireProbability = ENEMY_WEAPON_FIRE_PROBABILITY_LOW;
		mWeaponFireFrequency = ENEMY_FIRE_FREQUENCY_LOW;
		mValue = ENEMY_VALUE_LEVEL_1;
		break;
	case EnemyShipType::Two:
		mMissileSpeed = ENEMY_MISSILE_MEDIUM_SPEED;
		mShipSpeed = ENEMY_SPACESHIP_MEDIUM_SPEED;
		mWeaponFireProbability = ENEMY_WEAPON_FIRE_PROBABILITY_MEDIUM;
		mWeaponFireFrequency = ENEMY_FIRE_FREQUENCY_MEDIUM;
		mValue = ENEMY_VALUE_LEVEL_2;
		break;
	case EnemyShipType::Three:
		mMissileSpeed = ENEMY_MISSILE_SLOW_SPEED;
		mShipSpeed = ENEMY_SPACESHIP_SLOW_SPEED;
		mWeaponFireProbability = ENEMY_WEAPON_FIRE_PROBABILITY_MEDIUM;
		mWeaponFireFrequency = ENEMY_FIRE_FREQUENCY_HIGH;
		mValue = ENEMY_VALUE_LEVEL_3;
		break;
	case EnemyShipType::Four:
		mMissileSpeed = ENEMY_MISSILE_FAST_SPEED;
		mShipSpeed = ENEMY_SPACESHIP_MEDIUM_SPEED;
		mWeaponFireProbability = ENEMY_WEAPON_FIRE_PROBABILITY_HIGH;
		mWeaponFireFrequency = ENEMY_FIRE_FREQUENCY_MEDIUM;
		mValue = ENEMY_VALUE_LEVEL_4;
		break;
	case EnemyShipType::Five:
		mMissileSpeed = ENEMY_MISSILE_FAST_SPEED;
		mShipSpeed = ENEMY_SPACESHIP_FAST_SPEED;
		mWeaponFireProbability = ENEMY_WEAPON_FIRE_PROBABILITY_MEDIUM;
		mWeaponFireFrequency = ENEMY_FIRE_FREQUENCY_MEDIUM;
		mValue = ENEMY_VALUE_LEVEL_5;
		break;
	} // end of switch

	mWeaponSound.setBuffer(mData->assets.getSound("Enemy Weapon Sound"));

	mPosition = mEnemySprite.getPosition();
	mWeaponFireClock.restart();
}

ADS::EnemyShip::~EnemyShip() {}

void ADS::EnemyShip::draw()
{
	mData->window.draw(mEnemySprite);
}

void ADS::EnemyShip::update(float dt)
{
	float posY = getPosition().y;
	posY += mShipSpeed * dt;
	mEnemySprite.setPosition(getPosition().x, posY);
	setPosition(sf::Vector2f(getPosition().x, posY));
}

void ADS::EnemyShip::fireWeapon(std::vector<Weapon*>& weapons)
{
	int fireChance = rand() % 1000;
	if (fireChance < mWeaponFireProbability &&
		mWeaponFireClock.getElapsedTime().asSeconds() > mWeaponFireFrequency)
	{
		EnemyWeapon* enemyWeapon = new EnemyWeapon(mData, mMissileSpeed,
												   mEnemyShipProps.shipType);
		enemyWeapon->setPosition(getPosition());
		weapons.push_back(enemyWeapon);
		mWeaponSound.play();
		mWeaponFireClock.restart();
	}
}

void ADS::EnemyShip::reset() {}

sf::Vector2f ADS::EnemyShip::getPosition() const
{
	return mPosition;
}

void ADS::EnemyShip::setPosition(sf::Vector2f position)
{
	mPosition = position;
	mEnemySprite.setPosition(position);
}

int ADS::EnemyShip::getValue() const
{
	return mValue;
}

const sf::Sprite & ADS::EnemyShip::getSprite() const
{
	return mEnemySprite;
}

float ADS::EnemyShip::getHeight() const
{
	return mEnemySprite.getGlobalBounds().height;
}

float ADS::EnemyShip::getWidth() const
{
	return mEnemySprite.getGlobalBounds().width;
}

#include "enemyweapon.h"

ADS::EnemyWeapon::EnemyWeapon(GameDataRef data, float speed, 
	                          EnemyShipType enemyShipType)
	: Weapon(data, ADS::WeaponType::Enemy), mSpeed(speed),
	mEnemyShipType(enemyShipType)
{
	// What missile sprite do we use?
	switch (enemyShipType)
	{
	case EnemyShipType::One:
		mWeaponSprite.setTexture(mData->assets.getTexture("Enemy Weapon Level 1"));
		mDamage = ENEMY_MISSILE_DAMAGE_LEVEL_1;
		break;
	case EnemyShipType::Two:
		mWeaponSprite.setTexture(mData->assets.getTexture("Enemy Weapon Level 2"));
		mDamage = ENEMY_MISSILE_DAMAGE_LEVEL_2;
		break;
	case EnemyShipType::Three:
		mWeaponSprite.setTexture(mData->assets.getTexture("Enemy Weapon Level 3"));
		mDamage = ENEMY_MISSILE_DAMAGE_LEVEL_3;
		break;
	case EnemyShipType::Four:
		mWeaponSprite.setTexture(mData->assets.getTexture("Enemy Weapon Level 4"));
		mDamage = ENEMY_MISSILE_DAMAGE_LEVEL_4;
		break;
	case EnemyShipType::Five:
		mWeaponSprite.setTexture(mData->assets.getTexture("Enemy Weapon Level 5"));
		mDamage = ENEMY_MISSILE_DAMAGE_LEVEL_5;
		break;
	}

	sf::Vector2f origin = sf::Vector2f(mWeaponSprite.getGlobalBounds().width / 2,
									   mWeaponSprite.getGlobalBounds().height / 2);
	mWeaponSprite.setOrigin(origin);
}

ADS::EnemyWeapon::~EnemyWeapon() {}

void ADS::EnemyWeapon::draw()
{
	mData->window.draw(mWeaponSprite);
}

void ADS::EnemyWeapon::update(float dt)
{
	float posY = getPosition().y;
	posY += mSpeed * dt;
	mWeaponSprite.setPosition(getPosition().x, posY);
	setPosition(sf::Vector2f(getPosition().x, posY));
}

int ADS::EnemyWeapon::getDamage() const
{
	return mDamage;
}

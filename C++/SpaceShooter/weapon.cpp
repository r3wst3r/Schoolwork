#include "weapon.h"

ADS::Weapon::Weapon(GameDataRef data, ADS::WeaponType weaponType)
	: mData(data), mWeaponType(weaponType)
{}

ADS::Weapon::~Weapon() {}

void ADS::Weapon::setPosition(sf::Vector2f position)
{
	mPosition.x = position.x;
	mPosition.y = position.y;
}

sf::Vector2f ADS::Weapon::getPosition() const
{
	return mPosition;
}

ADS::WeaponType ADS::Weapon::getWeaponType() const
{
	return mWeaponType;
}

int ADS::Weapon::getDamage() const
{
	return 0;
}

const sf::Sprite & ADS::Weapon::getSprite() const
{
	return mWeaponSprite;
}

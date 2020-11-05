#include "heroweapon.h"
#include "definitions.h"

ADS::HeroWeapon::HeroWeapon(GameDataRef data)
	: Weapon(data, ADS::WeaponType::Hero)
{
	mWeaponSprite.setTexture(mData->assets.getTexture("Hero Weapon"));
	sf::Vector2f origin = sf::Vector2f(mWeaponSprite.getGlobalBounds().width / 2,
		                               mWeaponSprite.getGlobalBounds().height / 2);
	mWeaponSprite.setOrigin(origin);
}

ADS::HeroWeapon::~HeroWeapon() {}

void ADS::HeroWeapon::draw()
{
	mData->window.draw(mWeaponSprite);
}

void ADS::HeroWeapon::update(float dt)
{
	float posY = getPosition().y;
	posY -= HERO_WEAPON_SPEED * dt;
	mWeaponSprite.setPosition(getPosition().x, posY);
	setPosition(sf::Vector2f(getPosition().x, posY));
}

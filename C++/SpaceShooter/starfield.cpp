#include "starfield.h"
#include "definitions.h"

ADS::Starfield::Starfield(GameDataRef data) : mData(data)
{
	sf::Sprite sprite1(mData->assets.getTexture("Starfield"));
	sf::Sprite sprite2(mData->assets.getTexture("Starfield"));
	sf::Sprite sprite3(mData->assets.getTexture("Starfield"));

	sprite1.setPosition(0, 0);
	sprite2.setPosition(0, -sprite2.getLocalBounds().height / 2);
	sprite3.setPosition(0, -sprite3.getLocalBounds().height);

	mStarfieldSprites.push_back(sprite1);
	mStarfieldSprites.push_back(sprite2);
	mStarfieldSprites.push_back(sprite3);
}

void ADS::Starfield::moveStarfield(float dt)
{
	for (unsigned int i = 0; i < mStarfieldSprites.size(); i++)
	{
		float movement = GAME_BACKGROUND_SPEED * dt;
		mStarfieldSprites.at(i).move(0.0f, movement);

		if (mStarfieldSprites.at(i).getPosition().y >
			mData->window.getSize().y)
		{
			sf::Vector2f position(mStarfieldSprites.at(i).getPosition().x,
				-mStarfieldSprites.at(i).getLocalBounds().height);
			mStarfieldSprites.at(i).setPosition(position);
		}
	}
}

void ADS::Starfield::drawStarfield()
{
	for (unsigned int i = 0; i < mStarfieldSprites.size(); i++)
	{
		mData->window.draw(mStarfieldSprites.at(i));
	}
}

const std::vector<sf::Sprite>& ADS::Starfield::getSprites() const
{
	return mStarfieldSprites;
}

#include "explosion.h"

ADS::Explosion::Explosion(GameDataRef data, 
	            ExplosionProperties properties, 
	            sf::Vector2f position) 
	: mData(data), mProperties(properties)
{
	// Setup the frame stream
	mLoopFrameStream.create(mData->assets.getTexture(properties.name),
		properties.frameSize, properties.frameCount,
		properties.frameTime, false);

	// Setup animation
	mAnim = new Animation(mLoopFrameStream);

	mExplosionSprite = mAnim->getSprite();

	// Place explosion on sprite being exploded
	mAnim->setPosition(position);

	sf::Vector2f origin = sf::Vector2f(mExplosionSprite.getGlobalBounds().width / 2,
		mExplosionSprite.getGlobalBounds().height / 2);
	mAnim->setOrigin(origin);
	frameNumber = 0;
}

ADS::Explosion::~Explosion()
{
	if (mAnim)
		delete mAnim;
}

void ADS::Explosion::draw()
{
	mAnim->draw(mData->window, mAnim->getPosition(), 0);
}

void ADS::Explosion::update(float dt)
{
	mAnim->update(sf::seconds(dt));
}

ADS::AnimationStatus ADS::Explosion::getAnimationStatus() const
{
	return mAnim->getAnimationStatus();
}

const sf::Sprite & ADS::Explosion::getSprite() const
{
	return mAnim->getSprite();
}

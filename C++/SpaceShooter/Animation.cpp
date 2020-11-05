#include "Animation.h"
//#include "LoopFrameStream.h"

#include <iostream>

ADS::Animation::Animation(FrameStream const & stream, sf::Vector2f origin, sf::Time initialTime) : mStream(0), mOrigin(origin)
{
	setFrameStream(stream);
	restart(initialTime);
	mAnimationStatus = ADS::AnimationStatus::Running;
	if (mStream)
		mAnimationRunTime = mStream->getCount() * mStream->getFrameTime().asSeconds();

}

void ADS::Animation::setFrameStream(FrameStream const & stream)
{
	mStream = &stream;
	if (mStream)
		mAnimationRunTime = mStream->getCount() * mStream->getFrameTime().asSeconds();
	updateRender();
}

void ADS::Animation::setOrigin(sf::Vector2f origin)
{
	mOrigin = origin;
}

void ADS::Animation::restart(sf::Time initialTime)
{
	mTimeElapsed = initialTime;
	mAnimationStatus = ADS::AnimationStatus::Running;
	updateRender();
}

void ADS::Animation::update(sf::Time dt)
{
	//std::cout << "ADS::Animation::update" << std::endl;
	mTimeElapsed += dt;
	int elapsedMilliseconds = mTimeElapsed.asSeconds();
	if (elapsedMilliseconds <= mAnimationRunTime)
		updateRender();
	else
		mAnimationStatus = ADS::AnimationStatus::Stop;
}

void ADS::Animation::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Note: if the stream was not set it will simply draw nothing, like a sprite without any texture
	if (mAnimationStatus == ADS::AnimationStatus::Running)
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
	}		
}

void ADS::Animation::draw(sf::RenderTarget & target, sf::Vector2f position, float rotation)
{
	if (mAnimationStatus == ADS::AnimationStatus::Running)
	{
		mSprite.setPosition(position);
		mSprite.setRotation(rotation);
		target.draw(mSprite);
	}
}



void ADS::Animation::draw(sf::RenderTarget & target)
{
	//std::cout << "ADS::Animation::draw" << std::endl;
	//mSprite.setPosition(target.getSize().x / 4 - mSprite.getGlobalBounds().width / 2, target.getSize().y / 2 - mSprite.getGlobalBounds().height / 2);
	//float x = target.getSize().x / 4.0f - mSprite.getGlobalBounds().width / 2.0f;
	//float y = target.getSize().y / 2.0f - mSprite.getGlobalBounds().height / 2.0f;
	//mSprite.setPosition(50.0, 150.0);
	if (mAnimationStatus == ADS::AnimationStatus::Running)
	{
		target.draw(mSprite);
	}
}

sf::Sprite ADS::Animation::getSprite() const
{
	return mSprite;
}

ADS::AnimationStatus ADS::Animation::getAnimationStatus() const
{
	return mAnimationStatus;
}

void ADS::Animation::updateRender()
{
	if (mStream)
	{
		Frame frame = mStream->getFrameAt(mTimeElapsed);
		
		if (frame.texture) 
			mSprite.setTexture(*frame.texture);
		mSprite.setTextureRect(frame.area);
		mSprite.setColor(frame.color);
		mSprite.setOrigin(mOrigin);
	}
}

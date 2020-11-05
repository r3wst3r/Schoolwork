#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include <SFML/Graphics.hpp>
#include "definitions.h"
#include "Game.h"
#include "Animation.h"
#include "LoopFrameStream.h"
#include <string>

namespace ADS
{
	struct ExplosionProperties
	{
		std::string name;
		sf::Vector2i frameSize;
		sf::Vector2u frameCount;
		sf::Time frameTime;
	};

	class Explosion
	{
	public:
		Explosion(GameDataRef data, 
			      ExplosionProperties properties, 
			      sf::Vector2f position);
		~Explosion();

		void draw();
		void update(float dt);
		ADS::AnimationStatus getAnimationStatus() const;
		const sf::Sprite& getSprite() const;

	private:
		GameDataRef mData;
		sf::Sprite mExplosionSprite;
		ExplosionProperties mProperties;
		LoopFrameStream mLoopFrameStream;
		Animation *mAnim;
		sf::Clock mAnimationClock;
		int frameNumber;

	};
}


#endif // !_EXPLOSION_H_


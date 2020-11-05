#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "FrameStream.h"

namespace ADS
{
	enum class AnimationStatus
	{
		Start,
		Running,
		Stop
	};

	class Animation : public sf::Drawable, public sf::Transformable
	{
	public:
		Animation(FrameStream const& stream, sf::Vector2f origin = sf::Vector2f(0.0f, 0.0f),  sf::Time initialTime = sf::Time::Zero);

		void setFrameStream(FrameStream const& stream);

		void setOrigin(sf::Vector2f origin);

		void restart(sf::Time initialTime = sf::Time::Zero);

		void update(sf::Time dt);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void draw(sf::RenderTarget& target, sf::Vector2f position, float rotation);
		virtual void draw(sf::RenderTarget& target);

		sf::Sprite getSprite() const;

		AnimationStatus getAnimationStatus() const;

	private:
		void updateRender();

	private:
		FrameStream const* mStream;	// frame stream for animation
		sf::Time mTimeElapsed;		// current time position in the animation
		sf::Sprite mSprite;			// internal renderer
		sf::Vector2f mOrigin;		// origin of the sprite to be rendered
		AnimationStatus mAnimationStatus;
		int mAnimationRunTime;
	};
}

#endif // !_ANIMATION_H_


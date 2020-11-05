#ifndef _LOOPFRAMESTREAM_H_
#define _LOOPFRAMESTREAM_H_

#include <SFML/System/Time.hpp>
#include "FrameStream.h"

#include <vector>
#include <algorithm>
#include <stdexcept>

namespace ADS
{
	class LoopFrameStream : public FrameStream
	{
	public:
		enum class HorizontalStartFromPolicy
		{
			FromLeft = 0,	// read the sprite sheet from left to right
			FromRight		// read the sprite sheet from right to left
		};

		enum class VerticalStartFromPolicy
		{
			FromTop = 0,	// read the sprite sheet from top to bottom
			FromBottom		// read the sprite sheet from bottom to top
		};

		enum class PrecedencePolicy
		{
			HorizontalFirst = 0,	// read the sprite sheet by row
			VerticalFirst			// read the spite sheet by column
		};

		struct Settings
		{
			Settings(HorizontalStartFromPolicy horizontalPolicy = HorizontalStartFromPolicy::FromLeft,
				     VerticalStartFromPolicy verticalPolicy = VerticalStartFromPolicy::FromTop,
				     PrecedencePolicy precedencePolicy = PrecedencePolicy::HorizontalFirst) :	horizontalPolicy(horizontalPolicy),
																								verticalPolicy(verticalPolicy),
																								precedencePolicy(precedencePolicy)
			{}

			HorizontalStartFromPolicy horizontalPolicy;
			VerticalStartFromPolicy verticalPolicy;
			PrecedencePolicy precedencePolicy;
		};

	public:
		LoopFrameStream();

		LoopFrameStream(LoopFrameStream const& stream);

		LoopFrameStream(sf::Texture const& texture, sf::Vector2i frameSize, sf::Vector2u frameCount, sf::Time frameTime, bool loop = true, Settings const& settings = Settings());

		LoopFrameStream& operator=(LoopFrameStream const& rhs);

		void create(sf::Texture const& texture, sf::Vector2i frameSize, sf::Vector2u frameCount, sf::Time frameTime, bool loop = true, Settings const& settings = Settings());

		virtual Frame getFrameAt(sf::Time time) const;

		int getCount() const;
		sf::Time getFrameTime() const;

	private:
		unsigned int mCount;	// number of frames
		sf::Time mFrameTime;	// frame time
		bool mLoop;				// loop mode

		std::vector<Frame> mFrames;
	};
}


#endif // !_LOOPFRAMESTREAM_H_


#ifndef _FRAMESTREAM_H_
#define _FRAMESTREAM_H_

#include <SFML/System/Time.hpp>

#include "Frame.h"

namespace ADS
{
	class FrameStream
	{
	public:
		virtual Frame getFrameAt(sf::Time time) const = 0;

		virtual ~FrameStream() {}

		virtual int getCount() const = 0;

		virtual sf::Time getFrameTime() const = 0;

	};
}

#endif // !_FRAMESTREAM_H_


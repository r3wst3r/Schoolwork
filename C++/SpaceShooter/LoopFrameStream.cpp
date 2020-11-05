#include "LoopFrameStream.h"
#include <iostream>

ADS::LoopFrameStream::LoopFrameStream() : mCount(0)
{
}

ADS::LoopFrameStream::LoopFrameStream(LoopFrameStream const & stream) : mCount(stream.mCount), mFrameTime(stream.mFrameTime), mLoop(stream.mLoop), mFrames(stream.mFrames)
{
}

ADS::LoopFrameStream::LoopFrameStream(sf::Texture const & texture, sf::Vector2i frameSize, sf::Vector2u frameCount, sf::Time frameTime, bool loop, Settings const & settings)
{
	create(texture, frameSize, frameCount, frameTime, loop, settings);
}

ADS::LoopFrameStream & ADS::LoopFrameStream::operator=(LoopFrameStream const & rhs)
{
	mCount = rhs.mCount;
	mFrameTime = rhs.mFrameTime;
	mLoop = rhs.mLoop;
	mFrames = rhs.mFrames;

	return *this;
}

void ADS::LoopFrameStream::create(sf::Texture const & texture, sf::Vector2i frameSize, sf::Vector2u frameCount, sf::Time frameTime, bool loop, Settings const & settings)
{
	// First, check some assertions
	if (frameCount == sf::Vector2u(0, 0)) throw std::invalid_argument("frameCount can't be 0");
	if (frameTime == sf::Time::Zero) throw std::invalid_argument("frameTime can't be 0");

	// Then copy some stuff
	mCount = frameCount.x * frameCount.y;
	mFrameTime = frameTime;
	mLoop = loop;

	// Initialize some other stuff
	mFrames.clear();
	mFrames.reserve(mCount);

	// Now we can create the frames

	// Define the first point according to the chosen policies
	const int initX = settings.horizontalPolicy == HorizontalStartFromPolicy::FromLeft ? 0 : texture.getSize().x - frameSize.x;
	const int initY = settings.verticalPolicy == VerticalStartFromPolicy::FromTop ? 0 : texture.getSize().y - frameSize.y;
	const int stepX = settings.horizontalPolicy == HorizontalStartFromPolicy::FromLeft ? frameSize.x : -frameSize.x;
	const int stepY = settings.verticalPolicy == VerticalStartFromPolicy::FromTop ? frameSize.y : -frameSize.y;
	const int endX = initX + frameCount.x * stepX;
	const int endY = initY + frameCount.y * stepY;

	// Create the invariants
	int x = 0;
	int y = 0;

	// Set up the loop order (X or Y first?) according to the chosen policy
	/*int& first = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? x : y;
	int& second = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? y : x;
	const int& init1st = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? initX : initY;
	const int& init2nd = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? initY : initX;
	const int step1st = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? stepX : stepY;
	const int step2nd = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? stepY : stepX;
	const int end1st = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? endX : endY;
	const int end2nd = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? endY : endX;*/

	int& first = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? y : x;
	int& second = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? x : y;
	const int& init1st = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? initY : initX;
	const int& init2nd = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? initX : initY;
	const int step1st = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? stepY : stepX;
	const int step2nd = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? stepX : stepY;
	const int end1st = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? endY : endX;
	const int end2nd = settings.precedencePolicy == PrecedencePolicy::HorizontalFirst ? endX : endY;

	// Finally we can go through the process of creating the frames
	for (first = init1st; first < end1st; first += step1st)
	{
		for (second = init2nd; second < end2nd; second += step2nd)
		{
			sf::Vector2i point(x, y);
			sf::IntRect area(point, frameSize);
			mFrames.push_back(Frame(texture, area));
		}
	}

}

ADS::Frame ADS::LoopFrameStream::getFrameAt(sf::Time time) const
{
	if (mCount == 0) throw std::runtime_error("the stream was not properly initialized");

	unsigned int frameIndex = time.asMilliseconds() / mFrameTime.asMilliseconds();

	if (mLoop) frameIndex %= mCount;
	else frameIndex = std::min(frameIndex, mCount - 1);
	//std::cout << frameIndex << std::endl;
	return mFrames[frameIndex];
}

int ADS::LoopFrameStream::getCount() const
{
	return mCount;
}

sf::Time ADS::LoopFrameStream::getFrameTime() const
{
	return mFrameTime;
}

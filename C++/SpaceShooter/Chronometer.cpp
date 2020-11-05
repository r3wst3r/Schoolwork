#include "Chronometer.h"

ADS::Chronometer::Chronometer(sf::Time initialTime)
{
	reset();
	add(initialTime);
}

sf::Time ADS::Chronometer::add(sf::Time time)
{
	mTime += time;

	if (mState == TimeState::STOPPED)
		mState = TimeState::PAUSED;

	return getElapsedTime();
}

sf::Time ADS::Chronometer::reset(bool start)
{
	sf::Time time = getElapsedTime();

	mTime = sf::Time::Zero;
	mState = TimeState::STOPPED;

	if (start)
		resume();

	return time;
}

sf::Time ADS::Chronometer::pause()
{
	if (isRunning())
	{
		mState = TimeState::PAUSED;
		mTime += mClock.getElapsedTime();
	}
	return getElapsedTime();
}

sf::Time ADS::Chronometer::resume()
{
	if (!isRunning())
	{
		mState = TimeState::RUNNING;
		mClock.restart();
	}
	return getElapsedTime();
}

sf::Time ADS::Chronometer::toggle()
{
	if (isRunning())
		pause();
	else
		resume();
	return getElapsedTime();
}

bool ADS::Chronometer::isRunning() const
{
	return mState == TimeState::RUNNING;
}

sf::Time ADS::Chronometer::getElapsedTime() const
{
	switch (mState)
	{
	case TimeState::STOPPED:
		return sf::Time::Zero;

	case TimeState::RUNNING:
		return mTime + mClock.getElapsedTime();

	case TimeState::PAUSED:
		return mTime;
	}
}

ADS::Chronometer::operator sf::Time() const
{
	return getElapsedTime();
}

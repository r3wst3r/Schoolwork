#ifndef _CHRONOMETER_H_
#define _CHRONOMETER_H_

#include <SFML/System/Clock.hpp>

namespace ADS
{
	class Chronometer
	{
	public:
		Chronometer(sf::Time initialTime = sf::Time::Zero);

		sf::Time add(sf::Time time);
		sf::Time reset(bool start = false);
		sf::Time pause();
		sf::Time resume();
		sf::Time toggle();
		bool isRunning() const;
		sf::Time getElapsedTime() const;
		operator sf::Time() const;

	private:
		sf::Time mTime;
		sf::Clock mClock;
		enum class TimeState
		{
			STOPPED,
			RUNNING,
			PAUSED
		} mState;


	};
}

#endif // !_CHRONOMETER_H_


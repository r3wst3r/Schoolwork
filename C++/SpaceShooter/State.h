#ifndef _STATE_H_
#define _STATE_H_

namespace ADS
{
	enum class EGameStates
	{
		eStop,
		eReady,
		ePlaying,
		eGameOver
	};

	class State
	{
	public:
		virtual void init() = 0;

		virtual void handleInput() = 0;
		virtual void update(float dt) = 0;
		virtual void draw(float dt) = 0;

		virtual void pause() {}
		virtual void resume() {}
	};
}

#endif // !_STATE_H_


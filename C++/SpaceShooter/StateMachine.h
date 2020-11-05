#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#include <memory>
#include <stack>

#include "State.h"

namespace ADS
{
	using StateRef = std::unique_ptr<State>;

	class StateMachine
	{
	public:
		StateMachine() {}
		~StateMachine() {}

		void addState(StateRef newState, bool isReplacing = true);
		void removeState();
		// Run at start of each loop in Game.cpp
		void processStateChanges();

		StateRef& getActiveState();

	private:
		std::stack<StateRef> mStates;
		StateRef mNewState;

		bool mIsRemoving;
		bool mIsAdding;
		bool mIsReplacing;
	};
}

#endif // !_STATEMACHINE_H_


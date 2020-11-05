#include "StateMachine.h"

#include <iostream>

void ADS::StateMachine::addState(StateRef newState, bool isReplacing)
{
	mIsAdding = true;
	mIsReplacing = isReplacing;

	mNewState = std::move(newState);
	return;
}

void ADS::StateMachine::removeState()
{
	mIsRemoving = true;
}

void ADS::StateMachine::processStateChanges()
{
	if (mIsRemoving && !mStates.empty())
	{
		
		mStates.pop();

		if (!mStates.empty())
		{
			mStates.top()->resume();
		}

		mIsRemoving = false;
	}

	if (mIsAdding)
	{
		if (!mStates.empty())
		{
			if (mIsReplacing)
			{
				mStates.pop();
			}
			else
			{
				mStates.top()->pause();
			}
		}

		mStates.push(std::move(mNewState));
		(mStates.top())->init();
		mIsAdding = false;
	}

}

ADS::StateRef & ADS::StateMachine::getActiveState()
{
	return mStates.top();
}

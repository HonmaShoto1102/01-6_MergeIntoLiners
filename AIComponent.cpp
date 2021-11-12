/*---------------------------------------------------------------------------*/
//  FILE : AIComponent.cpp
//
//         　　　           AIステートの管理クラス
//
/*===========================================================================*/
//
//                                                          Author : R.Usui
/*---------------------------------------------------------------------------*/
#include "AIComponent.h"
#include "AIState.h"
#include <cassert>

AIComponent::AIComponent(class Enemy* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mStateMap(NULL)
	,mCurrentState(nullptr)
{
}

void AIComponent::Update()
{
	if (mCurrentState)
	{
		mCurrentState->Update();
	}
}

void AIComponent::ChangeState(const std::string& name)
{
	if (mCurrentState)
	{
		mCurrentState->OnExit();
	}

	auto iter = mStateMap.find(name);
	if (iter != mStateMap.end())
	{
		mCurrentState = iter->second;
		mCurrentState->OnEnter();
	}
	
	assert(mCurrentState != nullptr);
}

std::vector<std::string> AIComponent::GetRegisteredStateName() const
{
	return mRegisteredName;
}

void AIComponent::RegisterState(AIState* state)
{
	mStateMap.emplace(state->GetName(), state);
	mRegisteredName.emplace_back(state->GetName());
}

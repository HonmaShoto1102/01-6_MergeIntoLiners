/*---------------------------------------------------------------------------*/
//  FILE : AIComponent.h
//
//         　　　           AIステートの管理クラス
//
/*===========================================================================*/
//
//                                                          Author : R.Usui
/*---------------------------------------------------------------------------*/
#pragma once
#include <unordered_map>
#include <string>
#include "Component.h"

class AIComponent : public Component
{
public:
	AIComponent(class Enemy* owner, int updateOrder = 90);

	void Update() override;
	void ChangeState(const std::string& name);

	std::vector<std::string> GetRegisteredStateName() const;
	void RegisterState(class AIState* state);
private:
	std::unordered_map<std::string, class AIState*> mStateMap;
	std::vector<std::string> mRegisteredName;
	class AIState* mCurrentState;
};

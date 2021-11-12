/*---------------------------------------------------------------------------*/
//  FILE : Component.h
//
//         �@�@�@�e�R���|�[�l���g�̊��N���X��`�w�b�_�t�@�C��
//
/*===========================================================================*/
//
//                                                          Author : R.Usui
/*---------------------------------------------------------------------------*/
#pragma once
#include <cstdint>
#include "Enemy.h"

class Component
{
public:
	Component(Enemy* owner, int updateOrder = 100)
		:mOwner(owner)
		,mUpdateOrder(updateOrder)
	{
		mOwner->AddComponent(this);
	}
	
	virtual ~Component()
	{
		mOwner->RemoveComponent(this);
	}

	virtual void Update() = 0;

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	Enemy* mOwner;
	int mUpdateOrder;
};

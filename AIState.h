/*---------------------------------------------------------------------------*/
//  FILE : AIState.h
//
//         　　　           AIステートクラスの定義
//
/*===========================================================================*/
//
//                                                          Author : R.Usui
/*---------------------------------------------------------------------------*/
#pragma once
#include <cstdint>
#include <random>
#include "Math.h"
#include "collision.h"
#include "MoveComponent.h"

class AIState
{
public:
	AIState(class AIComponent* owner, class Enemy* enemy)
		:mOwner(owner)
		,mEnemy(enemy)
		,mHorizRect(nullptr)
		,mVertRect(nullptr)
		,mRound(nullptr)
	{ }
	AIState(class AIComponent* owner, class Enemy* enemy,
		class MoveComponent* move)
		:mOwner(owner)
		,mEnemy(enemy)
		,mMoveComp(move)
		,mHorizRect(nullptr)
		,mVertRect(nullptr)
		,mRound(nullptr)
	{ }
	AIState(class AIComponent* owner, class Enemy* enemy,
		class SearchComponent* search)
		:mOwner(owner)
		,mEnemy(enemy)
		,mSearchComp(search)
		,mHorizRect(nullptr)
		,mVertRect(nullptr)
		,mRound(nullptr)
	{ }
	AIState(class AIComponent* owner, class Enemy* enemy,
		class MoveComponent* move, class SearchComponent* search)
		:mOwner(owner)
		,mEnemy(enemy)
		,mMoveComp(move)
		,mSearchComp(search)
		,mHorizRect(nullptr)
		,mVertRect(nullptr)
		,mRound(nullptr)
	{ }
	
	virtual void Update() = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	
	virtual const char* GetName() const = 0;
protected:
	class AIComponent* mOwner;
	class Enemy* mEnemy;
	class MoveComponent* mMoveComp;
	class SearchComponent* mSearchComp;
	CollisionRectangle* mHorizRect;
	CollisionRectangle* mVertRect;
	CollisionCircle* mRound;
};

/**=========================================================================================**/
//
// They are all moving around, at any time.
//
/*-------------------------------------------------------------------------------------------*/

class AIDeath : public AIState
{
public:
	AIDeath(class AIComponent* owner, class Enemy* enemy, class MoveComponent* move)
		:AIState(owner, enemy, move)
		,mAngle(0.0f)
		,mFollenSpeed(0.0f)
		,mValue(Vector2::Zero)
	{ }
	AIDeath(class AIComponent* owner, class Enemy* enemy)
		:AIState(owner, enemy)
		, mAngle(0.0f)
		, mFollenSpeed(0.0f)
		, mValue(Vector2::Zero)
	{ }

	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Death";
	}
private:
	float mAngle;
	const float mAngulerSpeed = 0.03f;
	float mFollenSpeed;
	Vector2 mValue;
};
bool IsFollingDown();


class AIPatrol : public AIState
{
public:
	AIPatrol(class AIComponent* owner, class Enemy* enemy, class MoveComponent* move)
		:AIState(owner, enemy, move)
		,mFire(nullptr)
	{ }
	AIPatrol(class AIComponent* owner, class Enemy* enemy,
		class MoveComponent* move, class SearchComponent* search)
		:AIState(owner, enemy, move, search)
		,mFire(nullptr)
	{ }
	AIPatrol(class AIComponent* owner, class Enemy* enemy,
		class MoveComponent* move, class SearchComponent* search, class Fire* fire)
		:AIState(owner, enemy, move, search)
	{
		mFire = fire;
	}

	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Patrol";
	}
private:
	class Fire* mFire;
};


class AIAttack : public AIState
{
public:
	AIAttack(class AIComponent* owner, class Enemy* enemy, 
		class MoveComponent* move, class SearchComponent* search)
		:AIState(owner, enemy, move, search)
		,mCheckCollider(new CollisionRectangle)
	{ }

	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Attack";
	}
private:
	CollisionRectangle* mCheckCollider;
};


class AIHidden : public AIState
{
public:
	AIHidden(class AIComponent* owner, class Enemy* enemy,
		class MoveComponent* move, class SearchComponent* search)
		:AIState(owner, enemy, move, search)
	{ }

	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Hidden";
	}
private:
	class AnimationC* mAnimator;
	bool mFinished = true;
};


struct TransVec
{
	Vector2 firstPiller  = Vector2(350,  500);
	Vector2 secondPiller = Vector2(1290, 500);
	Vector2 thirdPiller  = Vector2(2160, 500);
	Vector2 fourthPiller = Vector2(3070, 500);
	Vector2 leftCandle   = Vector2(880,  980);
	Vector2 centerCandle = Vector2(1780, 980);
	Vector2 rightCandle  = Vector2(2680, 980);
};
using CurrentTrans = enum
{
	FirstPiller,
	SecondPiller,
	ThirdPiller,
	FourthPiller,
	LeftCandle,
	CenterCandle,
	RightCandle,
};

class AINormal : public AIState
{
public:
	AINormal(class AIComponent* owner, class Enemy* enemy)
		:AIState(owner, enemy)
		,mDelayTimer(150)
	{ }

	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Normal";
	}
private:
	std::random_device r_d;
	std::mt19937 m_t;
	int mDelayTimer;
};


class AIMove : public AIState
{
public:
	AIMove(class AIComponent* owner, class Enemy* enemy)
		:AIState(owner, enemy)
		,mTarget(Vector2::Zero)
		,mStart(Vector2::Zero)
		,mIsStarted(false)
		,mIsMoving(false)
		,mCoeff(0.0f)
		,mCheckCollider(new CollisionRectangle)
	{ }

	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Move";
	}
private:
	Vector2 mTarget;
	Vector2 mStart;
	bool mIsStarted;
	TransVec mTrans;
	bool mIsMoving;
	float mCoeff;
	CollisionRectangle* mCheckCollider;
};


class AIFire : public AIState
{
public:
	AIFire(class AIComponent* owner, class Enemy* enemy, class Fire* fire)
		:AIState(owner, enemy)
	{ 
		mFire = fire;
	}

	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Fire";
	}
private:
	class Fire* mFire;
};


class AIMagic : public AIState
{
public:
	AIMagic(class AIComponent* owner, class Enemy* enemy, class Magic* magic)
		:AIState(owner, enemy)
		,mMagic(magic)
	{ }

	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override
	{
		return "Magic";
	}
private:
	class Magic* mMagic;
};

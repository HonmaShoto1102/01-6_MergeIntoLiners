
#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Enemy* owner, int updateOrder = 30);

	using EDir = enum
	{
		ENone = -1,
		// On Ground
		EWalkRight,
		EWalkLeft,
		// In Air
		EFlyRight,
		EFlyLeft,
		EFlyUpper,
		EFlyLower,
		// Various Dir
		EAngular,
	};

	void Update() override;

	EDir GetDirection() const { return mDirection; }
	void SetDirection(const EDir& dir) { mDirection = dir; }
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

protected:
	class Enemy* mOwner;
	// The Values for one's movement.
	EDir mDirection;
	float mAngularSpeed;
	float mForwardSpeed;
	// Check a intersect of Chip-Rect.
	CollisionRectangle* mChipCollider;
	CollisionRectangle* mCheckCollider;
};


class OnGroundComponent : public MoveComponent
{
public:
	OnGroundComponent(class Enemy* owner);

	void Update() override;

	void SetFolling(bool folling) { mFolling = folling; }
	bool GetFolling() const { return mFolling; }
private:
	// For the on ground owner.
	CollisionRectangle* mPrevRectangle;
	const float mGravAccele = 9.044f;
	// Will he foll from the ground ?
	bool mFolling;
	// If not, he has this rectangle collision, opposed to circle's.
	CollisionRectangle* mFollowRectangle;
};


class InAirComponent : public MoveComponent
{
public:
	InAirComponent(class Enemy* owner);

	void Update() override;

	void SetDisplacement(float disp) { mDisplace = disp; }
	float GetDisplacement() const { return mDisplace; }

	float mOriginSpeed;
private:
	float mDisplace;
	const float mDicaySpeed = 0.008f;
};


#include "AIState.h"
#include "AIComponent.h"
#include "Search.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "uiDisplay.h"
#include "FairyVH.h"
#include "Line.h"
#include "playerCollision.h"
#include <algorithm>
#include <cassert>


/*=================== Death =====================*/
static bool gFolling = false;
void AIDeath::Update()
{
	if (Player_GetState() == ps_backToOrigin && Player_isReturn() == false)
	{
		if (strcmp(mEnemy->GetSprite()->GetName(), "damaged") != 0)
		{
			mEnemy->ChangeAnimation("damaged");
		}
		UI_ReturnToOrigineAfterAttack(mEnemy);
		return;
	}

	if (strcmp(mEnemy->GetSprite()->GetName(), "dead") != 0)
	{
		mEnemy->ChangeAnimation("dead");
		mEnemy->GetSprite()->SetLayerChange(14);
	}
	gFolling = true;
	SpriteC* sprite = mEnemy->GetSprite();
	mAngle += mAngulerSpeed;
	sprite->SetAngle(mAngle);
	mValue.x += mFollenSpeed;
	mValue.y += 1.0f;
	sprite->SetPosition(sprite->GetPosition() + mValue);
	if (sprite->GetPosition().y > 6000)
	{
		OnExit();
	}
}
bool IsFollingDown()
{
	return gFolling;
}

void AIDeath::OnEnter()
{
	if (mMoveComp)
	{
		if (mEnemy->GetBounds())
		{
			mEnemy->RemoveRectColl();
		}
		MoveComponent::EDir dir = mMoveComp->GetDirection();
		switch (dir)
		{
		case MoveComponent::EWalkRight:
			mFollenSpeed = -0.04f;
			break;
		case MoveComponent::EWalkLeft:
			mFollenSpeed = 0.04f;
			break;
		case MoveComponent::EFlyRight:
			mFollenSpeed = -0.04f;
			break;
		case MoveComponent::EFlyLeft:
		case MoveComponent::EFlyUpper:
		case MoveComponent::EFlyLower:
			mFollenSpeed = 0.04f;
			break;
		case MoveComponent::EAngular:
			break;
		default:
			break;
		}
		if (mMoveComp)
		{
			mEnemy->RemoveComponent(mMoveComp);
		}
	}
	else
	{
		mFollenSpeed = 0.03f;
	}
	mEnemy->GetSprite()->SetLayerChange(14);
	SoundManager_PlaySE(SL_enemy_dead);
}

void AIDeath::OnExit()
{
	mEnemy->SetState(Enemy::EDead);
}
/*================================================================================================*/



/*=================== Patrol =====================*/
void AIPatrol::Update()
{
	if (mEnemy->GetHitPoint() <= 0)
	{
		mOwner->ChangeState("Death");
	}

	if (mSearchComp)
	{
		if (mSearchComp->GetSearchArea("HorizontalRange"))
		{
			mHorizRect = mSearchComp->GetSearchArea("HorizontalRange")->GetHorizontalRange();
		}
		if (mSearchComp->GetSearchArea("VerticalRange"))
		{
			mVertRect = mSearchComp->GetSearchArea("VerticalRange")->GetVerticalRange();
		}
		if (mSearchComp->GetSearchArea("CircleRange"))
		{
			mRound = mSearchComp->GetSearchArea("CircleRange")->GetCircleRange();
		}
	}

	if (mHorizRect)
	{
		for (auto& name : mOwner->GetRegisteredStateName())
		{
			if (std::strcmp(name.c_str(), "Hidden") == 0)
			{
				CollisionCircle cr_h = FairyVH_GetCurrentCollisionH();
				if (Collision_RectangleAndCircleHit(mHorizRect, &cr_h))
				{
					mEnemy->SetState(Enemy::ECollOff);
					mOwner->ChangeState("Hidden");
					break;
				}
			}
		}
	}
	if (mVertRect)
	{
		for (auto& name : mOwner->GetRegisteredStateName())
		{
			if (std::strcmp(name.c_str(), "Hidden") == 0)
			{
				CollisionCircle cr_v = FairyVH_GetCurrentCollisionV();
				if (Collision_RectangleAndCircleHit(mVertRect, &cr_v))
				{
					mEnemy->SetState(Enemy::ECollOff);
					mOwner->ChangeState("Hidden");
					break;
				}
			}
		}
	}
	if (mRound)
	{
		for (auto& name : mOwner->GetRegisteredStateName())
		{
			if (std::strcmp(name.c_str(), "Attack") == 0)
			{
				CollisionRectangle cr_p = Player_GetCollision();
				if (Collision_RectangleAndCircleHit(&cr_p, mRound))
				{
					mOwner->ChangeState("Attack");
					break;
				}
			}
		}
		if (mFire)
		{
			CollisionRectangle cr_p = Player_GetCollision();
			if (Collision_RectangleAndCircleHit(&cr_p, mRound) && !mFire->IsSpawned())
			{
				mOwner->ChangeState("Fire");
			}
		}
	}
}

void AIPatrol::OnEnter()
{
	MoveComponent::EDir dir = mMoveComp->GetDirection();
	const char* text = nullptr;
	switch (dir)
	{
	case MoveComponent::EWalkRight:
	case MoveComponent::EWalkLeft:
		text = "walk";
		break;
	case MoveComponent::EFlyRight:
	case MoveComponent::EFlyLeft:
	case MoveComponent::EFlyUpper:
	case MoveComponent::EFlyLower:
		text = "fly";
		break;
	case MoveComponent::EAngular:
		text = "normal";
		break;
	default:
		break;
	}
	mEnemy->ChangeAnimation(text);
}

void AIPatrol::OnExit()
{
}
/*================================================================================================*/



/*=================== Attack ====================*/
void AIAttack::Update()
{
	if (mEnemy->GetHitPoint() <= 0)
	{
		mOwner->ChangeState("Death");
	}
	
	mRound = mSearchComp->GetSearchArea("CircleRange")->GetCircleRange();
	mRound->radius = 1080;
	mCheckCollider->x = mEnemy->GetSprite()->GetPosX() - 100.f;
	mCheckCollider->y = mEnemy->GetSprite()->GetPosY() - 100.f;
	mCheckCollider->w = mEnemy->GetBounds()->w + 200.f;
	mCheckCollider->h = mEnemy->GetBounds()->h + 200.f;
	CollisionLine verticaLine = Line_GetCurrentLineV();
	CollisionLine horizyLine = Line_GetCurrentLineH();
	if (Collision_LineAndRectangleHit(&verticaLine, mCheckCollider) ||
		Collision_LineAndRectangleHit(&horizyLine, mCheckCollider))
	{
		return;
	}
	int mapLineNum = Line_GetAllNumber();
	for (int i = 0; i < mapLineNum; i++)
	{
		LINE* mapLine = Line_GetLineForNumberAllMAP(mapLineNum);
		CollisionLine mapLineColl = mapLine->GetColl();
		if (Collision_LineAndRectangleHit(&mapLineColl, mCheckCollider))
		{
			return;
		}
	}
	Vector2 prevPos = mEnemy->GetSprite()->GetPosition();
	Vector2 enemyToPlayer = Vector2(Player_GetPosX(), Player_GetPosY()) - prevPos;
	enemyToPlayer.Normalize();
	Vector2 currentPos = prevPos + enemyToPlayer * mMoveComp->GetForwardSpeed();
	mEnemy->GetSprite()->SetPosition(currentPos);
	CollisionRectangle* cr = mEnemy->GetBounds();
	cr->x = currentPos.x, cr->y = currentPos.y;
	mEnemy->SetBounds(cr);

	CollisionRectangle cr_p = Player_GetCollision();
	if (!Collision_RectangleAndCircleHit(&cr_p, mRound))
	{
		mRound->radius = 1000;
		mOwner->ChangeState("Patrol");
	}
}

void AIAttack::OnEnter()
{
	mEnemy->ChangeAnimation("attack");
}

void AIAttack::OnExit()
{
	
}
/*================================================================================================*/



/*=================== Hidden ====================*/
void AIHidden::Update()
{
	if (!mFinished)
	{
		if (!mAnimator->GetPlayF())
		{
			mOwner->ChangeState("Patrol");
		}
		return;
	}

	if (mSearchComp->GetSearchArea("HorizontalRange"))
	{
		mHorizRect = mSearchComp->GetSearchArea("HorizontalRange")->GetHorizontalRange();
	}
	if (mSearchComp->GetSearchArea("VerticalRange"))
	{
		mVertRect = mSearchComp->GetSearchArea("VerticalRange")->GetVerticalRange();
	}
	
	CollisionCircle cr_h = FairyVH_GetCurrentCollisionH();
	CollisionCircle cr_v = FairyVH_GetCurrentCollisionV();
	if (mHorizRect)
	{
		CollisionLine horizyLine = Line_GetCurrentLineH();
		if (Collision_LineAndRectangleHit(&horizyLine, mHorizRect))
		{
			return;
		}
		if (!Collision_RectangleAndCircleHit(mHorizRect, &cr_h))
		{
			mEnemy->ChangeAnimation("appear", false);
			mAnimator = mEnemy->GetAnimSpritesMap().find("appear")->second;
			mFinished = false;
		}
	}
	if (mVertRect)
	{
		CollisionLine verticaLine = Line_GetCurrentLineV();
		if (Collision_LineAndRectangleHit(&verticaLine, mVertRect))
		{
			return;
		}
		if (!Collision_RectangleAndCircleHit(mVertRect, &cr_v))
		{
			mEnemy->ChangeAnimation("appear", false);
			mAnimator = mEnemy->GetAnimSpritesMap().find("appear")->second;
			mFinished = false;
		}
	}
}

void AIHidden::OnEnter()
{
	mEnemy->ChangeAnimation("hidden", false);
}

void AIHidden::OnExit()
{
	mFinished = true;
	mEnemy->SetState(Enemy::EActive);
}
/*================================================================================================*/



CurrentTrans gCurrent = RightCandle;
/*==================== Normal ====================*/
void AINormal::Update()
{
	if (mEnemy->GetHitPoint() <= 0)
	{
		mOwner->ChangeState("Death");
	}

	mDelayTimer--;
	if (mDelayTimer <= 0)
	{
		m_t.seed(r_d());
		unsigned int feas = m_t() % 3;
		if (feas == 0 || feas == 1)
		{
			mOwner->ChangeState("Move");
		}
		if (feas == 2)
		{
			mOwner->ChangeState("Magic");
		}
	}
}

void AINormal::OnEnter()
{
	mEnemy->ChangeAnimation("normal");
}

void AINormal::OnExit()
{
	mDelayTimer = 150;
}
/*================================================================================================*/



/*================== Move ====================*/
void AIMove::Update()
{
	if (mEnemy->GetHitPoint() <= 0)
	{
		mOwner->ChangeState("Death");
	}
	
	if (mIsMoving)
	{
		if (!mIsStarted)
		{
			mStart = mEnemy->GetSprite()->GetPosition();
			mIsStarted = true;
		}
		CollisionRectangle* cr = mEnemy->GetBounds();
		mCoeff += 0.008f;
		if (mCoeff >= 1.0f) mCoeff = 1.0f;
		Vector2 enemy = mEnemy->GetSprite()->GetPosition();
		mEnemy->GetSprite()->SetPosition(enemy.Lerp(mStart, mTarget, mCoeff));
		cr->x = mEnemy->GetSprite()->GetPosX();
		cr->y = mEnemy->GetSprite()->GetPosY();
		mEnemy->SetBounds(cr);
		if (mCoeff == 1.0f)
		{
			mOwner->ChangeState("Normal");
			return;
		}
	}
}

void AIMove::OnEnter()
{
	Vector2 enemy = mEnemy->GetSprite()->GetPosition();
	Vector2 player = Vector2(Player_GetPosX(), Player_GetPosY());
	unsigned int toPlayer = toQuadrant(mEnemy, player);
	switch (toPlayer)
	{
	case 0:
		mEnemy->ChangeAnimation("Magic");
		break;
	case 1:
		switch (gCurrent)
		{
		case FirstPiller:
			mEnemy->ChangeAnimation("right", false);
			mTarget = mTrans.secondPiller;
			gCurrent = SecondPiller;
			break;
		case SecondPiller:
			mEnemy->ChangeAnimation("right", false);
			mTarget = mTrans.thirdPiller;
			gCurrent = ThirdPiller;
			break;
		case ThirdPiller:
			mEnemy->ChangeAnimation("right", false);
			mTarget = mTrans.fourthPiller;
			gCurrent = FourthPiller;
			break;
		case FourthPiller:
			mEnemy->ChangeAnimation("lower_left", false);
			mTarget = mTrans.centerCandle;
			gCurrent = CenterCandle;
			break;
		case LeftCandle:
			mEnemy->ChangeAnimation("upper_right", false);
			mTarget = mTrans.thirdPiller;
			gCurrent = ThirdPiller;
			break;
		case CenterCandle:
			mEnemy->ChangeAnimation("upper_left", false);
			mTarget = mTrans.secondPiller;
			gCurrent = SecondPiller;
			break;
		case RightCandle:
			mEnemy->ChangeAnimation("left", false);
			mTarget = mTrans.centerCandle;
			gCurrent = CenterCandle;
			break;
		default:
			break;
		}
		mIsMoving = true;
		break;
	case 2:
		switch (gCurrent)
		{
		case FirstPiller:
			mEnemy->ChangeAnimation("lower_right", false);
			mTarget = mTrans.centerCandle;
			gCurrent = CenterCandle;
			break;
		case SecondPiller:
			mEnemy->ChangeAnimation("left", false);
			mTarget = mTrans.firstPiller;
			gCurrent = FirstPiller;
			break;
		case ThirdPiller:
			mEnemy->ChangeAnimation("lower_left", false);
			mTarget = mTrans.leftCandle;
			gCurrent = LeftCandle;
			break;
		case FourthPiller:
			mEnemy->ChangeAnimation("lower_left", false);
			mTarget = mTrans.centerCandle;
			gCurrent = CenterCandle;
			break;
		case LeftCandle:
			mEnemy->ChangeAnimation("upper_right", false);
			mTarget = mTrans.thirdPiller;
			gCurrent = ThirdPiller;
			break;
		case CenterCandle:
			mEnemy->ChangeAnimation("upper_left", false);
			mTarget = mTrans.firstPiller;
			gCurrent = FirstPiller;
			break;
		case RightCandle:
			mEnemy->ChangeAnimation("upper_left", false);
			mTarget = mTrans.secondPiller;
			gCurrent = SecondPiller;
			break;
		default:
			break;
		}
		mIsMoving = true;
		break;
	case 3:
		switch (gCurrent)
		{
		case FirstPiller:
			mEnemy->ChangeAnimation("lower_right", false);
			mTarget = mTrans.thirdPiller;
			gCurrent = ThirdPiller;
			break;
		case SecondPiller:
			mEnemy->ChangeAnimation("left", false);
			mTarget = mTrans.firstPiller;
			gCurrent = FirstPiller;
			break;
		case ThirdPiller:
			mEnemy->ChangeAnimation("lower_left", false);
			mTarget = mTrans.leftCandle;
			gCurrent = LeftCandle;
			break;
		case FourthPiller:
			mEnemy->ChangeAnimation("left", false);
			mTarget = mTrans.secondPiller;
			gCurrent = SecondPiller;
			break;
		case LeftCandle:
			mEnemy->ChangeAnimation("right", false);
			mTarget = mTrans.centerCandle;
			gCurrent = CenterCandle;
			break;
		case CenterCandle:
			mEnemy->ChangeAnimation("right", false);
			mTarget = mTrans.rightCandle;
			gCurrent = RightCandle;
			break;
		case RightCandle:
			mEnemy->ChangeAnimation("upper_left", false);
			mTarget = mTrans.secondPiller;
			gCurrent = SecondPiller;
			break;
		default:
			break;
		}
		mIsMoving = true;
		break;
	case 4:
		switch (gCurrent)
		{
		case FirstPiller:
			mEnemy->ChangeAnimation("right", false);
			mTarget = mTrans.thirdPiller;
			gCurrent = ThirdPiller;
			break;
		case SecondPiller:
			mEnemy->ChangeAnimation("right", false);
			mTarget = mTrans.fourthPiller;
			gCurrent = FourthPiller;
			break;
		case ThirdPiller:
			mEnemy->ChangeAnimation("lower_left", false);
			mTarget = mTrans.leftCandle;
			gCurrent = LeftCandle;
			break;
		case FourthPiller:
			mEnemy->ChangeAnimation("lower_left", false);
			mTarget = mTrans.centerCandle;
			gCurrent = CenterCandle;
			break;
		case LeftCandle:
			mEnemy->ChangeAnimation("upper_right", false);
			mTarget = mTrans.thirdPiller;
			gCurrent = ThirdPiller;
			break;
		case CenterCandle:
			mEnemy->ChangeAnimation("upper_left", false);
			mTarget = mTrans.secondPiller;
			gCurrent = SecondPiller;
			break;
		case RightCandle:
			mEnemy->ChangeAnimation("left", false);
			mTarget = mTrans.centerCandle;
			gCurrent = CenterCandle;
			break;
		default:
			break;
		}
		mIsMoving = true;
		break;
	default:
		mOwner->ChangeState("Normal");
		break;
	}
}

void AIMove::OnExit()
{
	mIsStarted = false;
	mIsMoving = false;
	mCoeff = 0.0f;
}
/*================================================================================================*/



/*================== Fire ==================*/
void AIFire::Update()
{
	if (mEnemy->GetHitPoint() <= 0)
	{
		mOwner->ChangeState("Dead");
	}
	if (!mEnemy->GetAnimSpritesMap().find("spawn")->second->GetPlayF())
	{
		mOwner->ChangeState("Patrol");
	}
}

void AIFire::OnEnter()
{
	mEnemy->ChangeAnimation("spawn", false);
	mFire->Spawn();
}

void AIFire::OnExit()
{
}
/*================================================================================================*/



/*================== Magic ==================*/
void AIMagic::Update()
{
	if (mEnemy->GetHitPoint() <= 0)
	{
		mOwner->ChangeState("Death");
	}
	if (mMagic->DisCharge())
	{
		mOwner->ChangeState("Normal");
	}
}

void AIMagic::OnEnter()
{
	mMagic->Charge();
	mEnemy->ChangeAnimation("magic");
}

void AIMagic::OnExit()
{
}
/*================================================================================================*/



#include "MoveComponent.h"
#include "Enemy.h"
#include "GameScene.h"
#include "playerCollision.h"
#include "Stage.h"
#include "Line.h"

MoveComponent::MoveComponent(class Enemy* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mOwner(owner)
	,mDirection(ENone)
	,mAngularSpeed(0.0f)
	,mForwardSpeed(0.0f)
	,mCheckCollider(new CollisionRectangle)
{
	mChipCollider = new CollisionRectangle;
	mChipCollider->x = owner->GetSprite()->GetPosX();
	mChipCollider->y = owner->GetSprite()->GetPosY();
	mChipCollider->w = 20.0f;
	mChipCollider->h = 20.0f;
}

void MoveComponent::Update()
{
	SpriteC* sprite = mOwner->GetSprite();
	Vector2 pos = sprite->GetPosition();
	CollisionRectangle* cr = mOwner->GetBounds();
	switch (mDirection)
	{
	case EWalkRight:
		pos.x += mForwardSpeed;
		cr->x = pos.x, cr->y = pos.y;
		mOwner->SetBounds(cr);
		mChipCollider->x = pos.x + mOwner->GetBounds()->w;
		mChipCollider->y = pos.y + mOwner->GetBounds()->h * 0.5f;
		break;
	case EWalkLeft:
		pos.x += mForwardSpeed;
		cr->x = pos.x, cr->y = pos.y;
		mOwner->SetBounds(cr);
		mChipCollider->x = pos.x - mChipCollider->w;
		mChipCollider->y = pos.y + mOwner->GetBounds()->h * 0.5f;
		break;
	case EAngular:
		if (Player_GetPosX() >= pos.x)
		{
			mOwner->GetSprite()->SetSprteDirection(1, 1);
		}
		else if (Player_GetPosX() < pos.x)
		{
			mOwner->GetSprite()->SetSprteDirection(-1, 1);
		}
		break;
	default:
		break;
	}
	sprite->SetPosition(pos);

	// Before the on foot map blocks and front line check, do the chip's;
	int collBoxCount = Stage_GetNumberOfBlock(bl_collisionBox);
	for (int i = 0; i < collBoxCount; i++)
	{
		M_collsionBOX* mapCollBox = Stage_collisionBOX_hit(mChipCollider, i);
		if (mapCollBox == NULL)
		{
			continue;
		}
		
		switch (mDirection)
		{
		case EWalkRight:
			SetDirection(EWalkLeft);
			mOwner->GetSprite()->SetSprteDirection(-1, 1);
			SetForwardSpeed(-GetForwardSpeed());
			break;
		case EWalkLeft:
			SetDirection(EWalkRight);
			mOwner->GetSprite()->SetSprteDirection(1, 1);
			SetForwardSpeed(-GetForwardSpeed());
			break;
		default:
			break;
		}
		break;
	}
	
	// Check the chip line collision, which is a single segment.
	CollisionLine verticaLine = Line_GetCurrentLineV();
	CollisionLine horizyLine = Line_GetCurrentLineH();
	if (Collision_LineAndRectangleHit(&verticaLine, mCheckCollider) ||
		Collision_LineAndRectangleHit(&horizyLine, mCheckCollider))
	{
		switch (mDirection)
		{
		case EWalkRight:
			SetDirection(EWalkLeft);
			mOwner->GetSprite()->SetSprteDirection(-1, 1);
			SetForwardSpeed(-GetForwardSpeed());
			break;
		case EWalkLeft:
			SetDirection(EWalkRight);
			mOwner->GetSprite()->SetSprteDirection(1, 1);
			SetForwardSpeed(-GetForwardSpeed());
			break;
		case EFlyRight:
			SetDirection(EFlyLeft);
			mOwner->GetSprite()->SetSprteDirection(-1, 1);
			SetForwardSpeed(-GetForwardSpeed());
			break;
		case EFlyLeft:
			SetDirection(EFlyRight);
			mOwner->GetSprite()->SetSprteDirection(1, 1);
			SetForwardSpeed(-GetForwardSpeed());
			break;
		case EFlyUpper:
			SetDirection(EFlyLower);
			SetForwardSpeed(-GetForwardSpeed());
			break;
		case EFlyLower:
			SetDirection(EFlyUpper);
			SetForwardSpeed(-GetForwardSpeed());
			break;
		default:
			break;
		}
	}
	int mapLineNum = Line_GetAllNumber();
	for (int i = 0; i < mapLineNum; i++)
	{
		LINE* mapLine = Line_GetLineForNumberAllMAP(mapLineNum);
		CollisionLine mapLineColl = mapLine->GetColl();
		if(Collision_LineAndRectangleHit(&mapLineColl, mCheckCollider))
		{
			switch (mDirection)
			{
			case EWalkRight:
				SetDirection(EWalkLeft);
				mOwner->GetSprite()->SetSprteDirection(-1, 1);
				SetForwardSpeed(-GetForwardSpeed());
				break;
			case EWalkLeft:
				SetDirection(EWalkRight);
				mOwner->GetSprite()->SetSprteDirection(1, 1);
				SetForwardSpeed(-GetForwardSpeed());
				break;
			case EFlyRight:
				SetDirection(EFlyLeft);
				mOwner->GetSprite()->SetSprteDirection(-1, 1);
				SetForwardSpeed(-GetForwardSpeed());
				break;
			case EFlyLeft:
				SetDirection(EFlyRight);
				mOwner->GetSprite()->SetSprteDirection(1, 1);
				SetForwardSpeed(-GetForwardSpeed());
				break;
			case EFlyUpper:
				SetDirection(EFlyLower);
				SetForwardSpeed(-GetForwardSpeed());
				break;
			case EFlyLower:
				SetDirection(EFlyUpper);
				SetForwardSpeed(-GetForwardSpeed());
				break;
			default:
				break;
			}
		}
	}
}

OnGroundComponent::OnGroundComponent(class Enemy* owner)
	:MoveComponent(owner)
	,mPrevRectangle(nullptr)
	,mFolling(true)
	,mFollowRectangle(nullptr)
{
}

void OnGroundComponent::Update()
{
	MoveComponent::Update();

	Vector2 pos = mOwner->GetSprite()->GetPosition();
	CollisionRectangle* cr = mOwner->GetBounds();
	pos.y += mGravAccele;
	cr->y = pos.y;
	mOwner->GetSprite()->SetPosY(pos.y);
	mOwner->SetBounds(cr);

	if (mOwner->GetBounds())
	{
		SpriteC* sprite = mOwner->GetSprite();
		CollisionRectangle currentRectangle;
		currentRectangle.x = cr->x;
		currentRectangle.y = cr->y;
		currentRectangle.w = cr->w;
		currentRectangle.h = cr->h;
		if (mPrevRectangle == nullptr)
		{
			mPrevRectangle = &currentRectangle;
		}

		// First, check the map blocks intersect.
		int collBoxCount = Stage_GetNumberOfBlock(bl_collisionBox);
		for (int i = 0; i < collBoxCount; i++)
		{
			M_collsionBOX* mapCollBox = Stage_collisionBOX_hit(&currentRectangle, i);
			if (mapCollBox == NULL)
			{
				continue;
			}

			// Not Folling enemy has a following rectangle.
			if (!mFolling)
			{
				if (mFollowRectangle == nullptr)
				{
					mFollowRectangle = new CollisionRectangle;
				}
				mFollowRectangle->w = currentRectangle.w;
				mFollowRectangle->h = currentRectangle.h;
				switch (mDirection)
				{
				case EWalkRight:
					mFollowRectangle->x = currentRectangle.x + currentRectangle.w;
					mFollowRectangle->y = currentRectangle.y + 13.f;
					if (Stage_collisionBOX_hit(mFollowRectangle, i) == NULL)
					{
						SetDirection(EWalkLeft);
						mOwner->GetSprite()->SetSprteDirection(1, 1);
						SetForwardSpeed(-GetForwardSpeed());
					}
					break;
				case EWalkLeft:
					mFollowRectangle->x = currentRectangle.x - currentRectangle.w;
					mFollowRectangle->y = currentRectangle.y + 13.f;
					if (Stage_collisionBOX_hit(mFollowRectangle, i) == NULL)
					{
						SetDirection(EWalkRight);
						mOwner->GetSprite()->SetSprteDirection(-1, 1);
						SetForwardSpeed(-GetForwardSpeed());
					}
					break;
				default:
					break;
				}
			}
			
			// Folling and Not Folling, both are need to check on one's foot.
			if (mPrevRectangle->y + mPrevRectangle->h >= mapCollBox->GetColl().y)
			{
				sprite->SetPosY(mapCollBox->GetColl().y -
					mPrevRectangle->h);
				cr->y = sprite->GetPosY();
				continue;
			}
			// For the enemy who has a various velocity.
			if (mPrevRectangle->x <= mapCollBox->GetColl().x + mapCollBox->GetColl().w)
			{
				sprite->SetPosX(mapCollBox->GetColl().x +
					mapCollBox->GetColl().w);
				cr->x = sprite->GetPosX();
				continue;
			}
			if (mPrevRectangle->x + mPrevRectangle->w >= mapCollBox->GetColl().x)
			{
				mOwner->GetSprite()->SetPosX(mapCollBox->GetColl().x -
					mPrevRectangle->w);
				cr->x = sprite->GetPosX();
				continue;
			}
		}

		// And then, check the slope map blocks.
		int slopeBoxCount = Stage_GetNumberOfBlock(bl_diagonalBox);
		for (int i = 0; i < slopeBoxCount; i++)
		{
			M_diagonalCollisionBox* mapSlopeBox = Stage_diagonalBox_byNumber(i);

			if (mapSlopeBox != NULL)
			{
				LineStraightC* slope = mapSlopeBox->GetDiaLine();
				CollisionLine bottomLine = { 
					mPrevRectangle->x, 
					mPrevRectangle->y + mPrevRectangle->h - 10.0f,
					mPrevRectangle->x + mPrevRectangle->w,
					mPrevRectangle->y + mPrevRectangle->h - 10.0f 
				};
				CollisionLine slopeLine = slope->GetLine();
				Cross_imf ci = Collision_LineAndLineHit(bottomLine, slopeLine);
				if (ci.flag)
				{
					float Y1, Y2 = 0.0f;
					slope->GetY_formX(&Y1, bottomLine.sx);
					slope->GetY_formX(&Y2, bottomLine.ex);
					float minSEy = Math::Min(slopeLine.sy, slopeLine.ey);
					float maxSEy = Math::Max(slopeLine.sy, slopeLine.ey);
					if (Y1 > maxSEy) Y1 = maxSEy;
					if (Y2 < minSEy) Y2 = minSEy;
					float offY1 = bottomLine.sy - Y1;
					float offY2 = bottomLine.ey - Y2;
					float MaxY = Math::Max(offY1, offY2);
					mOwner->GetSprite()->SetPosY(sprite->GetPosY() - MaxY);
					cr->y = mOwner->GetSprite()->GetPosY();
				}
			}
		}
		mOwner->SetBounds(cr);

		// Then, to enemies intersect, which has a Update-Request.
		for (auto enemy : mOwner->GetGame()->GetEnemies())
		{
			if (!enemy->GetUpdateRequest())
			{
				continue;
			}

			if (enemy->GetBounds())
			{
				if (Collision_RectangleAndRectangleHit(mChipCollider, enemy->GetBounds()))
				{
					switch (mDirection)
					{
					case EWalkRight:
						SetDirection(EWalkLeft);
						mOwner->GetSprite()->SetSprteDirection(-1, 1);
						SetForwardSpeed(-GetForwardSpeed());
						break;
					case EWalkLeft:
						SetDirection(EWalkRight);
						mOwner->GetSprite()->SetSprteDirection(1, 1);
						SetForwardSpeed(-GetForwardSpeed());
						break;
					default: 
						break;
					}
					break;
				}
			}
		}
		mPrevRectangle = &currentRectangle;

		// If he has lower directed gravity, should to be fall.
		if (GetDirection() == EWalkRight || EWalkLeft)
		{
			if (mOwner->GetSprite()->GetPosY() > 6000)
			{
				mOwner->SetState(Enemy::EDead);
				return;
			}
		}
	}
}


InAirComponent::InAirComponent(Enemy* owner)
	:MoveComponent(owner)
	,mDisplace(0.0f)
	,mOriginSpeed(0.0f)
{
}

void InAirComponent::Update()
{
	SpriteC* sprite = mOwner->GetSprite();
	Vector2 pos = sprite->GetPosition();
	CollisionRectangle* cr = mOwner->GetBounds();
	Vector2 originPos = mOwner->GetInitialPosition();
	switch (mDirection)
	{
	case EFlyRight:
		if (pos.x >= originPos.x + mDisplace * 0.5f)
		{
			if (!Math::NearZero(mForwardSpeed))
			{
				mForwardSpeed -= mDicaySpeed;
			}
		}
		pos.x += mForwardSpeed;
		cr->x = pos.x, cr->y = pos.y;
		mChipCollider->x = pos.x + mOwner->GetBounds()->w;
		mChipCollider->y = pos.y + mOwner->GetBounds()->h * 0.5f;
		mCheckCollider->x = pos.x + sprite->GetWidth();
		mCheckCollider->y = pos.y;
		mCheckCollider->w = sprite->GetWidth() * 0.5f;
		mCheckCollider->h = sprite->GetHeight() * 0.5f;
		if (Math::NearZero(mForwardSpeed))
		{
			mForwardSpeed = -mOriginSpeed;
			mDirection = EFlyLeft;
		}
		break;
	case EFlyLeft:
		if (pos.x <= originPos.x - mDisplace * 0.5f)
		{
			if (!Math::NearZero(mForwardSpeed))
			{
				mForwardSpeed += mDicaySpeed;
			}
		}
		pos.x += mForwardSpeed;
		cr->x = pos.x, cr->y = pos.y;
		mChipCollider->x = pos.x - mChipCollider->w;
		mChipCollider->y = pos.y + mOwner->GetBounds()->h * 0.5f;
		mCheckCollider->x = pos.x - sprite->GetWidth() * 0.5f;
		mCheckCollider->y = pos.y;
		mCheckCollider->w = sprite->GetWidth() * 0.5f;
		mCheckCollider->h = sprite->GetHeight() * 0.5f;
		if (Math::NearZero(mForwardSpeed) || pos.x <= originPos.x - mDisplace)
		{
			mForwardSpeed = mOriginSpeed;
			mDirection = EFlyRight;
		}
		break;
	case EFlyUpper:
		if (pos.y <= originPos.y - mDisplace * 0.5f)
		{
			if (!Math::NearZero(mForwardSpeed))
			{
				mForwardSpeed += mDicaySpeed;
			}
		}
		pos.y += mForwardSpeed;
		cr->x = pos.x, cr->y = pos.y;
		mChipCollider->x = pos.x + mOwner->GetBounds()->w * 0.5f;
		mChipCollider->y = pos.y - mChipCollider->h;
		mCheckCollider->x = pos.x;
		mCheckCollider->y = pos.y - sprite->GetHeight() * 0.5f;
		mCheckCollider->w = sprite->GetWidth() * 0.5f;
		mCheckCollider->h = sprite->GetHeight() * 0.5f;
		if (Math::NearZero(mForwardSpeed) || pos.y <= originPos.y - mDisplace)
		{
			mForwardSpeed = mOriginSpeed;
			mDirection = EFlyLower;
		}
		break;
	case EFlyLower:
		if (pos.y >= originPos.y + mDisplace * 0.5f)
		{
			if (!Math::NearZero(mForwardSpeed))
			{
				mForwardSpeed -= mDicaySpeed;
			}
		}
		pos.y += mForwardSpeed;
		cr->x = pos.x, cr->y = pos.y;
		mChipCollider->x = pos.x + mOwner->GetBounds()->w * 0.5f;
		mChipCollider->y = pos.y + mOwner->GetBounds()->h;
		mCheckCollider->x = pos.x;
		mCheckCollider->y = pos.y + sprite->GetHeight();
		mCheckCollider->w = sprite->GetWidth() * 0.5f;
		mCheckCollider->h = sprite->GetHeight() * 0.5f;
		if (Math::NearZero(mForwardSpeed) || pos.y >= originPos.y + mDisplace)
		{
			mForwardSpeed = -mOriginSpeed;
			mDirection = EFlyUpper;
		}
		break;
	default: 
		break;
	}
	mOwner->GetSprite()->SetPosition(pos);
	mOwner->SetBounds(cr);

	// Before the on foot map blocks and front line check, do the chip's;
	int collBoxCount = Stage_GetNumberOfBlock(bl_collisionBox);
	for (int i = 0; i < collBoxCount; i++)
	{
		M_collsionBOX* mapCollBox = Stage_collisionBOX_hit(mChipCollider, i);
		if (mapCollBox == NULL)
		{
			continue;
		}
		switch (mDirection)
		{
		case EFlyRight:
			SetDirection(EFlyLeft);
			mOwner->GetSprite()->SetSprteDirection(-1, 1);
			mForwardSpeed = -mOriginSpeed;
			break;
		case EFlyLeft:
			SetDirection(EFlyRight);
			mOwner->GetSprite()->SetSprteDirection(1, 1);
			mForwardSpeed = mOriginSpeed;
			break;
		case EFlyUpper:
			SetDirection(EFlyLower);
			mOwner->GetSprite()->SetSprteDirection(-1, 1);
			mForwardSpeed = -mOriginSpeed;
			break;
		case EFlyLower:
			SetDirection(EFlyUpper);
			mOwner->GetSprite()->SetSprteDirection(-1, 1);
			mForwardSpeed = mOriginSpeed;
			break;
		default:
			break;
		}
	}

	for (auto enemy : mOwner->GetGame()->GetEnemies())
	{
		if (!enemy->GetUpdateRequest())
		{
			continue;
		}

		if (enemy->GetBounds())
		{
			if (Collision_RectangleAndRectangleHit(mChipCollider, enemy->GetBounds()))
			{
				switch (mDirection)
				{
				case EFlyRight:
					mForwardSpeed = -mOriginSpeed;
					SetDirection(EFlyLeft);
					mOwner->GetSprite()->SetSprteDirection(-1, 1);
					break;
				case EFlyLeft:
					mForwardSpeed = mOriginSpeed;
					SetDirection(EFlyRight);
					mOwner->GetSprite()->SetSprteDirection(1, 1);
					break;
				case EFlyUpper:
					mForwardSpeed = mOriginSpeed;
					SetDirection(EFlyLower);
					break;
				case EFlyLower:
					mForwardSpeed = -mOriginSpeed;
					SetDirection(EFlyUpper);
					break;
				case EAngular:
					break;
				default:
					break;
				}
			}
		}
	}
	MoveComponent::Update();
}

/*---------------------------------------------------------------------------*/
//  FILE : Enemy.cpp
//
// Enemies for all area, which are sometimes so special that have the "heart"
// affection a player interects, or have a stronger character than the others.
//
/*===========================================================================*/
//
//                                                          Author : R.Usui
/*---------------------------------------------------------------------------*/
#include "Enemy.h"
#include "GameScene.h"
#include "AIState.h"
#include "AIComponent.h"
#include "MoveComponent.h"
#include "Search.h"
#include "SoundManager.h"
#include "PlayerData.h"
#include "playerCollision.h"
#include "FairyVH.h"
#include "Line.h"
#include "GM.h"
#include "Stage.h"
#include "base_MapBlock.h"
#include "uiDisplay.h"
#include <algorithm>
#include <cassert>
#include <random>


Enemy::Enemy(class Game* game)
	:mState(EActive)
	,mInitialCoordinates(Vector2::Zero)
	,mInitialAIState(false)
	,mSprites(NULL)
	,mAnimSprites(NULL)
	,mIsDamaged(false)
	,mIsPlaying(false)
	,mCounter(0)
	,mPrevLife(0)
	,mIsUpdating(false)
	,mBounds(nullptr)
	,mHitPoint(0)
	,mAttackPower(0)
	,mGame(game)
{
	mGame->AddEnemy(this);
}

Enemy::~Enemy()
{	
	for (auto& anim : mAnimSprites)
	{
		delete anim.second;
		anim.second = NULL;
		FreeContainer(anim.second);
	}
	FreeContainer(mAnimSprites);
	
	for (auto& sprite : mSprites)
	{
		delete sprite.second;
		sprite.second = NULL;
		FreeContainer(sprite.second);
	}
	FreeContainer(mSprites);

	mGame->RemoveEnemy(this);

	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

/*---------------------------------------*/
const Vector2 Vector2::Zero(0.0f, 0.0f);
const Vector2 Vector2::Right(1.0f, 0.0f);
const Vector2 Vector2::Left(-1.0f, 0.0f);
const Vector2 Vector2::Up(0.0f, -1.0f);
const Vector2 Vector2::Down(0.0f, 1.0f);
/*---------------------------------------*/

void Enemy::Init()
{
	InitEnemy();
}

void Enemy::Update()
{
	if (mState == EActive || mState == ECollOff || IsFollingDown())
	{
		UpdateEnemy();
		UpdateComponents();
	}
	for (auto& anim : mAnimSprites)
	{
		if (anim.second->GetPlayF())
		{
			anim.second->Update();
			break;
		}
	}
}

void Enemy::UpdateComponents()
{
	for (auto component : mComponents)
	{
		component->Update();
	}
}

void Enemy::InitEnemy()
{
	for (auto& anim : mAnimSprites)
	{
		anim.second->Init();
	}
}

void Enemy::UpdateEnemy()
{
	if (mPrevLife != mHitPoint && mPrevLife > 0 && mIsDamaged)
	{
		if (!mIsPlaying)
		{
			mPrevAnim = GetSprite()->GetName();
			ChangeAnimation("damaged");
			SoundManager_PlaySE(SL_enemy_damaged);
			mIsPlaying = true;
		}
		mCounter++;
		if (mCounter >= mDelayTime)
		{
			mCounter = 0;
			mPrevLife = mHitPoint;
			mIsDamaged = false;
			mIsPlaying = false;
			ChangeAnimation(mPrevAnim);
		}
	}

	if (mState != ECollOff && !mIsDamaged)
	{
		if (mBounds)
		{
			mPrevLife = mHitPoint;
			CollisionRectangle cr = Player_GetCollision();
			if (Collision_RectangleAndRectangleHit(mBounds, &cr))
			{
				if (Player_GetState() == ps_default)
				{
					if (mBounds->x + mBounds->w * 0.5f < cr.x + cr.w * 0.5f)
					{
						Player_SeedDamegeMessage(mAttackPower, LIFT);
					}
					else
					{
						Player_SeedDamegeMessage(mAttackPower, RIGHT);
					}
				}
				if (Player_GetState() == ps_leaveHeart)
				{
					mHitPoint -= 5;
					mIsDamaged = true;
					SpriteC* sp = GetSprite();
					Player_SetState_backToOrigin(sp->GetPosX(), sp->GetPosY());
				}
			}

			CollisionLine verticaLine = Line_GetCurrentLineV();
			CollisionLine horizyLine = Line_GetCurrentLineH();
			CollisionPoint verticaLineTip;
			verticaLineTip.point = D3DXVECTOR2(verticaLine.ex, verticaLine.ey);
			CollisionPoint horizyLineTip;
			horizyLineTip.point = D3DXVECTOR2(horizyLine.ex, horizyLine.ey);
			if (Collision_RectangleAndPointHit(mBounds, &verticaLineTip))
			{
				mHitPoint -= 3;
				mIsDamaged = true;
			}
			if (Collision_RectangleAndPointHit(mBounds, &horizyLineTip))
			{
				mHitPoint -= 3;
				mIsDamaged = true;
			}
			if (Collision_LineAndRectangleHit(&verticaLine, mBounds))
			{
				mHitPoint -= 3;
				mIsDamaged = true;
			}
			if (Collision_LineAndRectangleHit(&horizyLine, mBounds))
			{
				mHitPoint -= 3;
				mIsDamaged = true;
			}
			int allLineNum = Line_GetAllNumber();
			for (int i = 0; i < allLineNum; i++)
			{
				LINE* mapLine = Line_GetLineForNumberAllMAP(i);
				CollisionLine cl = mapLine->GetColl();
				if (Collision_LineAndRectangleHit(&cl, mBounds))
				{
					mHitPoint -= (mapLine->fl == fl_defalt) ? 3 : 6;
					mIsDamaged = true;
				}
			}
		}
	}
}

void Enemy::AddComponent(Component* component)
{
	int order = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (order < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter, component);
}

void Enemy::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

Vector2 Enemy::GetForward() const
{
	Vector2 pos;
	pos.x = Math::Cos(GetSprite()->GetAngle());
	pos.y = -Math::Sin(GetSprite()->GetAngle());
	return pos;
}

class SpriteC* Enemy::GetSprite() const
{
	for (auto& sprite : mSprites)
	{
		if (sprite.second->GetActive())
		{
			return sprite.second;
		}
	}
	return nullptr;
}

void Enemy::ChangeAnimation(const std::string& name, bool loop)
{
	assert(name.c_str() != nullptr);
	
	Vector2 pos;
	for (auto& sprite : mSprites)
	{
		if (sprite.second->GetActive())
		{
			pos = sprite.second->GetPosition();
			sprite.second->SetActive(false);
			break;
		}
	}
	
	mSprites.find(name)->second->SetActive(true);
	mSprites.find(name)->second->SetPosition(pos);
	mAnimSprites.find(name)->second->Play(loop);
}

void Timer::Invoke(const std::function <void()>& func, int delay)
{
	mInvokeList.emplace_back(std::make_pair<>(mCounter + delay, func));
}

void Timer::Update()
{
	if (!mPaused)
	{
		mCounter++;
		for (auto iter = mInvokeList.begin(); iter != mInvokeList.end(); )
		{
			if (mCounter > iter->first)
			{
				iter->second();
				iter = mInvokeList.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void Timer::Pause()
{
	mPaused = true;
}

void Timer::Play()
{
	mPaused = false;
}


/*!
* @Coronbot
*/
Coronbot::Coronbot(class Game* game, float x, float y, const char* type, int id)
	:Enemy(game)
	,mID(id)
{
	SetInitialPosition(Vector2(x, y));

	/*  walk  */
	SpriteC* walk = new SpriteC("Asset/EnemyAnim/coronbot_walk.png", "walk", 8, SPRITE_OBJ);
	walk->SetActive(true);
	walk->SetPosition(x, y);
	RegisterSprite("walk", walk);
	/*  damaged  */
	SpriteC* damaged = new SpriteC("Asset/EnemyAnim/coronbot_damaged.png", "damaged", 8, SPRITE_OBJ);
	damaged->SetActive(false);
	RegisterSprite("damaged", damaged);
	/*  dead  */
	SpriteC* dead = new SpriteC("Asset/EnemyAnim/coronbot_dead.png", "dead", 8, SPRITE_OBJ);
	dead->SetActive(false);
	RegisterSprite("dead", dead);

	CollisionRectangle* cr = new CollisionRectangle;
	cr->x = x, cr->y = y;
	cr->w = 157, cr->h = 265;
	SetBounds(cr);

	mMoveComp = new OnGroundComponent(this);
	mMoveComp->SetFolling(true);

	if (strcmp(type, "walk_right") == 0)
	{
		GetSprite()->SetSprteDirection(1, 1);
		mMoveComp->SetDirection(mMoveComp->EWalkRight);
		mMoveComp->SetForwardSpeed(1.0f);
	}
	else if (strcmp(type, "walk_left") == 0)
	{
		GetSprite()->SetSprteDirection(-1, 1);
		mMoveComp->SetDirection(mMoveComp->EWalkLeft);
		mMoveComp->SetForwardSpeed(-1.0f);
	}

	mAiComp = new AIComponent(this);
	mAiComp->RegisterState(new AIPatrol(mAiComp, this, mMoveComp));
	mAiComp->RegisterState(new AIDeath(mAiComp, this, mMoveComp));

	SetHitPoint(3);
	SetAttackPower(1);
}

Coronbot::~Coronbot()
{
	auto iter = std::find(GetGame()->GetEnemies().begin(),
		GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Coronbot::InitEnemy()
{
	for (auto& sprite : GetSpritesMap())
	{
		sprite.second->Init();
		sprite.second->SetScale(1.0f, 1.0f);
		if (strcmp(sprite.second->GetName(), "walk") == 0)
		{
			sprite.second->SetCutSize((int)989 / 6, 271);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 6, { 0,0 }, 25, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "damaged") == 0)
		{
			sprite.second->SetCutSize((int)320 / 2, 266);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 2, { 0,0 }, 15, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "dead") == 0)
		{
			sprite.second->SetCutSize(157, 265);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 1, { 0,0 }, 10, sprite.second->GetName()));
		}
	}
}

void Coronbot::UpdateEnemy()
{
	Enemy::UpdateEnemy();

	if (GetInitialAIState())
	{
		mAiComp->ChangeState("Patrol");
		SetInitialAIState(false);
	}
	if (IsFollingDown() && mID >= 0)
	{
		Stage_heartBoxCreate(mID);
	}
}
/*-----------------------------------------------------------------------------------*/


/*!
* @Digbot
*/
Digbot::Digbot(Game* game, float x, float y, const char* type, int id)
	:Enemy(game)
	,mID(id)
{
	SetInitialPosition(Vector2(x, y));

	/*  damaged  */
	SpriteC* damaged = new SpriteC("Asset/EnemyAnim/digbot_damaged.png", "damaged", 8, SPRITE_OBJ);
	damaged->SetActive(false);
	RegisterSprite("damaged", damaged);
	/*  dead  */
	SpriteC* dead = new SpriteC("Asset/EnemyAnim/digbot_dead.png", "dead", 8, SPRITE_OBJ);
	dead->SetActive(false);
	RegisterSprite("dead", dead);
	/*  walk  */
	SpriteC* walk = new SpriteC("Asset/EnemyAnim/digbot_walk.png", "walk", 8, SPRITE_OBJ);
	walk->SetActive(true);
	walk->SetPosition(x, y);
	RegisterSprite("walk", walk);
	/*  hidden  */
	SpriteC* hidden = new SpriteC("Asset/EnemyAnim/digbot_hidden.png", "hidden", 8, SPRITE_OBJ);
	hidden->SetActive(false);
	RegisterSprite("hidden", hidden);
	/*  appear  */
	SpriteC* appear = new SpriteC("Asset/EnemyAnim/digbot_appear.png", "appear", 8, SPRITE_OBJ);
	appear->SetActive(false);
	RegisterSprite("appear", appear);

	CollisionRectangle* cr = new CollisionRectangle;
	cr->x = x, cr->y = y;
	cr->w = 116, cr->h = 265;
	SetBounds(cr);

	mMoveComp = new OnGroundComponent(this);
	mMoveComp->SetFolling(false);
	
	if (strcmp(type, "walk_right") == 0)
	{
		mMoveComp->SetDirection(mMoveComp->EWalkRight);
		GetSprite()->SetSprteDirection(1, 1);
		mMoveComp->SetForwardSpeed(1.3f);
	}
	if (strcmp(type, "walk_left") == 0)
	{
		mMoveComp->SetDirection(mMoveComp->EWalkLeft);
		GetSprite()->SetSprteDirection(-1, 1);
		mMoveComp->SetForwardSpeed(-1.3f);
	}
	mSearchComp = new SearchComponent(this);
	mSearchComp->RegisterSearchRange(new HorizontalRange(this));

	mAiComp = new AIComponent(this);
	mAiComp->RegisterState(new AIPatrol(mAiComp, this, mMoveComp, mSearchComp));
	mAiComp->RegisterState(new AIHidden(mAiComp, this, mMoveComp, mSearchComp));
	mAiComp->RegisterState(new AIDeath(mAiComp, this, mMoveComp));

	SetHitPoint(3);
	SetAttackPower(1);
}

Digbot::~Digbot()
{
	auto iter = std::find(GetGame()->GetEnemies().begin(),
		GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Digbot::InitEnemy()
{
	for (auto& sprite : GetSpritesMap())
	{
		sprite.second->Init();
		sprite.second->SetScale(1.0f, 1.0f);
		if (strcmp(sprite.second->GetName(), "walk") == 0)
		{
			sprite.second->SetCutSize((int)873 / 6, 267);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 6, { 0,0 }, 25, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "hidden") == 0)
		{
			sprite.second->SetCutSize((int)975 / 7, 270);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 7, { 0,0 }, 8, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "appear") == 0)
		{
			sprite.second->SetCutSize((int)975 / 7, 270);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 7, { 0,0 }, 8, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "damaged") == 0)
		{
			sprite.second->SetCutSize((int)266 / 2, 277);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 2, { 0,0 }, 15, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "dead") == 0)
		{
			sprite.second->SetCutSize(116, 265);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 1, { 0,0 }, 10, sprite.second->GetName()));
		}
	}
}

void Digbot::UpdateEnemy()
{
	Enemy::UpdateEnemy();

	if (GetInitialAIState())
	{
		mAiComp->ChangeState("Patrol");
		SetInitialAIState(false);
	}
	if (IsFollingDown() && mID >= 0)
	{
		Stage_heartBoxCreate(mID);
	}
}
/*-----------------------------------------------------------------------------------*/


/*!
* @Garabot
*/
Garabot::Garabot(Game* game, float x, float y, const char* type, int id)
	:Enemy(game)
	,mID(id)
{
	SetInitialPosition(Vector2(x, y));

	/*  damaged  */
	SpriteC* damaged = new SpriteC("Asset/EnemyAnim/digbot_damaged.png", "damaged", 8, SPRITE_OBJ);
	damaged->SetActive(false);
	damaged->SetColor(255, 33, 33);
	RegisterSprite("damaged", damaged);
	/*  dead  */
	SpriteC* dead = new SpriteC("Asset/EnemyAnim/digbot_dead.png", "dead", 8, SPRITE_OBJ);
	dead->SetActive(false);
	dead->SetColor(255, 33, 33);
	RegisterSprite("dead", dead);
	/*  walk  */
	SpriteC* walk = new SpriteC("Asset/EnemyAnim/digbot_walk.png", "walk", 8, SPRITE_OBJ);
	walk->SetActive(true);
	walk->SetColor(255, 33, 33);
	walk->SetPosition(x, y);
	RegisterSprite("walk", walk);
	/*  hidden  */
	SpriteC* hidden = new SpriteC("Asset/EnemyAnim/digbot_hidden.png", "hidden", 8, SPRITE_OBJ);
	hidden->SetActive(false);
	hidden->SetColor(255, 33, 33);
	RegisterSprite("hidden", hidden);
	/*  appear  */
	SpriteC* appear = new SpriteC("Asset/EnemyAnim/digbot_appear.png", "appear", 8, SPRITE_OBJ);
	appear->SetActive(false);
	appear->SetColor(255, 33, 33);
	RegisterSprite("appear", appear);

	CollisionRectangle* cr = new CollisionRectangle;
	cr->x = x, cr->y = y;
	cr->w = 116, cr->h = 265;
	SetBounds(cr);

	mMoveComp = new OnGroundComponent(this);
	mMoveComp->SetFolling(false);

	if (strcmp(type, "walk_right") == 0)
	{
		mMoveComp->SetDirection(mMoveComp->EWalkRight);
		mMoveComp->SetForwardSpeed(2.0f);
		GetSprite()->SetSprteDirection(1, 1);
	}
	if (strcmp(type, "walk_left") == 0)
	{
		mMoveComp->SetDirection(mMoveComp->EWalkLeft);
		mMoveComp->SetForwardSpeed(-2.0f);
		GetSprite()->SetSprteDirection(-1, 1);
	}
	mSearchComp = new SearchComponent(this);
	mSearchComp->RegisterSearchRange(new VerticalRange(this));

	mAiComp = new AIComponent(this);
	mAiComp->RegisterState(new AIPatrol(mAiComp, this, mMoveComp, mSearchComp));
	mAiComp->RegisterState(new AIHidden(mAiComp, this, mMoveComp, mSearchComp));
	mAiComp->RegisterState(new AIDeath(mAiComp, this, mMoveComp));

	SetHitPoint(6);
	SetAttackPower(2);
}

Garabot::~Garabot()
{
	auto iter = std::find(GetGame()->GetEnemies().begin(),
		GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Garabot::InitEnemy()
{
	for (auto& sprite : GetSpritesMap())
	{
		sprite.second->Init();
		sprite.second->SetScale(1.0f, 1.0f);
		if (strcmp(sprite.second->GetName(), "walk") == 0)
		{
			sprite.second->SetCutSize((int)873 / 6, 267);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 6, { 0,0 }, 25, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "hidden") == 0)
		{
			sprite.second->SetCutSize((int)975 / 7, 270);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 7, { 0,0 }, 8, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "appear") == 0)
		{
			sprite.second->SetCutSize((int)975 / 7, 270);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 7, { 0,0 }, 8, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "damaged") == 0)
		{
			sprite.second->SetCutSize((int)266 / 2, 277);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 2, { 0,0 }, 15, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "dead") == 0)
		{
			sprite.second->SetCutSize(116, 265);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 1, { 0,0 }, 10, sprite.second->GetName()));
		}
	}
}

void Garabot::UpdateEnemy()
{
	Enemy::UpdateEnemy();

	if (GetInitialAIState())
	{
		mAiComp->ChangeState("Patrol");
		SetInitialAIState(false);
	}
	if (IsFollingDown() && mID >= 0)
	{
		Stage_heartBoxCreate(mID);
	}
}
/*-----------------------------------------------------------------------------------*/


/*!
* @Wingy
*/
Wingy::Wingy(class Game* game, float x, float y, const char* type, int id)
	:Enemy(game)
	,mID(id)
{
	SetInitialPosition(Vector2(x, y));

	/*  fly  */
	SpriteC* fly = new SpriteC("Asset/EnemyAnim/wingy_fly.png", "fly", 8, SPRITE_OBJ);
	fly->SetActive(true);
	fly->SetPosition(x, y);
	RegisterSprite("fly", fly);
	/*  damaged  */
	SpriteC* damaged = new SpriteC("Asset/EnemyAnim/wingy_damaged.png", "damaged", 8, SPRITE_OBJ);
	damaged->SetActive(false);
	RegisterSprite("damaged", damaged);
	/*  dead  */
	SpriteC* dead = new SpriteC("Asset/EnemyAnim/wingy_dead.png", "dead", 8, SPRITE_OBJ);
	dead->SetActive(false);
	RegisterSprite("dead", dead);

	CollisionRectangle* cr = new CollisionRectangle;
	cr->x = x, cr->y = y;
	cr->w = 198 * 0.7f, cr->h = 151 * 0.7f;
	SetBounds(cr);

	mMoveComp = new InAirComponent(this);
	mMoveComp->SetDisplacement(300.f);
	if (strcmp(type, "fly_right") == 0)
	{
		GetSprite()->SetSprteDirection(1, 1);
		mMoveComp->SetDirection(mMoveComp->EFlyRight);
		mMoveComp->SetForwardSpeed(4.0f);
	}
	if (strcmp(type, "fly_left") == 0)
	{
		GetSprite()->SetSprteDirection(-1, 1);
		mMoveComp->SetDirection(mMoveComp->EFlyLeft);
		mMoveComp->SetForwardSpeed(-4.0f);
	}
	if (strcmp(type, "fly_upper") == 0)
	{
		GetSprite()->SetSprteDirection(-1, 1);
		mMoveComp->SetDirection(mMoveComp->EFlyUpper);
		mMoveComp->SetForwardSpeed(-4.0f);
	}
	if (strcmp(type, "fly_lower") == 0)
	{
		GetSprite()->SetSprteDirection(-1, 1);
		mMoveComp->SetDirection(mMoveComp->EFlyLower);
		mMoveComp->SetForwardSpeed(4.0f);
	}
	mMoveComp->mOriginSpeed = Math::Abs(mMoveComp->GetForwardSpeed());

	mAiComp = new AIComponent(this);
	mAiComp->RegisterState(new AIPatrol(mAiComp, this, mMoveComp));
	mAiComp->RegisterState(new AIDeath(mAiComp, this, mMoveComp));

	SetHitPoint(5);
	SetAttackPower(2);
}

Wingy::~Wingy()
{
	auto iter = std::find(GetGame()->GetEnemies().begin(),
		GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Wingy::InitEnemy()
{
	for (auto& sprite : GetSpritesMap())
	{
		sprite.second->Init();
		sprite.second->SetScale(0.7f, 0.7f);
		if (strcmp(sprite.second->GetName(), "fly") == 0)
		{
			sprite.second->SetCutSize((int)1000 / 4, 153);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 33, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "damaged") == 0)
		{
			sprite.second->SetCutSize((int)995 / 4, 154);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 15, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "dead") == 0)
		{
			sprite.second->SetCutSize(198, 151);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 1, { 0,0 }, 10, sprite.second->GetName()));
		}
	}
}

void Wingy::UpdateEnemy()
{
	Enemy::UpdateEnemy();

	if (GetInitialAIState())
	{
		mAiComp->ChangeState("Patrol");
		SetInitialAIState(false);
	}
	if (IsFollingDown() && mID >= 0)
	{
		Stage_heartBoxCreate(mID);
	}
}
/*-----------------------------------------------------------------------------------*/


/*!
* @Liney
*/
Fire::Fire(class Enemy* owner)
	:mOwner(owner)
	,mTarget(Vector2::Zero)
{
	mSprite = new SpriteC("Asset/EnemyAnim/fire.png");
	mBounds = new CollisionRectangle;
	mBounds->w = 75, mBounds->h = 75;
}
Fire::~Fire()
{
	delete mBounds;
	mBounds = NULL;

	delete mSprite;
	mSprite = NULL;
}
void Fire::Init()
{
	mSprite->Init();
	mSprite->SetWidth(90);
	mSprite->SetHeight(90);
	mSprite->SetActive(false);
}
void Fire::Update()
{
	if (mSprite->GetActive())
	{
		mSprite->SetPosition(mSprite->GetPosition() + mTarget * mSpeed);
		mBounds->x = mSprite->GetPosX(), mBounds->y = mSprite->GetPosY();
		CollisionRectangle cr = Player_GetCollision();
		if (Collision_RectangleAndRectangleHit(mBounds, &cr))
		{
			Player_SeedDamegeMessage(5, RIGHT);
		}
		mTimeCounter++;
		if (mTimeCounter >= mActiveTime)
		{
			mTimeCounter = 0;
			mSprite->SetPosition(-400, -400);
			mBounds->y = -400;
			mSprite->SetActive(false);
		}
	}
}
void Fire::Spawn()
{
	mSprite->SetPosition(mOwner->GetSprite()->GetPosition() + Vector2(30, 50));
	Vector2 mainTarget;
	mainTarget.x = Player_GetPosX();
	mainTarget.y = Player_GetPosY();
	mTarget = mainTarget - mSprite->GetPosition();
	mTarget.Normalize();
	mSprite->SetActive(true);
}
bool Fire::IsSpawned() const
{
	return mSprite->GetActive();
}

Liney::Liney(class Game* game, float x, float y, const char* type, int id)
	:Enemy(game)
	,mID(id)
{
	SetInitialPosition(Vector2(x, y));

	/*  walk  */
	SpriteC* walk = new SpriteC("Asset/EnemyAnim/liney_walk.png", "walk", 8, SPRITE_OBJ);
	walk->SetActive(true);
	walk->SetPosition(x, y);
	RegisterSprite("walk", walk);
	/*  spawn  */
	SpriteC* spawn = new SpriteC("Asset/EnemyAnim/liney_spawn.png", "spawn", 8, SPRITE_OBJ);
	spawn->SetActive(true);
	spawn->SetPosition(x, y);
	RegisterSprite("spawn", spawn);
	/*  damaged  */
	SpriteC* damaged = new SpriteC("Asset/EnemyAnim/liney_damaged.png", "damaged", 8, SPRITE_OBJ);
	damaged->SetActive(false);
	RegisterSprite("damaged", damaged);
	/*  dead  */
	SpriteC* dead = new SpriteC("Asset/EnemyAnim/liney_dead.png", "dead", 8, SPRITE_OBJ);
	dead->SetActive(false);
	RegisterSprite("dead", dead);

	CollisionRectangle* cr = new CollisionRectangle;
	cr->x = x, cr->y = y;
	cr->w = 196 , cr->h = 277 ;
	SetBounds(cr);

	mMoveComp = new OnGroundComponent(this);
	mMoveComp->SetFolling(false);

	if (strcmp(type, "walk_right") == 0)
	{
		GetSprite()->SetSprteDirection(1, 1);
		mMoveComp->SetDirection(mMoveComp->EWalkRight);
		mMoveComp->SetForwardSpeed(1.5f);
	}
	if (strcmp(type, "walk_left") == 0)
	{
		GetSprite()->SetSprteDirection(-1, 1);
		mMoveComp->SetDirection(mMoveComp->EWalkLeft);
		mMoveComp->SetForwardSpeed(-1.5f);
	}

	mSearchComp = new SearchComponent(this);
	mSearchComp->RegisterSearchRange(new CircleRange(this, 800));
	mFire = new Fire(this);
	mAiComp = new AIComponent(this);
	mAiComp->RegisterState(new AIPatrol(mAiComp, this, mMoveComp, mSearchComp, mFire));
	mAiComp->RegisterState(new AIFire(mAiComp, this, mFire));
	mAiComp->RegisterState(new AIDeath(mAiComp, this, mMoveComp));

	SetHitPoint(10);
	SetAttackPower(3);
}

Liney::~Liney()
{
	auto iter = std::find(GetGame()->GetEnemies().begin(),
		GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Liney::InitEnemy()
{
	for (auto& sprite : GetSpritesMap())
	{
		sprite.second->Init();
		if (strcmp(sprite.second->GetName(), "walk") == 0)
		{
			sprite.second->SetCutSize((int)1476 / 6, 282);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 6, { 0,0 }, 22, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "spawn") == 0)
		{
			sprite.second->SetCutSize((int)956 / 4, 280);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 20, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "damaged") == 0)
		{
			sprite.second->SetCutSize((int)450 / 2, 275);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 2, { 0,0 }, 10, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "dead") == 0)
		{
			sprite.second->SetCutSize(196, 277);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 1, { 0,0 }, 10, sprite.second->GetName()));
		}
	}
	mFire->Init();
}

void Liney::UpdateEnemy()
{
	Enemy::UpdateEnemy();

	if (GetInitialAIState())
	{
		mAiComp->ChangeState("Patrol");
		SetInitialAIState(false);
	}
	if (IsFollingDown() && mID >= 0)
	{
		Stage_heartBoxCreate(mID);
	}
	mFire->Update();
}
/*-----------------------------------------------------------------------------------*/


/*!
* @Guardian
*/
Guardian::Guardian(class Game* game, float x, float y, const char* type, int id)
	:Enemy(game)
	, mID(id)
{
	SetInitialPosition(Vector2(x, y));

	/*  walk  */
	SpriteC* walk = new SpriteC("Asset/EnemyAnim/guardian_walk.png", "walk", 8, SPRITE_OBJ);
	walk->SetActive(true);
	walk->SetPosition(x, y);
	RegisterSprite("walk", walk);
	/*  guard  */
	SpriteC* guard = new SpriteC("Asset/EnemyAnim/wingy_guard.png", "guard", 8, SPRITE_OBJ);
	guard->SetActive(false);
	RegisterSprite("guard", guard);
	/*  sword  */
	SpriteC* sword = new SpriteC("Asset/EnemyAnim/wingy_sword.png", "sword", 8, SPRITE_OBJ);
	sword->SetActive(false);
	RegisterSprite("sword", sword);
	/*  damaged  */
	SpriteC* damaged = new SpriteC("Asset/EnemyAnim/wingy_damaged.png", "damaged", 8, SPRITE_OBJ);
	damaged->SetActive(false);
	RegisterSprite("damaged", damaged);
	/*  dead  */
	SpriteC* dead = new SpriteC("Asset/EnemyAnim/wingy_dead.png", "dead", 8, SPRITE_OBJ);
	dead->SetActive(false);
	RegisterSprite("dead", dead);

	CollisionRectangle* cr = new CollisionRectangle;
	cr->x = x, cr->y = y;
	cr->w = 198 * 0.5f, cr->h = 151 * 0.5f;
	SetBounds(cr);

	mMoveComp = new OnGroundComponent(this);
	mMoveComp->SetFolling(false);
	mMoveComp->SetDirection(MoveComponent::EWalkLeft);
	mMoveComp->SetForwardSpeed(-3.0f);

	mSearchComp = new SearchComponent(this);
	mSearchComp->RegisterSearchRange(new HorizontalRange(this));
	mSearchComp->RegisterSearchRange(new VerticalRange(this));
	mSearchComp->RegisterSearchRange(new CircleRange(this, 350.0f));

	mAiComp = new AIComponent(this);
	mAiComp->RegisterState(new AIPatrol(mAiComp, this, mMoveComp));

	SetHitPoint(999);
	SetAttackPower(4);
}

Guardian::~Guardian()
{
	auto iter = std::find(GetGame()->GetEnemies().begin(),
		GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Guardian::InitEnemy()
{
	for (auto& sprite : GetSpritesMap())
	{
		sprite.second->Init();
		sprite.second->SetScale(0.5f, 0.5f);
		if (strcmp(sprite.second->GetName(), "fly") == 0)
		{
			sprite.second->SetCutSize((int)1000 / 4, 153);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 10, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "damaged") == 0)
		{
			sprite.second->SetCutSize((int)995 / 4, 154);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 4, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "dead") == 0)
		{
			sprite.second->SetCutSize(198, 151);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 1, { 0,0 }, 10, sprite.second->GetName()));
		}
	}
}

void Guardian::UpdateEnemy()
{
	Enemy::UpdateEnemy();

	if (GetInitialAIState())
	{
		mAiComp->ChangeState("Patrol");
		SetInitialAIState(false);
	}
	if (IsFollingDown() && mID >= 0)
	{
		Stage_heartBoxCreate(mID);
	}
}
/*-----------------------------------------------------------------------------------*/


/*!
* @Ghost
*/
Ghost::Ghost(class Game* game, float x, float y, const char* type, int id)
	:Enemy(game)
	,mID(id)
	,mValue(0.0f)
{
	SetInitialPosition(Vector2(x, y));

	/*  normal  */
	SpriteC* normal = new SpriteC("Asset/EnemyAnim/ghost_normal.png", "normal", 8, SPRITE_OBJ);
	normal->SetActive(true);
	normal->SetPosition(x, y);
	RegisterSprite("normal", normal);
	/*  attack  */
	SpriteC* attack = new SpriteC("Asset/EnemyAnim/ghost_attack.png", "attack", 8, SPRITE_OBJ);
	attack->SetActive(false);
	RegisterSprite("attack", attack);
	/*  damaged  */
	SpriteC* damaged = new SpriteC("Asset/EnemyAnim/ghost_damaged.png", "damaged", 8, SPRITE_OBJ);
	damaged->SetActive(false);
	RegisterSprite("damaged", damaged);
	/*  dead  */
	SpriteC* dead = new SpriteC("Asset/EnemyAnim/ghost_dead.png", "dead", 8, SPRITE_OBJ);
	dead->SetActive(false);
	RegisterSprite("dead", dead);

	CollisionRectangle* cr = new CollisionRectangle;
	cr->x = x, cr->y = y;
	cr->w = 230 * 0.6f, cr->h = 320 * 0.6f;
	SetBounds(cr);

	mMoveComp = new MoveComponent(this);
	mMoveComp->SetForwardSpeed(2.0f);
	mMoveComp->SetDirection(MoveComponent::EAngular);

	mSearchComp = new SearchComponent(this);
	mSearchComp->RegisterSearchRange(new CircleRange(this, 1000));

	mAiComp = new AIComponent(this);
	mAiComp->RegisterState(new AIPatrol(mAiComp, this, mMoveComp, mSearchComp));
	mAiComp->RegisterState(new AIAttack(mAiComp, this, mMoveComp, mSearchComp));
	mAiComp->RegisterState(new AIDeath(mAiComp, this, mMoveComp));

	SetHitPoint(8);
	SetAttackPower(3);
}

Ghost::~Ghost()
{
	auto iter = std::find(GetGame()->GetEnemies().begin(),
		GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);
}

void Ghost::InitEnemy()
{
	for (auto& sprite : GetSpritesMap())
	{
		sprite.second->Init();
		sprite.second->SetScale(0.6f, 0.6f);
		if (strcmp(sprite.second->GetName(), "normal") == 0)
		{
			sprite.second->SetCutSize((int)994 / 4, 355);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 20, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "attack") == 0)
		{
			sprite.second->SetCutSize((int)1750 / 6, 330);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 6, { 0,0 }, 10, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "damaged") == 0)
		{
			sprite.second->SetCutSize((int)660 / 2, 327);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 2, { 0,0 }, 6, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "dead") == 0)
		{
			sprite.second->SetCutSize(227, 320);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 1, { 0,0 }, 10, sprite.second->GetName()));
		}
	}
}

void Ghost::UpdateEnemy()
{
	Enemy::UpdateEnemy();

	if (GetInitialAIState())
	{
		mAiComp->ChangeState("Patrol");
		SetInitialAIState(false);
	}
	mValue += 0.07f;
	float posY = GetSprite()->GetPosY();
	GetSprite()->SetPosY(posY + mFloatDisp * Math::Sin(mValue));
	CollisionRectangle* cr = GetBounds();
	cr->y = GetSprite()->GetPosY();
	SetBounds(cr);

	if (IsFollingDown() && mID >= 0)
	{
		Stage_heartBoxCreate(mID);
	}
}
/*-----------------------------------------------------------------------------------*/


/*!
* @Acies
*/
Magic::Magic(class Enemy* owner)
	:mOwner(owner)
	,mTarget(Vector2::Zero)
	,mValue(0.0f)
	,mBounds(nullptr)
	,mIsEmitted(false)
	,mIsPlayed(false)
	,mTimeCounter(0)
{
	mSprite = new SpriteC("Asset/EnemyAnim/magic.png", 9);
	mBounds = new CollisionRectangle;
	mBounds->w = 250 * 1.1f, mBounds->h = 250 * 1.1f;
}

Magic::~Magic()
{
	delete mBounds;
	mBounds = NULL;

	delete mSprite;
	mSprite = NULL;

	delete mAnimator;
	mAnimator = NULL;
}

void Magic::Init()
{
	mSprite->Init();
	mSprite->SetActive(false);
	mSprite->SetScale(1.3f, 1.3f);
	mSprite->SetCutSize((int)2550 / 9, 263);
	mAnimator = new AnimationC(mSprite, 9, { 0,0 }, 20);
	mAnimator->Init();
}

void Magic::Update()
{
	mAnimator->Update();
	if (mIsPlayed)
	{
		mDelayCounter++;
		if (mDelayCounter >= mDelayTimme)
		{
			mDelayCounter = 0;
			mIsPlayed = false;
			mIsEmitted = true;
			Vector2 mainTarget;
			mainTarget.x = Player_GetPosX();
			mainTarget.y = Player_GetPosY();
			mTarget = mainTarget - mSprite->GetPosition();
			mTarget.Normalize();
			SoundManager_PlaySE(SL_magic_charge);
		}
	}
	if (mIsEmitted)
	{
		mSprite->SetPosition(mSprite->GetPosition() + mTarget * mSpeed);
		mBounds->x = mSprite->GetPosX(), mBounds->y = mSprite->GetPosY();
		CollisionRectangle cr = Player_GetCollision();
		if (Collision_RectangleAndRectangleHit(mBounds, &cr))
		{
			Player_SeedDamegeMessage(6, RIGHT);
		}
		mTimeCounter++;
		if (mTimeCounter >= mActiveTime)
		{
			mTimeCounter = 0;
			mIsEmitted = false;
			mAnimator->Stop();
			mSprite->SetPosition(-400, -400);
			mSprite->SetActive(false);
		}
	}
}

void Magic::Charge()
{
	mSprite->SetPosition(mOwner->GetSprite()->GetPosition() + Vector2(300, 50));
	mSprite->SetActive(true);
	mAnimator->Play(false);
	mIsPlayed = true;
	SoundManager_PlaySE(SL_magic_charge);
}

Acies::Acies(class Game* game, float x, float y, const char* type, int id)
	:Enemy(game)
	,mID(id)
{
	SetInitialPosition(Vector2(x, y));

	/*  normal  */
	SpriteC* normal = new SpriteC("Asset/EnemyAnim/acies_normal.png", "normal", 8, SPRITE_OBJ);
	normal->SetActive(true);
	normal->SetPosition(x, y);
	RegisterSprite("normal", normal);
	/*  magic  */
	SpriteC* magic = new SpriteC("Asset/EnemyAnim/acies_magic.png", "magic", 8, SPRITE_OBJ);
	magic->SetActive(false);
	RegisterSprite("magic", magic);
	/*  right  */
	SpriteC* right = new SpriteC("Asset/EnemyAnim/acies_right.png", "right", 8, SPRITE_OBJ);
	right->SetActive(false);
	RegisterSprite("right", right);
	/*  upper_right  */
	SpriteC* upper_right = new SpriteC("Asset/EnemyAnim/acies_upper_right.png", "upper_right", 8, SPRITE_OBJ);
	upper_right->SetActive(false);
	RegisterSprite("upper_right", upper_right);
	/*  lower_right  */
	SpriteC* lower_right = new SpriteC("Asset/EnemyAnim/acies_lower_right.png", "lower_right", 8, SPRITE_OBJ);
	lower_right->SetActive(false);
	RegisterSprite("lower_right", lower_right);
	/*  left  */
	SpriteC* left = new SpriteC("Asset/EnemyAnim/acies_left.png", "left", 8, SPRITE_OBJ);
	left->SetActive(false);
	RegisterSprite("left", left);
	/*  upper_left  */
	SpriteC* upper_left = new SpriteC("Asset/EnemyAnim/acies_upper_left.png", "upper_left", 8, SPRITE_OBJ);
	upper_left->SetActive(false);
	RegisterSprite("upper_left", upper_left);
	/*  lower_left  */
	SpriteC* lower_left = new SpriteC("Asset/EnemyAnim/acies_lower_left.png", "lower_left", 8, SPRITE_OBJ);
	lower_left->SetActive(false);
	RegisterSprite("lower_left", lower_left);
	/*  damaged  */
	SpriteC* damaged = new SpriteC("Asset/EnemyAnim/acies_damaged.png", "damaged", 8, SPRITE_OBJ);
	damaged->SetActive(false);
	RegisterSprite("damaged", damaged);
	/*  dead  */
	SpriteC* dead = new SpriteC("Asset/EnemyAnim/acies_dead.png", "dead", 8, SPRITE_OBJ);
	dead->SetActive(false);
	RegisterSprite("dead", dead);

	CollisionRectangle* cr = new CollisionRectangle;
	cr->x = x, cr->y = y;
	cr->w = 642 * 0.8f, cr->h = 468 * 0.8f;
	SetBounds(cr);

	mAiComp = new AIComponent(this);
	mAiComp->RegisterState(new AINormal(mAiComp, this));
	mAiComp->RegisterState(new AIMove(mAiComp, this));
	mMagic = new Magic(this);
	mAiComp->RegisterState(new AIMagic(mAiComp, this, mMagic));
	mAiComp->RegisterState(new AIDeath(mAiComp, this));

	SetHitPoint(70);
	SetAttackPower(5);
}

Acies::~Acies()
{
	auto iter = std::find(GetGame()->GetEnemies().begin(),
		GetGame()->GetEnemies().end(), this);
	GetGame()->GetEnemies().erase(iter);

	SoundManager_StopBGM();
}

void Acies::InitEnemy()
{
	for (auto& sprite : GetSpritesMap())
	{
		sprite.second->Init();
		sprite.second->SetScale(0.8f, 0.8f);
		if (strcmp(sprite.second->GetName(), "normal") == 0)
		{
			sprite.second->SetCutSize((int)2553 / 4, 468);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 22, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "magic") == 0)
		{
			sprite.second->SetCutSize(642, 468);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 1, { 0,0 }, 10, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "right") == 0)
		{
			sprite.second->SetCutSize((int)2943 / 4, 473);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 13, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "upper_right") == 0)
		{
			sprite.second->SetCutSize((int)3024 / 4, 555);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 13, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "lower_right") == 0)
		{
			sprite.second->SetCutSize((int) 2935/ 4, 565);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 13, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "left") == 0)
		{
			sprite.second->SetCutSize((int)3041 / 4, 472);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 13, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "upper_left") == 0)
		{
			sprite.second->SetCutSize((int) 3053/ 4, 529);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 13, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "lower_left") == 0)
		{
			sprite.second->SetCutSize((int)2996 / 4, 557);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 13, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "damaged") == 0)
		{
			sprite.second->SetCutSize((int)2566 / 4, 464);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 4, { 0,0 }, 5, sprite.second->GetName()));
		}
		if (strcmp(sprite.second->GetName(), "dead") == 0)
		{
			sprite.second->SetScale(0.95f, 0.95f);
			sprite.second->SetCutSize(303, 370);
			RegisterAnimation(sprite.second->GetName(),
				new AnimationC(sprite.second, 1, { 0,0 }, 10, sprite.second->GetName()));
		}
	}
	mMagic->Init();
	SoundManager_StopBGM();
}

void Acies::UpdateEnemy()
{
	Enemy::UpdateEnemy();

	if (GetInitialAIState())
	{
		mAiComp->ChangeState("Normal");
		SetInitialAIState(false);
		SoundManager_PlayBGM(SL_BGM_LastBoss);
	}
	if (IsFollingDown() && mID >= 0)
	{
		Stage_heartBoxCreate(mID);
	}
	mMagic->Update();
}
/*-----------------------------------------------------------------------------------*/

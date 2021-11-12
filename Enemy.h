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
#pragma once
#include <cstdint>
#include <unordered_map>
#include <functional>
#include <random>
#include "base_Sprite.h"
#include "base_Animation.h" 
#include "collision.h"

class Enemy
{
public:
	// EActive  : ���̃X�e�[�g�ŏ���������A�J�������E�ɓ��������_����X�V�����B
	// ECollOff : �v���C���[�Ƃ̃R���W������OFF�ɂ���B
	// EPaused  : �G�l�~�[�̍X�V���ꎞ��~����B
	// EDead    : Game�N���X���ɂ����āA���̃X�e�[�g�̃G�l�~�[�͂��ׂč폜�����B
	using EState = enum
	{
		EActive,
		ECollOff,
		EPaused,
		EDead
	};

	Enemy(class Game* game);
	virtual ~Enemy();

	// Game���ŌĂяo��Update (not overridable)
	void Init();
	void Update();

	// Enemy�ɒǉ�����Ă��邷�ׂẴR���|�[�l���g��Update (not overridable)
	void UpdateComponents();

	// �ʂ�Enemy�̂��߂̏������E�X�V (overridable)
	virtual void InitEnemy();
	virtual void UpdateEnemy();

	// �Q�b�^�E�Z�b�^�֐�
	class SpriteC* GetSprite() const;
	std::unordered_map<std::string, class SpriteC*> GetSpritesMap() { return mSprites; }
	void RegisterSprite(const std::string& name, class SpriteC* sprite) { mSprites.emplace(name, sprite); }
	void ChangeAnimation(const std::string& name, bool loop = true);
	std::unordered_map<std::string, class AnimationC*> GetAnimSpritesMap() { return mAnimSprites; }
	void RegisterAnimation(const std::string& name, class AnimationC* anim) { mAnimSprites.emplace(name, anim); }
	Vector2 GetForward() const;
	EState GetState() const { return mState; }
	void SetState(EState state) { mState = state; }
	Vector2 GetInitialPosition() const { return mInitialCoordinates; }
	void SetInitialPosition(const Vector2& position) { mInitialCoordinates = position; }
	bool GetInitialAIState() { return mInitialAIState; }
	void SetInitialAIState(bool isAdapted) { mInitialAIState = isAdapted; }
	class Game* GetGame() { return mGame; }
	bool GetUpdateRequest() { return mIsUpdating; }
	void SetUpdateRequest(bool isSended) { mIsUpdating = isSended; }
	int GetHitPoint(void) { return mHitPoint; }
	void SetHitPoint(int hp) { mHitPoint = hp; }
	int GetAttackPower() { return mAttackPower; }
	void SetAttackPower(int attack) { mAttackPower = attack; }
	CollisionRectangle* GetBounds() const { return mBounds; }
	void SetBounds(CollisionRectangle* rect) { mBounds = rect; }
	void RemoveRectColl() { delete mBounds; }

	// �R���|�[�l���g�̒ǉ��E�폜
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	EState mState;
	// �}�b�v��̏������W
	Vector2 mInitialCoordinates;
	// ����AI�X�e�[�g�̑J�ڃt���O
	bool mInitialAIState;
	// �A�j���[�V�����`�撆��Sprite
	std::unordered_map<std::string, class SpriteC*> mSprites;
	std::unordered_map <std::string, class AnimationC* > mAnimSprites;
	// �R���W�����p�����[�^(�������Ă��Ȃ��ꍇ��nullptr)
	CollisionRectangle* mBounds;
	// �̗́E�U���͂̃p�����[�^
	int mHitPoint;
	int mAttackPower;
	
	std::vector<class Component*> mComponents;
	bool mIsDamaged;
	bool mIsPlaying;
	int mCounter;
	const int mDelayTime = 50;
	std::string mPrevAnim;
	int mPrevLife;
	bool mIsUpdating;
	class Game* mGame;
};

template <typename T>
inline void FreeContainer(T& container)
{
	T empty{};
	std::swap(container, empty);
}

class Timer
{
public:
	Timer()
		:mCounter(0)
		,mPaused(false)
		,mInvokeList(NULL)
	{ }
	void Invoke(const std::function <void()>& func, int delay);
	void Update();
	void Pause();
	void Play();
private:
	int mCounter;
	bool mPaused;
	std::list<std::pair<int, std::function<void()>>> mInvokeList;
};

/*!
* @Coronbot
*/
class Coronbot : public Enemy
{
public:
	Coronbot(class Game* game, float x, float y, const char* type, int id = -1);
	~Coronbot();

	void InitEnemy() override;
	void UpdateEnemy() override;
private:
	class AIComponent* mAiComp;
	class OnGroundComponent* mMoveComp;

	int mID;
};
/*-----------------------------------------------------------------------------------*/

/*!
* @Digbot
*/
class Digbot : public Enemy
{
public:
	Digbot(class Game* game, float x, float y, const char* type, int id = -1);
	~Digbot();

	void InitEnemy() override;
	void UpdateEnemy() override;
private:
	class AIComponent* mAiComp;
	class SearchComponent* mSearchComp;
	class OnGroundComponent* mMoveComp;

	int mID;
};
/*-----------------------------------------------------------------------------------*/

/*!
* @Garabot
*/
class Garabot : public Enemy
{
public:
	Garabot(class Game* game, float x, float y, const char* type, int id = -1);
	~Garabot();

	void InitEnemy() override;
	void UpdateEnemy() override;
private:
	class AIComponent* mAiComp;
	class SearchComponent* mSearchComp;
	class OnGroundComponent* mMoveComp;

	int mID;
};
/*-----------------------------------------------------------------------------------*/

/*!
* @Wingy
*/
class Wingy : public Enemy
{
public:
	Wingy(class Game* game, float x, float y, const char* type, int id = -1);
	~Wingy();

	void InitEnemy() override;
	void UpdateEnemy() override;
private:
	class AIComponent* mAiComp;
	class InAirComponent* mMoveComp;

	int mID;
};
/*-----------------------------------------------------------------------------------*/


/*!
* @Liney
*/
class Fire
{
public:
	Fire(class Enemy* enemy);
	~Fire();

	void Init();
	void Update();
	void Spawn();
	bool IsSpawned() const;
private:
	class Enemy* mOwner;
	class SpriteC* mSprite;
	Vector2 mTarget;
	const float mSpeed = 8.0f;
	CollisionRectangle* mBounds;
	const int mActiveTime = 250;
	int mTimeCounter;
};

class Liney : public Enemy
{
public:
	Liney(class Game* game, float x, float y, const char* type, int id = -1);
	~Liney();

	void InitEnemy() override;
	void UpdateEnemy() override;
private:
	class AIComponent* mAiComp;
	class SearchComponent* mSearchComp;
	class OnGroundComponent* mMoveComp;
	class Fire* mFire;

	int mID;
};
/*-----------------------------------------------------------------------------------*/

/*!
* @Guardian
*/
class Guardian : public Enemy
{
public:
	Guardian(class Game* game, float x, float y, const char* type, int id = -1);
	~Guardian();

	void InitEnemy() override;
	void UpdateEnemy() override;
private:
	class AIComponent* mAiComp;
	class SearchComponent* mSearchComp;
	class OnGroundComponent* mMoveComp;

	int mID;
};
/*-----------------------------------------------------------------------------------*/

/*!
* @Ghost
*/
class Ghost : public Enemy
{
public:
	Ghost(class Game* game, float x, float y, const char* type, int id = -1);
	~Ghost();

	void InitEnemy() override;
	void UpdateEnemy() override;
private:
	class AIComponent* mAiComp;
	class SearchComponent* mSearchComp;
	class MoveComponent* mMoveComp;

	int mID;

	float mValue;
	const float mFloatDisp = 5.0f;
};
/*-----------------------------------------------------------------------------------*/

/*!
* @Acies
*/
class Magic
{
public: 
	Magic(class Enemy* enemy);
	~Magic();
	
	void Init();
	void Update();
	void Charge();
	bool DisCharge() const { return mIsEmitted; }
	CollisionRectangle* GetBounds() const { return mBounds; }
private:
	class Enemy* mOwner;
	class SpriteC* mSprite;
	class AnimationC* mAnimator;
	CollisionRectangle* mBounds;
	const float mSpeed = 10.0f;
	Vector2 mTarget;
	float mValue;
	bool mIsEmitted;
	bool mIsPlayed;
	const int mActiveTime = 250;
	int mTimeCounter;
	const int mDelayTimme = 140;
	int mDelayCounter;
};

class Acies : public Enemy
{
public:
	Acies(class Game* game, float x, float y, const char* type, int id = -1);
	~Acies();

	void InitEnemy() override;
	void UpdateEnemy() override;
private:
	class AIComponent* mAiComp;
	class Magic* mMagic;
	int mID;
};
/*-----------------------------------------------------------------------------------*/

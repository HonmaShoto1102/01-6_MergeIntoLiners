
#include "TitleScene.h"
#include "Button.h"
#include "base_Sprite.h"
#include "myDirect3D.h"
#include "keyloger.h"
#include "SceneManager.h"
#include "SoundManager.h"

Title::Title()
	:mBlackAlpha(1.0f)
	,mFontsAlpha(0.0f)
	,mCoeff(0.0f)
	,mCrossCoeff(0.0f)
	,mButtonCoeff(0.0f)
	,mDelayTimer(0)
	,mTrigger(false)
{
}

void Title::Load()
{
	mStartButton = new Button("game_start", Vector2(430, 750));
	mCenterLight = new HighLight(mStartButton);
	mBgFar= new SpriteUI("Asset/Stage/3a.png", 10);
	mBgMiddle = new SpriteUI("Asset/Stage/2a.png", 11);
	mBgNear = new SpriteUI("Asset/Stage/1a.png", 12);
	mBlackBG = new SpriteUI("Asset/Fonts/white.png", 13);
	mMerge = new SpriteUI("Asset/Fonts/merge.png", 15);
	mInto = new SpriteUI("Asset/Fonts/into.png", 15);
	mLiners = new SpriteUI("Asset/Fonts/liners.png", 15);
	mKana = new SpriteUI("Asset/Fonts/kana.png", 15);
	mRightLine = new SpriteUI("Asset/Fonts/line_right.png", 15);
	mLeftLine = new SpriteUI("Asset/Fonts/line_left.png", 15);
	mCross = new SpriteUI("Asset/Fonts/cross.png", 15);
}

void Title::Init()
{
	mStartButton->Init();
	mStartButton->GetSprite()->SetWidth(970);
	mStartButton->GetSprite()->SetHeight(270);
	mStartButton->GetSprite()->SetAlpha(0.0f);
	mStartButton->SetHighLighted(false);

	mCenterLight->Init();

	mBgFar->Init();
	mBgFar->SetPosition(-2.0f, 0.0f);
	mBgFar->SetWidth(SCREEN_WIDTH+500);
	mBgFar->SetHeight(SCREEN_HEIGHT+200);

	mBgNear->Init();
	mBgNear->SetPosition(-2.0f, 0.0f);
	mBgNear->SetWidth(SCREEN_WIDTH+1000);
	mBgNear->SetHeight(SCREEN_HEIGHT+600);

	mBgMiddle->Init();
	mBgMiddle->SetPosition(-2.0f, 0.0f);
	mBgMiddle->SetWidth(SCREEN_WIDTH+700);
	mBgMiddle->SetHeight(SCREEN_HEIGHT+400);

	mBlackBG->Init();
	mBlackBG->SetPosition(0.0f, 0.0f);
	mBlackBG->SetWidth(SCREEN_WIDTH);
	mBlackBG->SetHeight(SCREEN_HEIGHT);
	mBlackBG->SetColor(0, 0, 0);
	mBlackBG->SetAlpha(1.0f);

	mMerge->Init();
	mMerge->SetPosition(150, 180);
	mMerge->SetWidth(600);
	mMerge->SetHeight(300);
	mMerge->SetAlpha(0.0f);
	mMerge->SetActive(false);

	mInto->Init();
	mInto->SetPosition(800, 160);
	mInto->SetWidth(222);
	mInto->SetHeight(120);
	mInto->SetAlpha(0.0f);
	mInto->SetActive(false);

	mLiners->Init();
	mLiners->SetPosition(1200, 460);
	mLiners->SetWidth(500);
	mLiners->SetHeight(300);
	mLiners->SetAlpha(0.0f);
	mLiners->SetActive(false);

	mKana->Init();
	mKana->SetPosition(1100, 333);
	mKana->SetWidth(500);
	mKana->SetHeight(50);
	mKana->SetAlpha(0.0f);
	mKana->SetActive(false);

	mRightLine->Init();
	mRightLine->SetPosition(mRightLineStart);
	mRightLine->SetWidth(SCREEN_WIDTH - 300);
	mRightLine->SetHeight(300);

	mLeftLine->Init();
	mLeftLine->SetPosition(mLeftLineStart);
	mLeftLine->SetWidth(SCREEN_WIDTH - 300);
	mLeftLine->SetHeight(300);

	mCross->Init();
	mCross->SetPosition(mCrossStart);
	mCross->SetWidth(250);
	mCross->SetHeight(250);

	mBlackAlpha = 1.0f;
	mFontsAlpha = 0.0f;
	mCoeff = 0.0f;
	mCrossCoeff = 0.0f;
	mButtonCoeff = 0.0f;
	mDelayTimer = 0;
	mTrigger = false;
}

void Title::Update()
{
	if (!mMerge->GetActive())
	{
		if (mCrossCoeff == 1.0f) mCoeff += 0.05f;
		mCrossCoeff += 0.008f;
		if (mCoeff >= 1.0f) mCoeff = 1.0f;
		if (mCrossCoeff >= 1.0f) mCrossCoeff = 1.0f;
		mRightLine->SetPosition(mRightLine->GetPosition().Lerp(mRightLineStart, mRightLineTarget, mCoeff));
		mLeftLine->SetPosition(mLeftLine->GetPosition().Lerp(mLeftLineStart, mLeftLineTarget, mCoeff));
		mCross->SetPosition(mCross->GetPosition().Lerp(mCrossStart, mCrossTarget, mCrossCoeff));
		if (mCoeff == 1.0f)
		{
			SoundManager_PlaySE(SL_line_drawn_up);
			SoundManager_PlayBGM(SL_BGM_Title);
			mMerge->SetActive(true);
			mInto->SetActive(true);
			mLiners->SetActive(true);
			mKana->SetActive(true);
		}
	}

	if (mMerge->GetActive())
	{
		mFontsAlpha += 0.008f;
		mBlackAlpha -= 0.008f;
		if (mFontsAlpha >= 1.0f) mFontsAlpha = 1.0f;
		mMerge->SetAlpha(mFontsAlpha);
		mInto->SetAlpha(mFontsAlpha);
		mLiners->SetAlpha(mFontsAlpha);
		mKana->SetAlpha(mFontsAlpha);
		if (mBlackAlpha <= 0.0f) mBlackAlpha = 0.0f;
		mBlackBG->SetAlpha(mBlackAlpha);
		if (mFontsAlpha == 1.0f)
		{
			mDelayTimer++;
		}
		if (mDelayTimer >= 190)
		{
			mButtonCoeff += 0.03f;
			if (mButtonCoeff >= 1.0f)
			{
				mButtonCoeff = 1.0f;
				mStartButton->SetHighLighted(true);
				if (keylogger_Trigger(KL_ENTER) || keylogger_Trigger(KL_SPACE))
				{
					SoundManager_PlaySE(SL_menu_start);
					mMerge->SetLayerChange(14);
					mInto->SetLayerChange(14);
					mLiners->SetLayerChange(14);
					mKana->SetLayerChange(14);
					mRightLine->SetLayerChange(14);
					mLeftLine->SetLayerChange(14);
					mCross->SetLayerChange(14);
					mBlackBG->SetLayerChange(15);
					mTrigger = true;
				}
				if (mTrigger)
				{
					mBlackAlpha += 0.075f;
					if (mBlackAlpha >= 1.0f) mBlackAlpha = 1.0f;
					mBlackBG->SetAlpha(mBlackAlpha);
				}
				if (mBlackAlpha >= 1.0f)
				{
					SM_SceneChange(EGame);					
				}
			}
			mStartButton->GetSprite()->SetAlpha(mButtonCoeff);
		}
	}
	mCenterLight->Update();
}

void Title::Unload()
{
	SoundManager_StopBGM();

	delete mBgFar;
	mBgFar = NULL;

	delete mBgMiddle;
	mBgMiddle = NULL;

	delete mBgNear;
	mBgNear = NULL;

	delete mBlackBG;
	mBlackBG = NULL;

	delete mCross;
	mCross = NULL;

	delete mLeftLine;
	mLeftLine = NULL;

	delete mRightLine;
	mRightLine = NULL;

	delete mKana;
	mKana = NULL;

	delete mLiners;
	mLiners = NULL;

	delete mInto;
	mInto = NULL;

	delete mMerge;
	mMerge = NULL;

	delete mCenterLight;
	mCenterLight = NULL;

	delete mStartButton;
	mStartButton = NULL;
}

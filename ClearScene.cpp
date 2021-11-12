
#include "ClearScene.h"
#include "Button.h"
#include "base_Sprite.h"
#include "keyloger.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Stage.h"
#include "Map_Manager.h"

Clear::Clear()
	:mStageCoeff(0.0f)
	,mClearCoeff(0.0f)
	,mScaling(1.0f)
	,mAlpha(0.0f)
	,mWhiteAlpha(1.0f)
	,mDelayTimer(0)
{
}

void Clear::Load()
{
	mNextStage = new Button("next_stage", Vector2(200, 400));
	mLeftLight = new HighLight(mNextStage);
	mToTitle = new Button("to_title_clear", Vector2(900, 400));
	mRightLight = new HighLight(mToTitle);
	mThanksFont = new SpriteUI("Asset/Fonts/thanks_playing.png");
	mBackGround = new SpriteUI("Asset/Fonts/white.png", 13);
	mStageFont = new SpriteUI("Asset/Fonts/STAGE.png", 15);
	mClearFont = new SpriteUI("Asset/Fonts/CLEAR.png", 15);
}

void Clear::Init()
{
	mNextStage->Init();
	mNextStage->GetSprite()->SetWidth(666);
	mNextStage->GetSprite()->SetHeight(200);
	mNextStage->GetSprite()->SetAlpha(0.0f);

	mToTitle->Init();
	mToTitle->GetSprite()->SetWidth(666);
	mToTitle->GetSprite()->SetHeight(200);
	mToTitle->GetSprite()->SetAlpha(0.0f);

	mLeftLight->Init();
	mRightLight->Init();

	mBackGround->Init();
	mBackGround->SetColor(255, 255, 255);
	mBackGround->SetWidth(SCREEN_WIDTH);
	mBackGround->SetHeight(SCREEN_HEIGHT);

	mStageFont->Init();
	mStageFont->SetPosition(mStartS);
	mStageFont->SetWidth(1000);
	mStageFont->SetHeight(300);

	mClearFont->Init();
	mClearFont->SetPosition(mStartC);
	mClearFont->SetWidth(750);
	mClearFont->SetHeight(300);

	mThanksFont->Init();
	mThanksFont->SetActive(false);
	mThanksFont->SetPosition(200, 380);
	mThanksFont->SetWidth(1500);
	mThanksFont->SetHeight(300);

	mStageCoeff = 0.0f;
	mClearCoeff = 0.0f;
	mScaling = 1.0f;
	mAlpha = 0.0f;
	mWhiteAlpha = 1.0f;
	mDelayTimer = 0;
	mNextTrigger = false;
	mReturnTrigger = false;
	mInitialTrigger = false;
	mThanksTrigger = false;

	SoundManager_PlaySE(SL_stage_clear);
}

void Clear::Update()
{
	mDelayTimer++;
	if (mDelayTimer >= 60 && mDelayTimer < 130)
	{
		mStageCoeff += 0.08f;
		if (mStageCoeff >= 1.0f) mStageCoeff = 1.0f;
		mStageFont->SetPosition(mStageFont->GetPosition().Lerp(mStartS, mTargetS, mStageCoeff));
	}
	if (mDelayTimer >= 130 && mDelayTimer < 250)
	{
		mClearCoeff += 0.08f;
		if (mClearCoeff >= 1.0f) mClearCoeff = 1.0f;
		mClearFont->SetPosition(mClearFont->GetPosition().Lerp(mStartC, mTargetC, mClearCoeff));
	}
	if (mDelayTimer >= 250 && mDelayTimer < 333)
	{
		mStageCoeff = 0.0f;
		mClearCoeff = 0.0f;
		mScaling += 0.008f;
		mStageFont->SetScale(mScaling, mScaling);
		mClearFont->SetScale(mScaling, mScaling);
	}
	if (mDelayTimer >= 333 && mDelayTimer < 444)
	{
		mStageCoeff += 0.08f;
		if (mStageCoeff >= 1.0f) mStageCoeff = 1.0f;
		mStageFont->SetPosition(mStageFont->GetPosition().Lerp(mTargetS, mStartS, mStageCoeff));
		mClearCoeff += 0.08f;
		if (mClearCoeff >= 1.0f) mClearCoeff = 1.0f;
		mClearFont->SetPosition(mClearFont->GetPosition().Lerp(mTargetC, mStartC, mClearCoeff));
		mScaling -= 0.5f;
		if (mScaling <= 0.0f) mScaling = 0.0f;
		mStageFont->SetScale(mScaling, mScaling);
		mClearFont->SetScale(mScaling, mScaling);
	}
	if (MapManager_GetStangeNumber() == 8)
	{
		mThanksTrigger = true;
	}
	if (mDelayTimer >= 444)
	{
		if (!mThanksTrigger)
		{
			mAlpha += 0.008f;
			if (mAlpha >= 1.0f)
			{
				mAlpha = 1.0f;
				if (!mInitialTrigger)
				{
					mNextStage->SetHighLighted(true);
					mInitialTrigger = true;
				}
			}
			mNextStage->GetSprite()->SetAlpha(mAlpha);
			mToTitle->GetSprite()->SetAlpha(mAlpha);
			if ((keylogger_Trigger(KL_D) || keylogger_Trigger(KL_END)) &&
				mNextStage->GetHighLighted() && !mNextTrigger && !mReturnTrigger)
			{
				mNextStage->SetHighLighted(false);
				mToTitle->SetHighLighted(true);
				SoundManager_PlaySE(SL_menu_move);
			}
			if ((keylogger_Trigger(KL_A) || keylogger_Trigger(KL_HOME)) &&
				mToTitle->GetHighLighted() && !mNextTrigger && !mReturnTrigger)
			{
				mToTitle->SetHighLighted(false);
				mNextStage->SetHighLighted(true);
				SoundManager_PlaySE(SL_menu_move);
			}
			if ((keylogger_Trigger(KL_ENTER) || keylogger_Trigger(KL_SPACE)) &&
				mNextStage->GetHighLighted() && !mNextTrigger)
			{
				mNextTrigger = true;
				SoundManager_PlaySE(SL_menu_start);
			}
			if ((keylogger_Trigger(KL_ENTER) || keylogger_Trigger(KL_SPACE)) &&
				mToTitle->GetHighLighted() && !mReturnTrigger)
			{
				mReturnTrigger = true;
				SoundManager_PlaySE(SL_menu_cancel);
			}

			if (mNextTrigger || mReturnTrigger)
			{
				mWhiteAlpha -= 0.008f;
				if (mWhiteAlpha <= 0.0f) mWhiteAlpha = 0.0f;
				mBackGround->SetColor((int)(255 * mWhiteAlpha) + 255,
					(int)(255 * mWhiteAlpha) + 255, (int)(255 * mWhiteAlpha) + 255);
				mBackGround->SetLayerChange(15);
				mNextStage->GetSprite()->SetLayerChange(13);
				mToTitle->GetSprite()->SetLayerChange(13);
				mNextStage->SetHighLighted(false);
				mToTitle->SetHighLighted(false);
				mBackGround->SetAlpha(mWhiteAlpha);
			}
			if (mWhiteAlpha <= 0.0f && mNextTrigger)
			{
				SM_SceneChange(EGame);
			}
			if (mWhiteAlpha <= 0.0f && mReturnTrigger)
			{
				SM_SceneChange(EFailure);
			}
			mLeftLight->Update();
			mRightLight->Update();
		}
		if (mThanksTrigger)
		{
			// Thank you for Playing!!
			mThanksFont->SetActive(true);
			if ((keylogger_Trigger(KL_ENTER) || keylogger_Trigger(KL_SPACE)))
			{
				SM_SceneChange(ETitle);
			}
		}
	}
}

void Clear::Unload()
{
	delete mClearFont;
	mClearFont = NULL;

	delete mStageFont;
	mStageFont = NULL;

	delete mBackGround;
	mBackGround = NULL;

	delete mNextStage;
	mNextStage = NULL;

	delete mToTitle;
	mToTitle = NULL;
}

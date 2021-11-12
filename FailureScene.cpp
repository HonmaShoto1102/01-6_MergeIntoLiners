

#include "FailureScene.h"
#include "Button.h"
#include "base_Sprite.h"
#include "keyloger.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Math.h"
#include "Stage.h"
#include "Map_Manager.h"
#include "config.h"

GameOver::GameOver()
	:mBackGround(nullptr)
	,mFonts(NULL)
	,mFollingAge(NULL)
	,mVeclocity(8.0f)
	,mFrameCount(0)
	,mAlpha(0.0f)
	,mRestartTrigger(false)
	,mReturnTrigger(false)
	,mInitialTrigger(false)
{
}

void GameOver::Load()
{
	mReStart = new Button("re_start", Vector2(200, 700));
	mLeftLight = new HighLight(mReStart);
	mToTitle = new Button("to_title", Vector2(1000, 700));
	mRightLight = new HighLight(mToTitle);

	mBackGround = new SpriteUI("Asset/Fonts/white.png", 13);

	SpriteUI* g = new SpriteUI("Asset/Fonts/G.png");
	mFonts.emplace_back(g);
	mFollingAge.emplace_back(60);
	SpriteUI* a = new SpriteUI("Asset/Fonts/A.png");
	mFonts.emplace_back(a);
	mFollingAge.emplace_back(120);
	SpriteUI* m = new SpriteUI("Asset/Fonts/M.png");
	mFonts.emplace_back(m);
	mFollingAge.emplace_back(90);
	SpriteUI* e = new SpriteUI("Asset/Fonts/E.png");
	mFonts.emplace_back(e);
	mFollingAge.emplace_back(150);
	SpriteUI* o = new SpriteUI("Asset/Fonts/O.png");
	mFonts.emplace_back(o);
	mFollingAge.emplace_back(120);
	SpriteUI* v = new SpriteUI("Asset/Fonts/V.png");
	mFonts.emplace_back(v);
	mFollingAge.emplace_back(60);
	SpriteUI* e_2 = new SpriteUI("Asset/Fonts/E.png");
	mFonts.emplace_back(e_2);
	mFollingAge.emplace_back(150);
	SpriteUI* r = new SpriteUI("Asset/Fonts/R.png");
	mFonts.emplace_back(r);
	mFollingAge.emplace_back(90);
}

void GameOver::Init()
{
	mReStart->Init();
	mReStart->GetSprite()->SetWidth(666);
	mReStart->GetSprite()->SetHeight(200);
	mReStart->GetSprite()->SetAlpha(0.0f);
	mReStart->SetHighLighted(false);

	mLeftLight->Init();
	mRightLight->Init();

	mToTitle->Init();
	mToTitle->GetSprite()->SetWidth(666);
	mToTitle->GetSprite()->SetHeight(200);
	mToTitle->GetSprite()->SetAlpha(0.0f);
	mToTitle->SetHighLighted(false);

	mBackGround->Init();
	mBackGround->SetColor(0, 0, 0);
	mBackGround->SetWidth(SCREEN_WIDTH);
	mBackGround->SetHeight(SCREEN_HEIGHT);
	
	float temp = 50.0f;
	for (size_t i = 0; i < mFonts.size(); i++)
	{
		mFonts.at(i)->Init();
		mFonts.at(i)->SetScale(4.6f, 4.6f);
		mFonts.at(i)->SetActive(false);
		if (i < 4)
		{
			mFonts.at(i)->SetPosition(temp, -300.0f);
		}
		if (i == 4)
		{
			mFonts.at(i)->SetPosition(temp + 100.0f, -200.0f);
		}
		else
		{
			mFonts.at(i)->SetPosition(temp + 100.0f, -250.0f);
		}
		temp += 200.0f;
	}

	mVeclocity = 8.0f;
	mFollingAge.clear();
	mAlpha = 0.0f;
	mWhiteAlpha = 1.0f;
	mRestartTrigger = false;
	mReturnTrigger = false;
	mInitialTrigger = false;

	SoundManager_PlayBGM(SL_BGM_GameOver);
}

void GameOver::Update()
{
	for (size_t i = 0; i < mFonts.size(); i++)
	{
		if (mFrameCount >= mFollingAge.at(i))
		{
			mFonts.at(i)->SetActive(true);
		}
	}

	for (auto& font : mFonts)
	{
		if (font->GetActive())
		{
			font->SetPosY(font->GetPosY() + mVeclocity + mGravAccele);
			if (font->GetPosY() >= mDisplayLine)
			{
				mVeclocity *= -1 * mFriction;
				if (Math::NearZero(mVeclocity))
				{
					mVeclocity = 0.0f;
					font->SetPosY(mDisplayLine);
				}
			}
		}
	}

	if (mFrameCount >= 346)
	{
		mAlpha += 0.01f;
		if (mAlpha >= 1.0f)
		{
			mAlpha = 1.0f;
			if (!mInitialTrigger)
			{
				mReStart->SetHighLighted(true);
				mInitialTrigger = true;
			}
		}
		mReStart->GetSprite()->SetAlpha(mAlpha);
		mToTitle->GetSprite()->SetAlpha(mAlpha);
	}

	if ((keylogger_Trigger(KL_D) || keylogger_Trigger(KL_END)) &&
		mReStart->GetHighLighted() && !mRestartTrigger && !mReturnTrigger)
	{
		mReStart->SetHighLighted(false);
		mToTitle->SetHighLighted(true);
		SoundManager_PlaySE(SL_menu_move);
	}
	if ((keylogger_Trigger(KL_A) || keylogger_Trigger(KL_HOME)) &&
		mToTitle->GetHighLighted() && !mRestartTrigger && !mReturnTrigger)
	{
		mToTitle->SetHighLighted(false);
		mReStart->SetHighLighted(true);
		SoundManager_PlaySE(SL_menu_move);
	}
	if ((keylogger_Trigger(KL_ENTER) || keylogger_Trigger(KL_SPACE)) &&
		mReStart->GetHighLighted() && !mRestartTrigger)
	{
		mRestartTrigger = true;
		SoundManager_PlaySE(SL_menu_start);
	}
	if ((keylogger_Trigger(KL_ENTER) || keylogger_Trigger(KL_SPACE)) &&
		mToTitle->GetHighLighted() && !mReturnTrigger)
	{
		mReturnTrigger = true;
		SoundManager_PlaySE(SL_menu_cancel);
	}

	if (mRestartTrigger || mReturnTrigger)
	{
		mWhiteAlpha -= 0.008f;
		if (mWhiteAlpha <= 0.0f) mWhiteAlpha = 0.0f;
		mBackGround->SetColor((int)255 * mWhiteAlpha + 255,
			(int)255 * mWhiteAlpha + 255, (int)255 * mWhiteAlpha + 255);
		mBackGround->SetLayerChange(15);
		mReStart->GetSprite()->SetLayerChange(13);
		mToTitle->GetSprite()->SetLayerChange(13);
		mReStart->SetHighLighted(false);
		mToTitle->SetHighLighted(false);
		mBackGround->SetAlpha(mWhiteAlpha);
	}
	if (mWhiteAlpha <= 0.0f && mRestartTrigger)
	{
		Stage_Translation(MapManager_GetStangeNumber());
	}
	if (mWhiteAlpha <= 0.0f && mReturnTrigger)
	{
		SM_SceneChange(ETitle);
	}

	mLeftLight->Update();
	mRightLight->Update();

	mFrameCount++;
}

void GameOver::Unload()
{
	SoundManager_StopBGM();

	for (auto& font : mFonts)
	{
		delete font;
		font = NULL;
	}

	delete mBackGround;
	mBackGround = NULL;
}

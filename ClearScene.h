
#pragma once
#include "Math.h"
#include "config.h"

class Clear
{
public:
	Clear();

	void Load();
	void Init();
	void Update();
	void Unload();
private:
	class Button* mToTitle;
	class HighLight* mLeftLight;
	class Button* mNextStage;
	class HighLight* mRightLight;

	class SpriteUI* mBackGround;
	class SpriteUI* mStageFont;
	class SpriteUI* mClearFont;
	class SpriteUI* mThanksFont;

	Vector2 mStartS = Vector2(-900, -400);
	Vector2 mStartC = Vector2(SCREEN_WIDTH + 900, SCREEN_HEIGHT + 40);
	Vector2 mTargetS = Vector2(400, 190);
	Vector2 mTargetC = Vector2(500, 515);

	float mStageCoeff;
	float mClearCoeff;
	float mScaling;
	float mAlpha;
	float mWhiteAlpha;
	int mDelayTimer;
	bool mNextTrigger;
	bool mReturnTrigger;
	bool mInitialTrigger;
	bool mThanksTrigger;
};


#pragma once
#include "Math.h"
#include "config.h"

class Title
{
public:
	Title();

	void Load();
	void Init();
	void Update();
	void Unload();
private:
	class Button* mStartButton;
	class HighLight* mCenterLight;

	class SpriteUI* mBgFar;
	class SpriteUI* mBgMiddle;
	class SpriteUI* mBgNear;
	class SpriteUI* mBlackBG;

	class SpriteUI* mMerge;
	class SpriteUI* mInto;
	class SpriteUI* mLiners;
	class SpriteUI* mKana;
	class SpriteUI* mRightLine;
	class SpriteUI* mLeftLine;
	class SpriteUI* mCross;

	Vector2 mRightLineStart = Vector2(SCREEN_WIDTH + 1700, 300);
	Vector2 mLeftLineStart = Vector2(-1700, 300);
	Vector2 mCrossStart    = Vector2(770, -100);
	Vector2 mRightLineTarget= Vector2(750, 280);
	Vector2 mLeftLineTarget	= Vector2(-537, 350);
	Vector2 mCrossTarget	= Vector2(788, 338);

	float mBlackAlpha;
	float mFontsAlpha;
	float mCoeff;
	float mCrossCoeff;
	float mButtonCoeff;
	int mDelayTimer;
	bool mTrigger;
};
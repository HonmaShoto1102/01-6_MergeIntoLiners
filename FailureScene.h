
#pragma once
#include <vector>

class GameOver
{
public:
	GameOver();

	void Load();
	void Init();
	void Update();
	void Unload();
private:
	class Button* mReStart;
	class HighLight* mLeftLight;
	class Button* mToTitle;
	class HighLight* mRightLight;

	class SpriteUI* mBackGround;
	std::vector<class SpriteUI*> mFonts;

	const float mDisplayLine = 333.0f;
	const float mFriction = 0.67f;
	const float mGravAccele = 9.044f;

	float mVeclocity;
	std::vector<int> mFollingAge;
	int mFrameCount;
	float mAlpha;
	float mWhiteAlpha;
	bool mRestartTrigger;
	bool mReturnTrigger;
	bool mInitialTrigger;
};

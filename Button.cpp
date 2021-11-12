
#include "Button.h"
#include "base_Sprite.h"

Button::Button(const std::string& name, const Vector2& pos)
	:mHighLighted(false)
{
	mBounds.SetPosition(pos);
	char path[64] = "Asset/Fonts/";
	strcat_s(path, name.c_str());
	strcat_s(path, ".png");
	mSprite = new SpriteUI(path);
}

Button::~Button()
{
	delete mSprite;
}

void Button::Init()
{
	mSprite->Init();
	mSprite->SetPosition(mBounds.GetPosition());
}

void Button::Update()
{
	mBounds.SetWidth(mSprite->GetWidth());
	mBounds.SetHeight(mSprite->GetHeight());
}

bool Button::ContainsCursol(const Vector2& cursol)
{
	bool no = 
		cursol.x < (mBounds.GetPosition().x - mBounds.GetPosition().x + mBounds.GetWidth() / 2.0f)  ||
		cursol.x >(mBounds.GetPosition().x + mBounds.GetPosition().x + mBounds.GetWidth() / 2.0f)   ||
		cursol.y < (mBounds.GetPosition().y - mBounds.GetPosition().y + mBounds.GetHeight() / 2.0f) ||
		cursol.y >(mBounds.GetPosition().y + mBounds.GetPosition().y + mBounds.GetHeight() / 2.0f);
	return !no;
}


HighLight::HighLight(class Button* button)
	:mButton(button)
	,mAlpha(0.0f)
	,mState(State::Appear)
{
	mSprite = new SpriteUI("Asset/Fonts/high_light.png", 14);
}

HighLight::~HighLight()
{
	delete mSprite;
}

void HighLight::Init()
{
	mSprite->Init();
	mSprite->SetPosition(mButton->GetBounds().GetPosition());
	mSprite->SetActive(false);
}

void HighLight::Update()
{
	mButton->Update();
	mSprite->SetWidth(mButton->GetBounds().GetWidth());
	mSprite->SetHeight(mButton->GetBounds().GetHeight() - 50);
	if (mButton->GetHighLighted())
	{
		mSprite->SetActive(true);
		if (mState == State::Appear)
		{
			mAlpha += 0.01f;
			if (mAlpha >= 0.9f)
			{
				mAlpha = 0.9f;
				mState = State::Vanish;
			}
		}
		if (mState == State::Vanish)
		{
			mAlpha -= 0.01f;
			if (mAlpha <= 0.38f)
			{
				mAlpha = 0.38f;
				mState = State::Appear;
			}
		}
		mSprite->SetAlpha(mAlpha);
	}
	if (!mButton->GetHighLighted())
	{
		mSprite->SetActive(false);
		mState = State::Appear;
		mAlpha = 0.0f;
	}
}

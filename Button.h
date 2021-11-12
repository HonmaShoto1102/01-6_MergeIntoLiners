
#pragma once
#include "Math.h"
#include <string>

class Bound
{
public:
	Bound()
		:mPosition(Vector2::Zero)
		,mWidth(0.0f)
		,mHeight(0.0f)
	{ }
	explicit Bound(const Vector2& inPosition, float inWidth, float inHeight)
		:mPosition(inPosition)
		,mWidth(inWidth)
		,mHeight(inHeight)
	{ }

	Vector2 GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetWidth() const { return mWidth; }
	void SetWidth(float width) { mWidth = width; }
	float GetHeight() const { return mHeight; }
	void SetHeight(float height) { mHeight = height; }
private:
	Vector2 mPosition;
	float mWidth;
	float mHeight;
};

class Button
{
public:
	Button(const std::string& name, const Vector2& pos);
	~Button();

	void Init();
	void Update();
	bool ContainsCursol(const Vector2& cursol);
	Bound GetBounds() const { return mBounds; }
	bool GetHighLighted() const { return mHighLighted; }
	void SetHighLighted(bool lighted) { mHighLighted = lighted; }
	class SpriteUI* GetSprite() const { return mSprite; }
private:
	class SpriteUI* mSprite;
	Bound mBounds;
	bool mHighLighted;
};

class HighLight
{
public:
	HighLight(class Button* button);
	~HighLight();

	void Init();
	void Update();
	class SpriteUI* GetSprite() const { return mSprite; }
private:
	class Button* mButton;
	class SpriteUI* mSprite;
	float mAlpha;
	enum class State { Appear, Vanish } mState;
};
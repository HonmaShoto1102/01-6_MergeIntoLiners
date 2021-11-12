
#pragma once
#include "Component.h"
#include "collision.h"
#include <vector>
#include <unordered_map>


class SearchArea
{
public:
	SearchArea(class Enemy* owner)
		:mOwner(owner)
		,mHorizontalRange(nullptr)
		,mVerticalRange(nullptr)
		,mCircleRange(nullptr)
	{ }

	virtual void Update() = 0;

	virtual const char* GetName() const = 0;
	CollisionRectangle* GetHorizontalRange() const
	{
		return mHorizontalRange;
	}
	CollisionRectangle* GetVerticalRange() const
	{
		return mVerticalRange;
	}
	CollisionCircle* GetCircleRange() const
	{
		return mCircleRange;
	}
protected:
	class Enemy* mOwner;
	CollisionRectangle* mHorizontalRange;
	CollisionRectangle* mVerticalRange;
	CollisionCircle* mCircleRange;
};


class HorizontalRange : public SearchArea
{
public:
	HorizontalRange(class Enemy* owner)
		:SearchArea(owner)
	{
		mHorizontalRange = new CollisionRectangle;
	}

	void Update() override;

	const char* GetName() const override
	{
		return "HorizontalRange";
	}
};


class VerticalRange : public SearchArea
{
public:
	VerticalRange(class Enemy* owner)
		:SearchArea(owner)
	{
		mVerticalRange = new CollisionRectangle;
	}

	void Update() override;

	const char* GetName() const override
	{
		return "VerticalRange";
	}
};


class CircleRange : public SearchArea
{
public:
	CircleRange(class Enemy* owner, float radius)
		:SearchArea(owner)
		,mRadius(radius)
	{
		mCircleRange = new CollisionCircle;
	}

	void Update() override;

	const char* GetName() const override
	{
		return "CircleRange";
	}
private:
	float mRadius;
};


class SearchComponent : public Component
{
public:
	SearchComponent(class Enemy* owner, int updateOrder = 10);

	void Update() override;

	class SearchArea* GetSearchArea(const std::string& name) const;
	void RegisterSearchRange(class SearchArea* area);
private:
	std::unordered_map<std::string, class SearchArea*> mOwnedRange;
	std::vector<std::string> mRegisterdName;
};


class Grid : public Enemy
{
public:
	Grid(class Game* game, Vector2 start, float size, size_t rows, size_t cols);

	void InitEnemy() override
	{ }
	void UpdateEnemy() override
	{ }

	// Use A-Star to find a path
	bool FindPath(class Grid* start, class Grid* goal);

	// Get start / end grid
	class Grid* GetStartGrid() const { return mStartGrid; }
	class Grid* GetEndGrid() const { return mEndGrid; }
private:
	std::vector<std::vector<class Grid*>> mGrids;

	class Grid* mStartGrid;
	class Grid* mEndGrid;
	// Rows / columns in grid.
	size_t mRowsNum;
	size_t mColsNum;
	// Start grid's position.
	Vector2 mStart;
	// Width/height of each grid.
	float mSize;
protected:
	class Grid* mSelectedGrid;
	std::vector<class Grid*> mAdjacent;
	class Grid* mParent;
	float f;
	float g;
	float h;
	bool mInOpenSet;
	bool mInClosedSet;
	bool mBlocked;
};

// 0 : ìØàÍê¸è„
// 1 : ëÊÇPè€å¿ 
// 2 : ëÊÇQè€å¿
// 3 : ëÊÇRè€å¿
// 4 : ëÊÇSè€å¿
unsigned int toQuadrant(class Enemy* enemy, const Vector2& target);

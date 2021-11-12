
#include "Search.h"
#include "Enemy.h"
#include "GM.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <cassert>


void HorizontalRange::Update()
{
	mHorizontalRange->x = GM_mainCamera()->GetOffsetPosX();
	mHorizontalRange->y = mOwner->GetSprite()->GetPosY();
	mHorizontalRange->w = GM_mainCamera()->GetScreenCameraWidth();
	mHorizontalRange->h = mOwner->GetBounds()->h;
}

void VerticalRange::Update()
{
	mVerticalRange->x = mOwner->GetSprite()->GetPosX();
	mVerticalRange->y = GM_mainCamera()->GetOffsetPosY();
	mVerticalRange->w = mOwner->GetBounds()->w;
	mVerticalRange->h = GM_mainCamera()->GetScreenCameraHeight();
}

void CircleRange::Update()
{
	mCircleRange->center.x = mOwner->GetSprite()->GetPosX() + mOwner->GetBounds()->w * 0.5f;
	mCircleRange->center.y = mOwner->GetSprite()->GetPosY() + mOwner->GetBounds()->h * 0.5f;
	mCircleRange->radius = mRadius;
}


SearchComponent::SearchComponent(class Enemy* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mOwnedRange(NULL)
	,mRegisterdName(NULL)
{
}

void SearchComponent::Update()
{
	for (auto& search : mOwnedRange)
	{
		search.second->Update();
	}
}

class SearchArea* SearchComponent::GetSearchArea(const std::string& name) const
{
	std::vector<int> confirm;
	for (auto& registered : mRegisterdName)
	{
		int str = std::strcmp(name.c_str(), registered.c_str());
		confirm.emplace_back(str);
	}
	auto iter = confirm.begin();
	for (;iter!=confirm.end();)
	{
		if ((*iter) == 0)
		{
			break;
		}
		else
		{
			if (iter == confirm.end() - 1)
			{
				return nullptr;
			}
			++iter;
		}
	}
	return mOwnedRange.find(name)->second;
}

void SearchComponent::RegisterSearchRange(class SearchArea* area)
{
	mOwnedRange.emplace(area->GetName(), area);
	mRegisterdName.emplace_back(area->GetName());
}


Grid::Grid(class Game* game, Vector2 start, float size, size_t rows, size_t cols)
	:Enemy(game)
	,mStartGrid(nullptr)
	,mEndGrid(nullptr)
	,mStart(start)
	,mSize(size)
	,mRowsNum(rows)
	,mColsNum(cols)
	,f(0.0f)
	,g(0.0f)
	,h(0.0f)
	,mBlocked(false)
	,mSelectedGrid(nullptr)
{
	mGrids.resize(rows);
	for (size_t i = 0; i < mGrids.size(); i++)
	{
		mGrids.at(i).resize(cols);
	}
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			mGrids.at(i).at(j)->GetSprite()->SetPosition(Vector2(start.x + j * size,
				start.y + i * size));
		}
	}
	mStartGrid = mGrids.at(0).at(0);
	mEndGrid = mGrids.at(rows).at(cols);
}

bool Grid::FindPath(Grid* start, Grid* goal)
{
	for (size_t i = 0; i < mRowsNum; i++)
	{
		for (size_t j = 0; j < mColsNum; j++)
		{
			// ヒューリスティック値
			mGrids.at(i).at(j)->g = 0.0f;
			// オープンセットに帰属
			mGrids.at(i).at(j)->mInOpenSet = false;
			// クローズドセットに帰属
			mGrids.at(i).at(j)->mInClosedSet = false;
		}
	}
	
	// オープンセットの動的配列を定義
	std::vector<Grid*> openSet;

	// カレントノードを記録するための変数
	// スタートのノードで初期化
	Grid* current = start;
	// カレントノードをクローズドセットに追加
	current->mInClosedSet = true;

	do
	{
		// 隣接ノードをオープンセットに追加
		for (Grid* neighbor : current->mAdjacent)
		{
			// 隣接ノードが壁ならcontinue
			if (neighbor->mBlocked)
			{
				continue;
			}

			// 隣接ノードがクローズドセットでない限り追加
			if (!neighbor->mInClosedSet)
			{
				// オープンセットでないなら
				if (!neighbor->mInOpenSet)
				{
					// 隣接ノードの親ノードを設定する
					neighbor->mParent = current;
					// 隣接ノードのヒューリスティック値を設定する
					neighbor->h = (neighbor->GetSprite()->GetPosition() - 
						goal->GetSprite()->GetPosition()).Length();

					// g(x) 経路コスト
					// 親ノードの経路コスト + エッジを辿るコスト 
					neighbor->g = current->g + mSize;
					// 
					neighbor->f = neighbor->g + neighbor->h;
					// 隣接ノードをオープンセットに追加
					openSet.emplace_back(neighbor);
					// オープンセットのスクラッチデータを設定
					neighbor->mInOpenSet = true;
				}
				else
				{
					// オープンセットの場合、もともと設定していたg(x)と
					// 現在のカレントノードから計算したg(x)を比較して、
					// 元々設定していたg(x)の方が大きい場合は、現在のカレントノードから計算したg(x)を設定

					// 現在のカレントノードからg(x)を計算
					float newG = current->g + mSize;
					if (newG < neighbor->g)
					{
						// カレントノードを採用
						neighbor->mParent = current;
						neighbor->g = newG;
						// g(x)を変更したのでf(x)も変更
						neighbor->f = neighbor->g + neighbor->h;
					}
				}
			}
		}

		// オープンセットが空なら、全ての可能性のある経路は探しつくした
		if (openSet.empty())
		{
			break;
		}

		// 最もコストの低いノードをオープンセットから探す
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[](Grid* a, Grid* b) 
			{
				return a->f < b->f;
			});
		// 最もコストの低いノードをカレントノードに設定
		current = *iter;
		// オープンセットから最もコストの低いノードを消去
		openSet.erase(iter);
		// クローズドセット
		current->mInOpenSet = false;
		current->mInClosedSet = true;
	} while (current != goal);

	return (current == goal) ? true : false;
}


unsigned int toQuadrant(class Enemy* enemy, const Vector2& target)
{
	Vector2 axis = enemy->GetSprite()->GetPosition() +
		Vector2(enemy->GetBounds()->w * 0.5f, enemy->GetBounds()->h * 0.5f);

	unsigned int result = 0;
	
	if (!Math::NearZero(axis.x - target.x) || !Math::NearZero(axis.y - target.y))
	{
		if (target.x > axis.x && target.y > axis.y) result = 1;
		if (target.x < axis.x && target.y > axis.y) result = 2;
		if (target.x < axis.x && target.y < axis.y) result = 3;
		if (target.x > axis.x && target.y < axis.y) result = 4;
	}
	
	return result;
}


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
			// �q���[���X�e�B�b�N�l
			mGrids.at(i).at(j)->g = 0.0f;
			// �I�[�v���Z�b�g�ɋA��
			mGrids.at(i).at(j)->mInOpenSet = false;
			// �N���[�Y�h�Z�b�g�ɋA��
			mGrids.at(i).at(j)->mInClosedSet = false;
		}
	}
	
	// �I�[�v���Z�b�g�̓��I�z����`
	std::vector<Grid*> openSet;

	// �J�����g�m�[�h���L�^���邽�߂̕ϐ�
	// �X�^�[�g�̃m�[�h�ŏ�����
	Grid* current = start;
	// �J�����g�m�[�h���N���[�Y�h�Z�b�g�ɒǉ�
	current->mInClosedSet = true;

	do
	{
		// �אڃm�[�h���I�[�v���Z�b�g�ɒǉ�
		for (Grid* neighbor : current->mAdjacent)
		{
			// �אڃm�[�h���ǂȂ�continue
			if (neighbor->mBlocked)
			{
				continue;
			}

			// �אڃm�[�h���N���[�Y�h�Z�b�g�łȂ�����ǉ�
			if (!neighbor->mInClosedSet)
			{
				// �I�[�v���Z�b�g�łȂ��Ȃ�
				if (!neighbor->mInOpenSet)
				{
					// �אڃm�[�h�̐e�m�[�h��ݒ肷��
					neighbor->mParent = current;
					// �אڃm�[�h�̃q���[���X�e�B�b�N�l��ݒ肷��
					neighbor->h = (neighbor->GetSprite()->GetPosition() - 
						goal->GetSprite()->GetPosition()).Length();

					// g(x) �o�H�R�X�g
					// �e�m�[�h�̌o�H�R�X�g + �G�b�W��H��R�X�g 
					neighbor->g = current->g + mSize;
					// 
					neighbor->f = neighbor->g + neighbor->h;
					// �אڃm�[�h���I�[�v���Z�b�g�ɒǉ�
					openSet.emplace_back(neighbor);
					// �I�[�v���Z�b�g�̃X�N���b�`�f�[�^��ݒ�
					neighbor->mInOpenSet = true;
				}
				else
				{
					// �I�[�v���Z�b�g�̏ꍇ�A���Ƃ��Ɛݒ肵�Ă���g(x)��
					// ���݂̃J�����g�m�[�h����v�Z����g(x)���r���āA
					// ���X�ݒ肵�Ă���g(x)�̕����傫���ꍇ�́A���݂̃J�����g�m�[�h����v�Z����g(x)��ݒ�

					// ���݂̃J�����g�m�[�h����g(x)���v�Z
					float newG = current->g + mSize;
					if (newG < neighbor->g)
					{
						// �J�����g�m�[�h���̗p
						neighbor->mParent = current;
						neighbor->g = newG;
						// g(x)��ύX�����̂�f(x)���ύX
						neighbor->f = neighbor->g + neighbor->h;
					}
				}
			}
		}

		// �I�[�v���Z�b�g����Ȃ�A�S�Ẳ\���̂���o�H�͒T��������
		if (openSet.empty())
		{
			break;
		}

		// �ł��R�X�g�̒Ⴂ�m�[�h���I�[�v���Z�b�g����T��
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[](Grid* a, Grid* b) 
			{
				return a->f < b->f;
			});
		// �ł��R�X�g�̒Ⴂ�m�[�h���J�����g�m�[�h�ɐݒ�
		current = *iter;
		// �I�[�v���Z�b�g����ł��R�X�g�̒Ⴂ�m�[�h������
		openSet.erase(iter);
		// �N���[�Y�h�Z�b�g
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

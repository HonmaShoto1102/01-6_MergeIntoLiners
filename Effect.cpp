/*---------------------------------------------------------------------------*/
//  FILE : Effect.cpp
//
//         　　　　　　  　　エフェクト効果の実装
//
/*===========================================================================*/
//
//                                                          Author : R.Usui
/*---------------------------------------------------------------------------*/

#include <vector>
#include <cassert>
#include <unordered_map>

#include "Effect.h"

struct Effect {
	Effect(const char* pFileName, int layer, SPRITETYPE spType) {
		sprite = new SpriteC(pFileName, layer, spType);
	}
	~Effect() {
		delete sprite;
		sprite = NULL;
	}
	SpriteC* sprite;
	int2D index;
	int2D cutSize;
	int frameCount;
};

// 画面上に１度に表示できる１種類のエフェクトの最大数
#define EFFECT_MAX (8)
static std::unordered_map<std::string, std::vector<Effect*>> mEffectArray;


void Effect_Load(void)
{
	std::vector<Effect*> temp1(EFFECT_MAX);
	for (int i = 0; i < EFFECT_MAX; i++) {
		temp1[i] = new Effect("Asset/effect_call_vertica.png", 13, SPRITE_UI);
		temp1[i]->sprite->SetAnchorPoint(ANCHOR_CENTER);
		temp1[i]->index = { 7,4 };
		temp1[i]->cutSize = { 128,128 };
	}
	mEffectArray.emplace("effect_call_vertica", temp1);
	

	std::vector<Effect*> temp2(EFFECT_MAX);
	for (int i = 0; i < EFFECT_MAX; i++) {
		temp2[i] = new Effect("Asset/effect_call_horizy.png", 13, SPRITE_UI);
		temp2[i]->sprite->SetAnchorPoint(ANCHOR_CENTER);
		temp2[i]->index = { 7,4 };
		temp2[i]->cutSize = { 128,128 };
	}
	mEffectArray.emplace("effect_call_horizy", temp2);


	std::vector<Effect*> temp3(EFFECT_MAX);
	for (int i = 0; i < EFFECT_MAX; i++) {
		temp3[i] = new Effect("Asset/effect_delete_vertica_line.png", 13, SPRITE_UI);
		temp3[i]->sprite->SetAnchorPoint(ANCHOR_CENTER);
		temp3[i]->index = { 7,4 };
		temp3[i]->cutSize = { (int)2304 / 7, (int)3000 / 4 };
	}
	mEffectArray.emplace("effect_delete_vertica_line", temp3);


	std::vector<Effect*> temp4(EFFECT_MAX);
	for (int i = 0; i < EFFECT_MAX; i++) {
		temp4[i] = new Effect("Asset/effect_delete_horizy_line.png", 13, SPRITE_UI);
		//temp4[i] = new Effect("Asset/effect_delete_vertica_line.png", 13, SPRITE_UI);
		temp4[i]->sprite->SetAnchorPoint(ANCHOR_CENTER);
		temp4[i]->index = { 7,4 };
		temp4[i]->cutSize = { (int)5800 / 7, (int)1280 / 4 };
	}
	mEffectArray.emplace("effect_delete_horizy_line", temp4);


	std::vector<Effect*> temp5(EFFECT_MAX);
	for (int i = 0; i < EFFECT_MAX; i++) {
		temp5[i] = new Effect("Asset/effect_line_drawn_up.png", 13, SPRITE_UI);
		temp5[i]->sprite->SetAnchorPoint(ANCHOR_LU);
		temp5[i]->index = { 7,4 };
		temp5[i]->cutSize = { (int)896 / 7, (int)512 / 4 };
	}
	mEffectArray.emplace("effect_line_drawn_up", temp5);


	std::vector<Effect*> temp6(EFFECT_MAX);
	for (int i = 0; i < EFFECT_MAX; i++) {
		temp6[i] = new Effect("Asset/effect_number_disappear.png", 13, SPRITE_UI);
		temp6[i]->sprite->SetAnchorPoint(ANCHOR_CENTER);
		temp6[i]->index = { 7,4 };
		temp6[i]->cutSize = { (int)1792 / 7, (int)1024 / 4 };
	}
	mEffectArray.emplace("effect_number_disappear", temp6);


	std::vector<Effect*> temp7(EFFECT_MAX);
	for (int i = 0; i < EFFECT_MAX; i++) {
		temp7[i] = new Effect("Asset/effect_to_heart_box.png", 13, SPRITE_UI);
		temp7[i]->sprite->SetAnchorPoint(ANCHOR_CENTER);
		temp7[i]->index = { 7,4 };
		temp7[i]->cutSize = { (int)1792 / 7, (int)1024 / 4 };
	}
	mEffectArray.emplace("effect_to_heart_box", temp7);


	std::vector<Effect*> temp8(EFFECT_MAX);
	for (int i = 0; i < EFFECT_MAX; i++) {
		temp8[i] = new Effect("Asset/effect_on_heart_box.png", 13, SPRITE_UI);
		temp8[i]->sprite->SetAnchorPoint(ANCHOR_CENTER);
		temp8[i]->index = { 7,4 };
		temp8[i]->cutSize = { (int)1792 / 7, (int)1024 / 4 };
	}
	mEffectArray.emplace("effect_on_heart_box", temp8);


	std::vector<Effect*> temp9(EFFECT_MAX);
	for (int i = 0; i < EFFECT_MAX; i++) {
		temp9[i] = new Effect("Asset/effect_enemy_damaged.png", 13, SPRITE_UI);
		temp9[i]->sprite->SetAnchorPoint(ANCHOR_LU);
		temp9[i]->index = { 7,4 };
		temp9[i]->cutSize = { (int)1792 / 7, (int)1024 / 4 };
	}
	mEffectArray.emplace("effect_enemy_damaged", temp9);
}


void Effect_Init(void)
{
	// すべてのeffectステートをNon-Activeに
	auto iter = mEffectArray.begin();
	for (;
		iter != mEffectArray.end();
		++iter)
	{
		for (auto effect : mEffectArray.at(iter->first) ){
			effect->sprite->SetActive(false);
		}
	}
}

void Effect_Update(void)
{
	// ActiveステートのeffectArrayを更新
	auto iter = mEffectArray.begin();
	for (;
		iter != mEffectArray.end();
		++iter)
	{
		for (int i = 0; i < EFFECT_MAX; i++) {
			if (iter->second[i]->sprite->GetActive() == true) {
				iter->second[i]->frameCount++;
				int drawPoint_U = static_cast<int>(iter->second[i]->frameCount 
					% iter->second[i]->index.x);
				int drawPoint_V = static_cast<int>(iter->second[i]->frameCount 
					/ iter->second[i]->index.x % iter->second[i]->index.y);
				iter->second[i]->sprite->SetRegion(drawPoint_U, drawPoint_V);
				if (iter->second[i]->frameCount
					>= iter->second[i]->index.x * iter->second[i]->index.y) {
					iter->second[i]->sprite->SetActive(false);
				}
			}
		}
	}
}

void Effect_Unload(void)
{
	for (auto temp = mEffectArray.begin(); temp != mEffectArray.end(); ++temp) {
		for (int i = 0; i < EFFECT_MAX; i++) {
			delete temp->second[i];
			temp->second[i] = NULL;
		}
	}
	mEffectArray.clear();
}


void ActivateEffect(std::string effectName, float2D position, float2D scale)
{
	Effect* effect = nullptr;
	auto iter = mEffectArray.find(effectName);
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (iter->second[i]->sprite->GetActive() == false) {
			effect = iter->second[i];
			break;
		}
	}
	assert(effect != nullptr);

	effect->sprite->Init();
	effect->sprite->SetActive(true);
	effect->sprite->SetPosition(position.x, position.y);
	effect->sprite->SetCutSize(effect->cutSize.x, effect->cutSize.y);
	effect->sprite->SetScale(scale.x, scale.y);
	effect->frameCount = 0;
}

void ActivateLineEffect(std::string effectName, float2D start, float2D scale, float angle)
{
	Effect* effect = nullptr;
	auto iter = mEffectArray.find(effectName);
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (iter->second[i]->sprite->GetActive() == false) {
			effect = iter->second[i];
			break;
		}
	}
	assert(effect != nullptr);

	effect->sprite->Init();
	effect->sprite->SetActive(true);
	effect->sprite->SetPosition(start.x, start.y);
	effect->sprite->SetCutSize(effect->cutSize.x, effect->cutSize.y);
	effect->sprite->SetScale(scale.x, scale.y);
	effect->sprite->SetAngle(angle);
	effect->frameCount = 0;
}

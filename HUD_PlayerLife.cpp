/*---------------------------------------------------------------------------*/
//  FILE : HUD_PlayerLife.h
//
//         　　　　　　playerのLife,HPのUIの演出
//
/*===========================================================================*/
//
//                                                          Author : Honma Shoto
/*---------------------------------------------------------------------------*/


#include "HUD_LineTime.h"
#include "PlayerData.h"
#include "base_Sprite.h"
#include "config.h"

#define scale_size_life (512.0f)

namespace life {

	SpriteUI* PlayerHP;
	SpriteUI* PlayerHPShade;
	bool PHenable;
}

void HUD_PlayerLife_Load(void)
{
	life::PlayerHP = new SpriteUI("Asset/HUD/hud_hp.png", 14, SPRITE_UI);
	life::PlayerHPShade = new SpriteUI("Asset/HUD/hud_hp_black.png", 15, SPRITE_UI);//使用済みの黒
}

void HUD_PlayerLife_Init(void)
{
	life::PlayerHP->Init();
	life::PlayerHPShade->Init();

	life::PlayerHP->SetPosX(0.0f+100.0f);
	life::PlayerHP->SetPosY(-50.0f);
	life::PlayerHPShade->SetPosX(0.0f + 100.0f);
	life::PlayerHPShade->SetPosY(-50.0f);

	life::PlayerHP->SetAnchorPoint(ANCHOR_TC);
	life::PlayerHP->SetScale(0.5f, 0.5f);
	life::PlayerHPShade->SetAnchorPoint(ANCHOR_TC);
	life::PlayerHPShade->SetScale(0.5f, 0.5f);
	life::PHenable = false;

}

void HUD_PlayerLife_Update(void)
{

}

void HUD_PlayerLife_Unload(void)
{
	delete life::PlayerHP;
	life::PlayerHP = NULL;
	delete life::PlayerHPShade;
	life::PlayerHPShade = NULL;
}
/*---------------------------------------------------------------------------*/
//  FILE : uiDisplay.cpp
//
//         　　　　　　ユーザーインターフェースの演出
//
/*===========================================================================*/
//
//                                                          Author : R.Usui
/*---------------------------------------------------------------------------*/

#include "uiDisplay.h"
#include "Enemy.h"
#include "playerCollision.h"
#include "playerAction.h"
#include "PlayerData.h"
#include "FairyVH.h"
#include "Heart.h"
#include "Effect.h"

namespace ui {
	// White Round
	SpriteC* WhiteRound;
	float WRvalue;
	float WRalpha;

	// White Jaggy
	SpriteC* WhiteJaggy;
	float WJvalue_w;
	float WJvalue_h;
	float WJoffset_w;
	float WJoffset_h;
	float WJalpha;
	float WJangle;

	// One Stick 
	SpriteC* OneStick;
	float OSgoal_x;
	float OSgoal_y;
	float OSangle;
	float OSvalue;
	int OSnumber;
}


void UI_Load(void)
{
	ui::WhiteRound = new SpriteC("Asset/white_round.png", 13, SPRITE_UI);

	ui::WhiteJaggy = new SpriteC("Asset/white_jaggy.png", 13, SPRITE_UI);

	ui::OneStick = new SpriteC("Asset/one_stick.png", 13, SPRITE_UI);
}


void UI_Init(void)
{
	// White Round
	ui::WhiteRound->Init();
	ui::WRvalue = 0.0f;
	ui::WRalpha = 1.0f;
	ui::WhiteRound->SetActive(false);
	ui::WhiteRound->SetAnchorPoint(ANCHOR_CENTER);

	// White Jaggy
	ui::WhiteJaggy->Init();
	ui::WJvalue_w = 0.0f;
	ui::WJvalue_h = 0.0f;
	ui::WJoffset_w = 0.0f;
	ui::WJoffset_h = 0.0f;
	ui::WJalpha = 1.0f;
	ui::WJangle = 0.0f;
	ui::WhiteJaggy->SetActive(false);
	ui::WhiteJaggy->SetAnchorPoint(ANCHOR_CENTER);

	// One Stick & One
	ui::OneStick->Init();
	ui::OneStick->SetAnchorPoint(ANCHOR_RD);
	ui::OneStick->SetActive(false);
	ui::OSgoal_x = 0.0f;
	ui::OSgoal_y = 0.0f;
	ui::OSangle = 0.0f;
	ui::OSvalue = 0.0f;
	ui::OSnumber = 0;
}


void UI_Unload(void)
{
	delete ui::OneStick;
	ui::OneStick = NULL;

	delete ui::WhiteJaggy;
	ui::WhiteJaggy = NULL;

	delete ui::WhiteRound;
	ui::WhiteRound = NULL;
}


void UI_Update(void)
{
	// White Round
	if (ui::WhiteRound->GetActive() == true) {
		ui::WRvalue += 0.2f;
		ui::WRalpha -= 0.04f;
		ui::WhiteRound->SetScale(ui::WRvalue, ui::WRvalue);
		ui::WhiteRound->SetAlpha(ui::WRalpha);

		if (ui::WRalpha <= 0.0f) {
			ui::WhiteRound->SetActive(false);
			ui::WRvalue = 0.0f;
			ui::WRalpha = 1.0f;
		}
	}

	// White Jaggy
	if (ui::WhiteJaggy->GetActive() == true) {
		ui::WJangle += 0.02f;
		ui::WhiteJaggy->SetAngle(ui::WJangle);
		if (!Player_isReturn()) {
			ui::WJoffset_w -= 0.05f;
			float scale_x = ui::WJvalue_w - ui::WJoffset_w;
			if (scale_x >= ui::WJvalue_w + 0.2f) {
				scale_x = ui::WJvalue_w + 0.2f;
			}
			ui::WJoffset_h -= 0.05f;
			float scale_y = ui::WJvalue_h - ui::WJoffset_h;
			if (scale_y >= ui::WJvalue_h + 0.2f) {
				scale_y = ui::WJvalue_h + 0.2f;
			}
			ui::WhiteJaggy->SetScale(scale_x, scale_y);
		}
		else if (Player_isReturn()) {
			ui::WJvalue_w += 0.4f;
			ui::WJvalue_h += 0.4f;
			ui::WJalpha -= 0.03f;
			ui::WhiteJaggy->SetScale(ui::WJvalue_w, ui::WJvalue_h);
			if (ui::WJalpha <= 0.0f) {
				Player_SetReturn(false);
				ui::WhiteJaggy->SetActive(false);
				ui::WJalpha = 1.0f;
				ui::WJoffset_h = 0.0f;
				ui::WJoffset_w = 0.0f;
				ui::WJvalue_h = 0.0f;
				ui::WJvalue_w = 0.0f;
			}
		}
	}

	// One Stick
	if (ui::OneStick->GetActive() == true) {
		if (ui::OSangle < -0.1f) {
			ui::OSangle += 0.07f;
		}
		else if (ui::OSangle > 0.1f) {
			ui::OSangle -= 0.07f;
		}
		ui::OneStick->SetAngle(ui::OSangle);
		ui::OSvalue += 0.008f;
		float dx = ui::OneStick->GetPosX() + ui::OSvalue * (ui::OSgoal_x - ui::OneStick->GetPosX());
		float dy = ui::OneStick->GetPosY() + ui::OSvalue * (ui::OSgoal_y - ui::OneStick->GetPosY());
		ui::OneStick->SetPosition(dx, dy);

		if ((ui::OSangle >= -0.1f && ui::OSangle <= 0.1f) ||
			(ui::OSangle <= 0.1f && ui::OSangle >= -0.1f))
		{
			ui::OneStick->SetAngle(0.0f);
			ui::OSvalue = 0.0f;
		}
	}
	if (ui::OneStick->GetActive() == true && ui::OSnumber < Heart_GetCurrentHeartNum()) {
		
		ui::OneStick->SetActive(false);
		ActivateEffect("effect_number_disappear",
			{ ui::OneStick->GetPosX(), ui::OneStick->GetPosY() }, { 1.0f, 1.0f });
	}
}



void UI_AttackFromHeart(void)
{
	if (ui::WhiteRound->GetActive() == true) return;

	ui::WhiteRound->SetActive(true);
	float cx = PlayerCollision_GetCollision().x + PlayerCollision_GetCollision().w * 0.5f;
	float cy = PlayerCollision_GetCollision().y + PlayerCollision_GetCollision().h * 0.5f;
	ui::WhiteRound->SetPosition(cx, cy);
	ui::WhiteRound->SetScale(1.0f, 1.0f);
}


void UI_ReturnToOrigineAfterAttack(class Enemy* enemy)
{
	if (ui::WhiteJaggy->GetActive() == true) return;

	ui::WhiteJaggy->SetActive(true);
	float cx = enemy->GetSprite()->GetPosX() + enemy->GetSprite()->GetWidth() * 0.5f;
	float cy = enemy->GetSprite()->GetPosY() + enemy->GetSprite()->GetHeight() * 0.5f;
	ui::WhiteJaggy->SetPosition(cx, cy);
	ui::WJvalue_w = static_cast<float>(enemy->GetSprite()->GetWidth() / 256);
	ui::WJvalue_h = static_cast<float>(enemy->GetSprite()->GetHeight() / 256);
	ui::WJoffset_w = ui::WJvalue_w;
	ui::WJoffset_h = ui::WJvalue_h;
	ui::WhiteJaggy->SetScale(0.0f, 0.0f);
}


void UI_OneStickChangetoOne(Heart* heart)
{
	if (ui::OneStick->GetActive() == true) return;

	ui::OneStick->SetActive(true);
	ui::OneStick->SetPosition(heart->sp->GetPosX(), heart->sp->GetPosY());
	ui::OneStick->SetScale(0.9f, 0.7f);
	ui::OSangle = Player_GetOnStackAngle();
	ui::OneStick->SetAngle(ui::OSangle);
	ui::OSnumber = heart->uiNumber;
	if (Player_GetDirection() == 1) {
		ui::OSgoal_x = PlayerCollision_GetCollision().x - PlayerCollision_GetCollision().w * 1.5f;
		ui::OSgoal_y = PlayerCollision_GetCollision().y + PlayerCollision_GetCollision().h * 0.5f;
	}
	else if (Player_GetDirection() == -1) {
		ui::OSgoal_x = PlayerCollision_GetCollision().x + PlayerCollision_GetCollision().w * 2.0f;
		ui::OSgoal_y = PlayerCollision_GetCollision().y + PlayerCollision_GetCollision().h * 0.5f;
	}
}

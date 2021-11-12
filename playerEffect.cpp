#include "playerEffect.h"
#include "base_Sprite.h"
#include "playerCollision.h"
#include "GM.h"
#include "FairyVH.h"
#include "Line.h"
#include "InputManager.h"


#define PARTI_BLOCKW (40)
#define PARTI_BLOCKH (20)
#define PARTI_W (65)
#define PARTI_H (80)
#define PARTICLEMAX (PARTI_W * PARTI_H)

typedef struct eff_st {
	SpriteC* sprite;
	int age;
	float2D offpos;
};
static eff_st E_callFairy;
static eff_st E_playerMoving;

static ParticleC* curtian;
//static SpriteC* curtianBg;

void CallFairyUpdate();
void CallFairyDelete(eff_st* es);
void CallFairyCreate(float x, float y);

void CurtianUpdate();

void PlayerEffect_Load()
{
	E_callFairy.sprite = new SpriteC("Asset/call_fairy.png", 11);
	
	curtian = new ParticleC("Asset/black_Curtain.png", PARTI_W * PARTI_H, 14);
	
}

void PlayerEffect_Init()
{
	E_callFairy.sprite->Init();
	E_callFairy.sprite->SetAnchorPoint(ANCHOR_CENTER);
	E_callFairy.sprite->SetActive(false);
	E_callFairy.sprite->SetScale(2.0f, 2.0f);
	E_callFairy.age = 0;
	E_callFairy.offpos = { 40.0f,-150.0f };

	
	curtian->Init();	
	curtian->SetSpDataAngleAll(PI / 4);
	curtian->Set_SpData_ScaleAll(0.5f, 0.5f);

	//SetInCaves(true);
}

void PlayerEffect_Update()
{
	CallFairyUpdate();
	if (GetInCaves()) {
		curtian->SetActive(true);
		CurtianUpdate();
	}
	else {
		curtian->SetActive(false);
	}
}

void PlayerEffect_Final()
{
	
	//delete curtian;
	delete E_callFairy.sprite;
}

void PlayerEffect_SetEffect(PEFFECT pe, float x, float y)
{
	switch (pe)
	{
	case pe_callFairy:
		CallFairyCreate(x, y);
		break;
	case pe_flyMoving:
		break;
	default:
		break;
	}
}

void CallFairyUpdate() {
	if (E_callFairy.sprite->GetActive() == false)return;

	if (E_callFairy.age % 20 >= 10) {
		E_callFairy.sprite->SetAlpha(0.0f);
	}
	else
	{
		E_callFairy.sprite->SetAlpha(1.0f);
	}
    
	E_callFairy.age++;
	if (E_callFairy.age >= 80) {
		CallFairyDelete(&E_callFairy);
	}
	E_callFairy.sprite->SetPosition(Player_GetPosX() + E_callFairy.offpos.x, Player_GetPosY() + E_callFairy.offpos.y);
}


void CallFairyDelete(eff_st* es) {
	es->sprite->SetActive(false);
	es->age = 0;
}

void CallFairyCreate(float x, float y) {
	E_callFairy.sprite->SetActive(true);
	E_callFairy.age = 0;
	E_callFairy.sprite->SetPosition(x + E_callFairy.offpos.x, y + E_callFairy.offpos.y);

}

void CurtianUpdate() {
	
    int cx = (int)GM_mainCamera()->GetOffsetPosX();
	int cy = (int)GM_mainCamera()->GetOffsetPosY();
	int playX = Player_GetPosX();
	int playY = Player_GetPosY();
	CollisionCircle Fx_v = FairyVH_GetCurrentCollisionV();
	CollisionCircle Fx_h = FairyVH_GetCurrentCollisionH();
	float sx = (cx / PARTI_BLOCKW) * PARTI_BLOCKW;
	float sy = (cy / PARTI_BLOCKW) * PARTI_BLOCKW;
	
	curtian->SetPostion(sx, sy);
	for (int i = 0; i < curtian->GetPcount(); i++)
	{
		float pX = (i % PARTI_W) * PARTI_BLOCKW - (i / PARTI_W) % 2 * PARTI_BLOCKH;
		float pY = (i / PARTI_W) * PARTI_BLOCKH;
		curtian->GetPdata(i)->SetPosition(pX,pY);

		float pdX = pX + sx;
		float pdY = pY + sy;

		float lenth = Collision_PointAndPoint_Distance(pdX, pdY, playX, playY);
		float lenthv = Collision_PointAndPoint_Distance(pdX, pdY, Fx_v.center.x, Fx_v.center.y);
		float lenthh = Collision_PointAndPoint_Distance(pdX, pdY, Fx_h.center.x, Fx_h.center.y);

		float bei,beiV,beiH;
		bei = beiV = beiH = 0.5f;
		if (lenth < 150.0f) {
			bei = 0.0f;
		}
		else if (lenth < 400.0f) {
			bei = (lenth - 150) / 250 * 0.5f;
		}

		if (lenthv < 100.0f) {
			beiV = 0.0f;
		}
		else if (lenthv < 250.0f) {
			beiV = (lenthv - 100) / 150 * 0.5f;
		}
		if (bei > beiV)bei = beiV;

		if (lenthh < 100.0f) {
			beiH = 0.0f;
		}
		else if (lenthh < 250.0f) {
			beiH = (lenthh - 100) / 150 * 0.5f;
		}
		if (bei > beiH)bei = beiH;


		float beiLine = 0.5f;
		for (int i = 0; i < LINEMAX + FMAX * 2; i++)
		{
			LINE* line = Line_GetLineForNumberAllMAP(i);
			if (line != NULL &&line->sp->GetActive()) {
				float len = Collision_PointAndLine_Distance(pdX, pdY, line->GetColl());
				if (len < 100.0f) {
					float tempb = 0.0f;
					if (beiLine > tempb)beiLine = tempb;
				}
				else if (len < 250.0f) {
					float tempb = (len - 100) / 150 * 0.5f;
					if (beiLine > tempb)beiLine = tempb;
				}
			}
		}
		if (bei > beiLine) bei = beiLine;	
		curtian->GetPdata(i)->SetScale(bei, bei);
		//curtian->GetPdata(i)->SetAlpha(0.5f);
	}
	
}


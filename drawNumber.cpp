#include "drawNumber.h"
#include "base_Sprite.h"
#include "Heart.h"
#include "Effect.h"

typedef struct NUMBERs {
	SpriteC* number;
	SpriteC* brackets;
	bool active;
	bool oldactive;
}NUMBER;

void DrawNumberCheck();

#define N_MAX (20)
static NUMBER numbers[N_MAX];

void DrawNumber_Load()
{
	for (int i = 0; i < N_MAX; i++)
	{
		numbers[i].number = new SpriteC("Asset/red_numbers.png", 14);
		numbers[i].brackets = new SpriteC("Asset/bracket.png", 14);
		numbers[i].oldactive = false;
		numbers[i].active = false;
	}
}

void DrawNumber_Init()
{
	for (int i = 0; i < N_MAX; i++)
	{
		numbers[i].number->Init();
		numbers[i].number->SetCutSize(64, 64);
		numbers[i].number->SetScale(2.5f, 2.5f);
		numbers[i].number->SetAnchorPoint(ANCHOR_CENTER);
		numbers[i].number->SetActive(false);

		numbers[i].brackets->Init();
		numbers[i].brackets->SetCutSize(82, 82);
		numbers[i].brackets->SetSpriteSize(100, 100);
		numbers[i].brackets->SetScale(2.5f, 2.5f);
		numbers[i].brackets->SetAnchorPoint(ANCHOR_CENTER);
		numbers[i].brackets->SetActive(false);
	}
}

void DrawNumber_Update()
{
	/*int nCount = Heart_GetHeartCount();
	int CurentCount = Heart_GetCurrentHeartNum();
	int bracketF = 0;
	bool bra = false;
	for (int i = 0; i < nCount; i++)
	{
		Heart* ht = Heart_GetHeart(i);
		if (ht->ht == RightAngle&&i!=1)bracketF++;
		if (i >= CurentCount) {
			if (bracketF > 0)bra = true;
			DrawNumber_SetDraw(ht->sp->GetPosX(), ht->sp->GetPosY(), ht->uiNumber, bra);
		}
	}*/

	DrawNumberCheck();
}

void DrawNumber_Final()
{
	for (int i = 0; i < N_MAX; i++)
	{
		delete numbers[i].number;
		delete numbers[i].brackets;
	}
}

void DrawNumber_SetDraw(float x, float y, int Number, bool bracket,int No)
{
	numbers[No].active = true;
	numbers[No].brackets->SetActive(bracket);
	numbers[No].number->SetActive(true);
	numbers[No].number->SetPosition(x, y);
	numbers[No].brackets->SetPosition(x-7, y);
	numbers[No].number->SetRegion(Number, 0);	
}

void DrawNumber_ReSet()
{
	for (int i = 0; i < N_MAX; i++)
	{
		numbers[i].number->SetActive(false);
		numbers[i].brackets->SetActive(false);
		numbers[i].active = false;
	}
}


void DrawNumberCheck() {
	for (int i = 0; i < N_MAX; i++)
	{
		if (numbers[i].oldactive == numbers[i].active)continue;
		numbers[i].oldactive = numbers[i].active;
		if (numbers[i].oldactive == false) {
			ActivateEffect("effect_number_disappear", { numbers[i].number->GetPosX(), numbers[i].number->GetPosY() }, { 1.0f,1.0f });

		}
	}
}



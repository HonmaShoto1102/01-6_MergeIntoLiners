#include "PlayerData.h"
#include "base_Sprite.h"
#include "playerCollision.h"
#include "SceneManager.h"
#define STRONGTIME (100)

struct P_DATA {
	float PosX;
	float PosY;
	float ScaleX;
	float ScaleY;
	float Width;
	float Height;
	int HP;
	int MaxHP;
};

static P_DATA pDate;
static int StrongTime = 0;


//static int HP;


void PlayerData_Load()
{
	pDate.HP = 30;
}

void PlayerData_Init()
{
	
}

void PlayerData_Update()
{
	StrongTime--;
	if (StrongTime <= 0)StrongTime = 0;
	if (pDate.HP <= 0)
	{
		
	}
}

void PlayerData_Final()
{
}


int Player_GetHP() {
	return pDate.HP;
}

int Player_GetMaxHP() {
	return pDate.MaxHP;
}

void Player_SetHP(int hp) {
	if (hp >= pDate.MaxHP) {
		pDate.HP = pDate.MaxHP;
	}
	else {
		pDate.HP = hp;
	}
	
}

void Player_PlusHP(int hp) {
	pDate.HP += hp;
	if (pDate.HP >= pDate.MaxHP) {
		pDate.HP = pDate.MaxHP;
	}
}
void Player_MinusHP(int hp) {
	
	pDate.HP -= hp;
	if (pDate.HP <= 0) {
		pDate.HP = 0;		
	}
	
}

void Player_SeedDamegeMessage(int hp, int dir)
{
	if (StrongTime>0)return;
	StrongTime = STRONGTIME;
	Player_MinusHP(hp);
	if (pDate.HP <= 0) {
		Player_SetState_Dead();
	}
	else {
		Player_SetDamegeFeedback(dir);
	}	
}

void Player_SetDamegeFeedback(int dir)
{
	Player_SetDamege(dir);
}

CollisionRectangle Player_GetCollision() {
	return PlayerCollision_GetOldCollision();
}

bool Player_GetStrong()
{
	if (StrongTime > 0)return true;
	return false;
}

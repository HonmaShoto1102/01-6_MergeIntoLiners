#ifndef PLAYEREFFECT_H
#define PLAYEREFFECT_H

enum PEFFECT
{
	pe_callFairy,    //�d���Ăяo��
	pe_flyMoving,    //��s
};



void PlayerEffect_Load();
void PlayerEffect_Init();
void PlayerEffect_Update();
void PlayerEffect_Final();

void PlayerEffect_SetEffect(PEFFECT pe, float x, float y);

#endif // !PLAYEREFFECT_H


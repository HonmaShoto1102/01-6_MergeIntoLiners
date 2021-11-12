#ifndef PLAYEREFFECT_H
#define PLAYEREFFECT_H

enum PEFFECT
{
	pe_callFairy,    //ódê∏åƒÇ—èoÇ∑
	pe_flyMoving,    //îÚçs
};



void PlayerEffect_Load();
void PlayerEffect_Init();
void PlayerEffect_Update();
void PlayerEffect_Final();

void PlayerEffect_SetEffect(PEFFECT pe, float x, float y);

#endif // !PLAYEREFFECT_H


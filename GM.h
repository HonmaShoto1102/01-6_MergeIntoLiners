#ifndef GM_H
#define GM_H
#include"config.h"

void GM_Init();
void GM_Final();
void GM_Update();
void GM_Draw();


void GM_DrawLayer();


int GM_AddParticle(ParticleC* pParticle);
int GM_UnAddParticle(int pID,int layer);
int GM_AddSprite(SpriteC* pSprite);
int GM_UnAddSprite(int aID);
int GM_AddAnimation(AnimationC* pAni);
int GM_UnAddAnimation(int aniID);
int GM_AddMoveAni(AnimationMove* mAni);
int GM_UnAddMoveAni(int aniID);
CameraC* GM_mainCamera();

#endif // !GM_H


#ifndef PLAYERACTION_H
#define PLAYERACTION_H
#include "base_Sprite.h"

enum ANIe
{
	ani_standby,
	ani_move,
	ani_airUp,
	ani_airDown,
	ani_jumpGrund,
	ani_jumpAir,
	ani_callVertica,
	ani_callHolizy,
	ani_damege,
	ani_goHeart,
	ani_goHeartUp,
	ani_leaveHeart,
	ani_heartRotate,
	ani_heartCallVertica,
	ani_heartCallHolizy,
	ani_backToOrigin,
	ani_heartBoxMove,
	ani_dead,
};

void PlayerAction_Load();
void PlayerAction_Init();
void PlayerAction_Update();
void PlayerAction_Final();

void PlayerAction_SetPosition(float x, float y);
void PlayerAction_SetDirction(int dirx,int diry);
void PlayerAction_SetAction(ANIe ani,int time = 0);
void PlayerAction_SetOneStickPos(float x, float y,int Dir);

void PlayerAction_SetSpriteAngle(float anl);
float PlayerAction_GetOneStickAngle();
void PlayerAction_SetOneStickAngle(float ang);

void PlayerAction_SetOneStickModel(bool b);

SpriteC* PlayerAction_GetOneStickSprite();
#endif // !PLAYERACTION_H


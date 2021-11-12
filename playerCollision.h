#ifndef PLAYERCOLLISION_H
#define PLAYERCOLLISION_H

#include "playerData.h"



void PlayerCollision_Load();
void PlayerCollision_Init();
void PlayerCollision_Update();
void PlayerCollision_Final();

//移動ボタン
void PlayerCollision_InputA();
void PlayerCollision_InputD();
void PlayerCollision_InputW();
void PlayerCollision_InputS();


void PlayerCollision_ToHeart();
void PlayerCollision_LeaveHeart();
void PlayerCollision_CallVertica();
void PlayerCollision_CallHorizy();


//void PlayerCollision_SetPosX(float x);
//void PlayerCollision_SetPosY(float y);


CollisionRectangle PlayerCollision_GetCollision();
CollisionRectangle PlayerCollision_GetOldCollision();

//プレイヤーが敵がアタックしてから、着地した瞬間trueに戻る
bool Player_isReturn();
void Player_SetReturn(bool Re);

//バレットタイム取得
float Player_GetBulletTime();
//方向ゲート
PL_DIR Player_GetDirection();
//プレイヤー状態取得
//PL_STATEe Player_GetState();
//プレイヤー座標取得
//float Player_GetPosX();
//float Player_GetPosY();
//"1"の方向を取得。
PL_DIR Player_OnStackDir();
float Player_GetOnStackAngle();
//今の持っているハートを取得。
float2D Player_GetHeartPos();

SpriteC* Player_GetOneStickSprite();


//***********************************************
//**************************Set*******************
//***********************************************
void SetAreaport(float x, float y);
void SetTeleport(float x, float y);
void Player_SetDamege(int dir);

void PlayerCollision_StageClear(float x,float y);
void Player_SetState_backToOrigin(float x,float y);
void Player_SetState_GobyLine();
void Player_SetState_Dead();
void Player_PositionReSet(float x, float y);

#endif // !PLAYERCOLLISION_H


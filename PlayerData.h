#ifndef PLAYERDATA_H
#define PLAYERDATA_H
#include "config.h"


#define PLAYER_WIDTH (128.0f * 0.9f)
#define PLAYER_HEIGHT (192.0f * 0.9f)
#define PLAYER_SPEED (10.0f)
//プレイヤーの方向
enum PL_DIR
{
	RIGHT = 1,
	LIFT = -1,
};
//プレイヤーの状態
enum PL_STATEe {
	ps_default,              //デフォルト状態、自由移動、落下など
	ps_goHeart,              //ハートに移動状態１（ハート飛んでいく）
	ps_goHeartUp,            //ハートに移動状態２ (ハート上に登る)
	ps_heartRotate,          //ハート上に、１を回る状態、
	ps_leaveHeart,           //ハートから飛んでいく状態、
	ps_backToOrigin,         //敵にアタックしてから、原点戻り
	ps_teleport,             //瞬間移動状態
	ps_heartBoxMove,
	ps_takeDamege_enemy,     //敵からのダメージ受け状態
	ps_takeDamege_box,       //マップボックスからのダメージ受け状態
	ps_goByLine,             //ラインに沿って、移動する
	ps_leaveHeart2,          //ラインに沿って、ハートから飛んでいく。
	ps_dead,                 //死ぬ
	ps_transBoxMove,         //ステージ切り替えボックスに移動
	ps_transBoxStand,        //ステージ切り替えボックスに待機
	ps_stageClear,           //ステージクリア
	//ps_callVertica,          
	//ps_callHorizy,
	//ps_callVerticaOnHeart,
	//ps_callHorizyOnHeart,
};

void PlayerData_Load();
void PlayerData_Init();
void PlayerData_Update();
void PlayerData_Final();

//************************************************************************
//************************Get//Get//Get//Get//Get*************************
//************************************************************************
//playerのHP値を取得。
int Player_GetHP();
int Player_GetMaxHP();

//playerの座標を取得。
float Player_GetPosX();
float Player_GetPosY();

//playerの状態（ステート）を取得。
PL_STATEe Player_GetState();

//playerの当たり判定boxを取得。
CollisionRectangle Player_GetCollision();

//playerの無敵状態を取得。
bool Player_GetStrong();
//************************************************************************
//************************Set//Set//Set//Set//Set*************************
//************************************************************************
//HP
void Player_SetHP(int hp);    //HPを設定します, HP = hp;
void Player_PlusHP(int hp);   //HPを増加, HP += hp;
void Player_MinusHP(int hp);  //HPを減少, HP -= hp;

void Player_SeedDamegeMessage(int hp, int dir);
void Player_SetDamegeFeedback(int dir);
//妖精

#endif // !PLAYERDATA_H


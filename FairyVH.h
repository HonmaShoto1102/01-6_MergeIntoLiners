#ifndef FAIRYVH_H
#define FAIRYVH_H
#include "base_Sprite.h"

#define LIMIT_LENGTH (0)
#define LIMIT_FAIRY (96)
#define FAIRY_SIZE (12)
#define LINEAS_TIME (300)
#define FAIRYAS_TIME (500)
#define VERTICA_LINELENGTH_MAX (1000)
#define HORIZY_LINELENGTH_MAX (1400)
#define OBLMOVING_LINELENGTH_HALF (750)
#define EN_PSIZE (64)
#define ST_PSIZE (64)
#define FMAX (3)

//妖精状態
enum FAIRYSTATEe
{
	fs_stand,     //待機状態
	fs_appear,    //プレイヤーが地面に呼び出す時の(出現)移動状態
	fs_oblmoving, //プレイヤーがハート上に、妖精の(出現)移動状態
	//fs_moving,
	fs_lineBecome,//ラインになる状態
	fs_coverStrong,//強化ラインになる。
	fs_origin,    //妖精がプレイヤーに戻る状態
};
enum FAIRYNAMEe {
	VERTICA,
	HORIZY,
};


struct FAIRY {
	SpriteC* sprite;    //妖精の本体スプライト
	SpriteC* endPoint;  //カーソルのスプライト
	float posX;         //妖精本体座標点
	float posY;         
	float endX;         //カーソル座標点
	float endY;
	FAIRYNAMEe name;
	int fairyID;
	//Coll coll;
};


void FairyVH_Load();
void FairyVH_Init();
void FairyVH_Update();
void FairyVH_Final();

void FairyVH_TransNextFairy(FAIRYNAMEe fse);

void FairyVH_SetLockV(bool loc,int num);
void FairyVH_SetLockH(bool loc, int num);
void FairyVH_SetLockAll(bool loc);

void FairyVH_SetLockAllV(bool loc);
void FairyVH_SetLockAllH(bool loc);

void FairyVH_DeleteFairyV(int fairyNum);
void FairyVH_DeleteFairyH(int fairyNum);

bool FairyVH_GetboolByFocus();

//妖精のポイントが取得
FAIRY* FairyVH_GetVertica(int id = 0);
FAIRY* FairyVH_GetHorizy(int id = 0);
//妖精の状態を取得。
FAIRYSTATEe FairyVH_GetStateV(int id);
FAIRYSTATEe FairyVH_GetStateH(int id);

bool FairyVH_GetStateForAllV(FAIRYSTATEe fs);
bool FairyVH_GetStateForAllH(FAIRYSTATEe fs);

//妖精のCollision取得
CollisionCircle FairyVH_GetCollisionV(int id = 0);
CollisionCircle FairyVH_GetCollisionH(int id = 0);

CollisionCircle FairyVH_GetCurrentCollisionV();
CollisionCircle FairyVH_GetCurrentCollisionH();

bool FairyVH_GetActiveV(int id = 0);
bool FairyVH_GetActiveH(int id = 0);

void FairyVH_SetFairyDirH(int dir);

//妖精がラインになる時間取得。(フレームを単位として)
//ラインが自然消すのタイムカウント
int FairyVH_GetTimeOfLine_CountDownV(int id = 0);
int FairyVH_GetTimeOfLine_CountDownH(int id = 0);

//ラインが消すまで必要な時間。
//ラインが自然存在している時間の長さ
int FairyVH_GetTimeOfLine_DurationV(int id = 0);
int FairyVH_GetTimeOfLine_DurationH(int id = 0);

//妖精が出現した時間を取得。
//妖精がラインにならないうちに、自然消滅タイムカウント
int FairyVH_GetTimeOfFairy_CountDownV(int id = 0);
int FairyVH_GetTimeOfFairy_CountDownH(int id = 0);

//妖精を消すまでに必要な時間。
//妖精がラインにならないうちに、存在している時間の長さ
int FairyVH_GetTimeOfFairy_DurationV(int id = 0);
int FairyVH_GetTimeOfFairy_DurationH(int id = 0);

//妖精のCoolTimeを取得。
//ラインが呼び出せるまでにのタイムカウント
int FairyVH_GetCoolTimeV(int id = 0);
int FairyVH_GetCoolTimeH(int id = 0);

//CoolTimeの最大値を取得。
//ラインが呼び出せるまでに必要な時間の長さを取得。
int FairyVH_GetCoolTimeMaxV(int id = 0);
int FairyVH_GetCoolTimeMaxH(int id = 0);

//cooltimeの値と最大値の比率を取得
//返す値が＞0.0f時、ラインがが呼び出せない、
//返す値が＝0.0f時、ラインがが呼び出せる
float FairyVH_CoolTimePercentV(int id = 0);
float FairyVH_CoolTimePercentH(int id = 0);


//プロトタイプ版の臨時関数。


#endif // !FAIRYVH_H


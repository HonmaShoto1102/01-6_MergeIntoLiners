#ifndef HEART_H
#define HEART_H
#include "base_Sprite.h"
#define HEARTMAX (8)
#define HEARTNULL (HEARTMAX + 1)
#define LINENUMBER_INV (-1)

//交点のタイプ
enum HeartType
{
	Diagonal,       //直角ではない(普通の交点)
	RightAngle,     //直角ハート(ハート)
};

typedef struct HeartTag {
	SpriteC* sp;              
	int l1;                  //交点を生成するライン１の番号
	int l2;                  //交点を生成するライン２の番号
	HeartType ht;            //交点の種類
	int uiNumber;            //uiに展示する数字
	bool active;
}Heart;

void Heart_Load();
void Heart_Init();
void Heart_Update();
void Heart_Final();


//int Heart_SetHeart(float x, float y);

//交点があるかを判定する関数。
bool Heart_GetFlag();

//next交点を取得,使わないでください。
Heart* Heart_GetHeart();

//交点を生成する
int Heart_CreateHeart(float x, float y, int L1, int L2,HeartType HT);

//交点を消す
void Heart_DeleteHeart(int lineNum);

//交点記録番号をリセット
void Heart_ReSet();

//次の交点は最後の交点ですか。
bool Heart_isEndHeart();

//図形を生成
void Heart_CreateFigure();

//図形を移動
void Heart_MoveFigure(float x, float y);

//******************************************
//******************************************

//今存在している交点の個数
int Heart_GetHeartCount();

//番号によって、交点を取得。
Heart* Heart_GetHeart(int hNumber);

//プレイヤーの現在地ハート番号取得
int Heart_GetCurrentHeartNum();




#endif // !HEART_H

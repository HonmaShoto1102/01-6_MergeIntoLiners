#ifndef LINE_H
#define LINE_H
#include "collision.h"
#include "base_Sprite.h"
#define LINEMAX (5)
#define LINENULL (-1)
//ラインの方向タイプ
enum ltp
{
	l_lhory,
	l_lvert,
	l_oleft,
	l_oright,
};
//ラインのタイプ
enum FAIRY_LINEe
{
	fl_defalt,  //普通
	fl_strong,  //強化ライン
};
//ラインの色
enum LINECOLOR {
	lc_red,
	lc_blue,
	lc_green,
	lc_yellow,
	lc_black,
	lc_pink,
};

enum LINEST {
	ls_off,  //隠れ
	ls_on,   //長さ完全
	ls_ing,  //伸びている
	ls_str,  //強化ラインでカーバー。
};
//創造者を指定
enum LINE_CREATERe {
	lineCreater_Fairy,
	lineCreater_Block,
	lineCreater_Enemy,
};

struct LINE
{
	SpritePA* sp;
	float2D startPos;
	float2D endPos;
	float2D currentEpos;
	float length;
	float lenghtMax;
	float angle;
	int Num;
	ltp lintType;
	FAIRY_LINEe fl;
	LINECOLOR lc;
	int age;
	LINEST st;
	LINE_CREATERe lineCreater;
	int contextID;        //影響を与えられるラインの番号。
	int rlineID;          //入射ラインと反射ラインの関係
	CollisionLine GetColl() {
		return {startPos.x, startPos.y, currentEpos.x, currentEpos.y};
	}
	CollisionLine GetCollMax() {
		return { startPos.x,startPos.y,endPos.x,endPos.y };
	}
};

void Line_Load();
void Line_Init();
void Line_Update();
void Line_Final();


//ラインが生成と消す
void Line_CreateLineV(int count,float sx, float sy, float ex, float ey,FAIRY_LINEe fl = fl_defalt);
void Line_CreateLineStrongV(int count, float sx, float sy, float ex, float ey, int context, FAIRY_LINEe fl = fl_strong);
void Line_DeleteLineV(int count);
void Line_CreateLineH(int count, float sx, float sy, float ex, float ey, FAIRY_LINEe fl = fl_defalt);
void Line_CreateLineStrongH(int count, float sx, float sy, float ex, float ey, int context, FAIRY_LINEe fl = fl_strong);
void Line_DeleteLineH(int count);
LINE* Line_GetLineMessageV(int num);
LINE* Line_GetLineMessageH(int num);
//マップラインが生成
//LINECOLORは色を指定。
//LINE_CREATEReは創造者
//FAIRY_LINEeは普通ラインか、強化ラインかを指定
int Line_CreateLineMap(float sx, float sy, float ex, float ey,LINECOLOR lc = lc_black,LINE_CREATERe creater = lineCreater_Block,FAIRY_LINEe fl = fl_defalt);
int Line_CreateLineMap(float sx, float sy, float ex, float ey, int reline, LINECOLOR lc = lc_black, LINE_CREATERe creater = lineCreater_Block, FAIRY_LINEe fl = fl_defalt);

void Line_DeleteLineMap(int Number);
void Line_BecomeStrongLineMap(int Number);

void Line_DeleteLineAll();

//今活動中のラインの数を取る（FairyVerticaとFairyHorizyを除く）。
int Line_GetAllNumber();

CollisionLine Line_GetLine(int lineNum);
CollisionLine Line_GetLineV(int count);
CollisionLine Line_GetLineH(int count);
CollisionLine Line_GetCurrentLineV();
CollisionLine Line_GetCurrentLineH();
CollisionLine Line_GetCollisionLineForNumberAll(int lineNum);
//void Line_DeleteLineForNumberAll(int lineNum);
//特定のファイルに作ったやつ、デバック用
//LINE* Line_GetLineForNumberAllOBJ(int lineNum);

//ラインが取りたいなら、こっちのオススメ
LINE* Line_GetLineForNumberAllMAP(int lineNum);
LINE* Line_GetEndLine();
bool Line_GetActiveLineV(int count);
bool Line_GetActiveLineH(int count);
bool Line_GetActiveLineV();
bool Line_GetActiveLineH();

#endif // !LINE_H


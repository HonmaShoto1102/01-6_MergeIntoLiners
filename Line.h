#ifndef LINE_H
#define LINE_H
#include "collision.h"
#include "base_Sprite.h"
#define LINEMAX (5)
#define LINENULL (-1)
//���C���̕����^�C�v
enum ltp
{
	l_lhory,
	l_lvert,
	l_oleft,
	l_oright,
};
//���C���̃^�C�v
enum FAIRY_LINEe
{
	fl_defalt,  //����
	fl_strong,  //�������C��
};
//���C���̐F
enum LINECOLOR {
	lc_red,
	lc_blue,
	lc_green,
	lc_yellow,
	lc_black,
	lc_pink,
};

enum LINEST {
	ls_off,  //�B��
	ls_on,   //�������S
	ls_ing,  //�L�тĂ���
	ls_str,  //�������C���ŃJ�[�o�[�B
};
//�n���҂��w��
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
	int contextID;        //�e����^�����郉�C���̔ԍ��B
	int rlineID;          //���˃��C���Ɣ��˃��C���̊֌W
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


//���C���������Ə���
void Line_CreateLineV(int count,float sx, float sy, float ex, float ey,FAIRY_LINEe fl = fl_defalt);
void Line_CreateLineStrongV(int count, float sx, float sy, float ex, float ey, int context, FAIRY_LINEe fl = fl_strong);
void Line_DeleteLineV(int count);
void Line_CreateLineH(int count, float sx, float sy, float ex, float ey, FAIRY_LINEe fl = fl_defalt);
void Line_CreateLineStrongH(int count, float sx, float sy, float ex, float ey, int context, FAIRY_LINEe fl = fl_strong);
void Line_DeleteLineH(int count);
LINE* Line_GetLineMessageV(int num);
LINE* Line_GetLineMessageH(int num);
//�}�b�v���C��������
//LINECOLOR�͐F���w��B
//LINE_CREATERe�͑n����
//FAIRY_LINEe�͕��ʃ��C�����A�������C�������w��
int Line_CreateLineMap(float sx, float sy, float ex, float ey,LINECOLOR lc = lc_black,LINE_CREATERe creater = lineCreater_Block,FAIRY_LINEe fl = fl_defalt);
int Line_CreateLineMap(float sx, float sy, float ex, float ey, int reline, LINECOLOR lc = lc_black, LINE_CREATERe creater = lineCreater_Block, FAIRY_LINEe fl = fl_defalt);

void Line_DeleteLineMap(int Number);
void Line_BecomeStrongLineMap(int Number);

void Line_DeleteLineAll();

//���������̃��C���̐������iFairyVertica��FairyHorizy�������j�B
int Line_GetAllNumber();

CollisionLine Line_GetLine(int lineNum);
CollisionLine Line_GetLineV(int count);
CollisionLine Line_GetLineH(int count);
CollisionLine Line_GetCurrentLineV();
CollisionLine Line_GetCurrentLineH();
CollisionLine Line_GetCollisionLineForNumberAll(int lineNum);
//void Line_DeleteLineForNumberAll(int lineNum);
//����̃t�@�C���ɍ������A�f�o�b�N�p
//LINE* Line_GetLineForNumberAllOBJ(int lineNum);

//���C������肽���Ȃ�A�������̃I�X�X��
LINE* Line_GetLineForNumberAllMAP(int lineNum);
LINE* Line_GetEndLine();
bool Line_GetActiveLineV(int count);
bool Line_GetActiveLineH(int count);
bool Line_GetActiveLineV();
bool Line_GetActiveLineH();

#endif // !LINE_H


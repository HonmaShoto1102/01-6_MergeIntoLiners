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

//�d�����
enum FAIRYSTATEe
{
	fs_stand,     //�ҋ@���
	fs_appear,    //�v���C���[���n�ʂɌĂяo������(�o��)�ړ����
	fs_oblmoving, //�v���C���[���n�[�g��ɁA�d����(�o��)�ړ����
	//fs_moving,
	fs_lineBecome,//���C���ɂȂ���
	fs_coverStrong,//�������C���ɂȂ�B
	fs_origin,    //�d�����v���C���[�ɖ߂���
};
enum FAIRYNAMEe {
	VERTICA,
	HORIZY,
};


struct FAIRY {
	SpriteC* sprite;    //�d���̖{�̃X�v���C�g
	SpriteC* endPoint;  //�J�[�\���̃X�v���C�g
	float posX;         //�d���{�̍��W�_
	float posY;         
	float endX;         //�J�[�\�����W�_
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

//�d���̃|�C���g���擾
FAIRY* FairyVH_GetVertica(int id = 0);
FAIRY* FairyVH_GetHorizy(int id = 0);
//�d���̏�Ԃ��擾�B
FAIRYSTATEe FairyVH_GetStateV(int id);
FAIRYSTATEe FairyVH_GetStateH(int id);

bool FairyVH_GetStateForAllV(FAIRYSTATEe fs);
bool FairyVH_GetStateForAllH(FAIRYSTATEe fs);

//�d����Collision�擾
CollisionCircle FairyVH_GetCollisionV(int id = 0);
CollisionCircle FairyVH_GetCollisionH(int id = 0);

CollisionCircle FairyVH_GetCurrentCollisionV();
CollisionCircle FairyVH_GetCurrentCollisionH();

bool FairyVH_GetActiveV(int id = 0);
bool FairyVH_GetActiveH(int id = 0);

void FairyVH_SetFairyDirH(int dir);

//�d�������C���ɂȂ鎞�Ԏ擾�B(�t���[����P�ʂƂ���)
//���C�������R�����̃^�C���J�E���g
int FairyVH_GetTimeOfLine_CountDownV(int id = 0);
int FairyVH_GetTimeOfLine_CountDownH(int id = 0);

//���C���������܂ŕK�v�Ȏ��ԁB
//���C�������R���݂��Ă��鎞�Ԃ̒���
int FairyVH_GetTimeOfLine_DurationV(int id = 0);
int FairyVH_GetTimeOfLine_DurationH(int id = 0);

//�d�����o���������Ԃ��擾�B
//�d�������C���ɂȂ�Ȃ������ɁA���R���Ń^�C���J�E���g
int FairyVH_GetTimeOfFairy_CountDownV(int id = 0);
int FairyVH_GetTimeOfFairy_CountDownH(int id = 0);

//�d���������܂łɕK�v�Ȏ��ԁB
//�d�������C���ɂȂ�Ȃ������ɁA���݂��Ă��鎞�Ԃ̒���
int FairyVH_GetTimeOfFairy_DurationV(int id = 0);
int FairyVH_GetTimeOfFairy_DurationH(int id = 0);

//�d����CoolTime���擾�B
//���C�����Ăяo����܂łɂ̃^�C���J�E���g
int FairyVH_GetCoolTimeV(int id = 0);
int FairyVH_GetCoolTimeH(int id = 0);

//CoolTime�̍ő�l���擾�B
//���C�����Ăяo����܂łɕK�v�Ȏ��Ԃ̒������擾�B
int FairyVH_GetCoolTimeMaxV(int id = 0);
int FairyVH_GetCoolTimeMaxH(int id = 0);

//cooltime�̒l�ƍő�l�̔䗦���擾
//�Ԃ��l����0.0f���A���C�������Ăяo���Ȃ��A
//�Ԃ��l����0.0f���A���C�������Ăяo����
float FairyVH_CoolTimePercentV(int id = 0);
float FairyVH_CoolTimePercentH(int id = 0);


//�v���g�^�C�v�ł̗Վ��֐��B


#endif // !FAIRYVH_H


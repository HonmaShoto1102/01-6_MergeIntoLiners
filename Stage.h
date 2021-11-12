#ifndef STAGE_H
#define STAGE_H
#include "base_MapBlock.h"
#include "collision.h"


#define STAGEMAX (10)
//�}�b�v����block�̃^�C�v
enum BL_TYPE
{
	bl_collisionBox,   //�n�ʁA�ǂȂǂ̃v���C���[����Ȃ�box
	bl_textureBox,     //�����ȕ`��X�v���C�g�B
	bl_heartBox,
	bl_stageTransBox,
	bl_goalBox,
	bl_damegeBox,
	bl_lineBox,
	bl_moveBox,
	bl_enemyBox,
	bl_diagonalBox,
	bl_enemy2Box,
	bl_eventBox,
	bl_mirrorBox,
	bl_Max,
};

struct STAGEDATA
{
	int stageNumber;
	int boxCount;
	int kindCount[bl_Max];
};


void Stage_Load();
void Stage_Init();
void Stage_Update();
void Stage_Final();

//�G�l�~�[�������Ă�֘A�n�[�gID��n���܂��B
void Stage_heartBoxCreate(int id);
int Stage_GetNowStageNumber();
//int Stage_GetNextStageNumber();

void Stage_Translation(int stageNumber);

float2D Stage_mapCheck(float2D stPos, float2D dir);
//�w��^�C�v��block�����擾�B
int Stage_GetNumberOfBlock(BL_TYPE bl_type);
//�w��ԍ���block�Ɠ����蔻��A����������A����box���擾�A�������ĂȂ�NULL��߂�B
//�p�����[�^�P�A����ڕWbox�A�p�����[�^�Q�Ablock�ԍ�
M_collsionBOX* Stage_collisionBOX_hit(CollisionRectangle* PayerBOX,int boxNum);
M_textureBOX* Stage_textureBOX_hit(CollisionRectangle* PlayerBOX, int boxNum);

M_collsionBOX * Stage_collisionBOX_hitWithLine(CollisionLine Lc, int boxNum);
M_collsionBOX * Stage_collisionBOX_Get(int boxNum);

M_heartBox* Stage_heartBox_hitWithPoint(float x, float y, int boxNum);
M_damegeBox* Stage_damegeBox_hit(CollisionRectangle pB, int boxNum);

M_lineCreateBox* Stage_lineBox_hit(float x, float y, int boxNum);

M_stageTransBox* Stage_transBox_hit(CollisionRectangle* playerBOX, int boxNum);

//�G�l�~�[�{�b�N�X�̃��b�Z�[�W���擾
M_enemyBox* Stage_enemyBox_byNumber(int boxNum);

M_diagonalCollisionBox* Stage_diagonalBox_byNumber(int boxNum);

//�n�[�g�֘A�G�l�~�[�̃��b�Z�[�W���擾
M_enemy2Box* Stage_GetEnemy2Box_byNumber(int boxNum);

M_eventBox* Stage_GetEventBox_byNumber(int boxNum);

M_mirorrBox* Stage_GetMirrorBox_byNumber(int boxNum);

M_goalBox* Stage_GetGoalBox_byNumber(int boxNum);

//�}�b�v���̂��ׂł̋���L��or����
void Stage_SetMirrorON_or_OFF(int trigger);

#endif // !STATE_H


#ifndef PLAYERDATA_H
#define PLAYERDATA_H
#include "config.h"


#define PLAYER_WIDTH (128.0f * 0.9f)
#define PLAYER_HEIGHT (192.0f * 0.9f)
#define PLAYER_SPEED (10.0f)
//�v���C���[�̕���
enum PL_DIR
{
	RIGHT = 1,
	LIFT = -1,
};
//�v���C���[�̏��
enum PL_STATEe {
	ps_default,              //�f�t�H���g��ԁA���R�ړ��A�����Ȃ�
	ps_goHeart,              //�n�[�g�Ɉړ���ԂP�i�n�[�g���ł����j
	ps_goHeartUp,            //�n�[�g�Ɉړ���ԂQ (�n�[�g��ɓo��)
	ps_heartRotate,          //�n�[�g��ɁA�P������ԁA
	ps_leaveHeart,           //�n�[�g������ł�����ԁA
	ps_backToOrigin,         //�G�ɃA�^�b�N���Ă���A���_�߂�
	ps_teleport,             //�u�Ԉړ����
	ps_heartBoxMove,
	ps_takeDamege_enemy,     //�G����̃_���[�W�󂯏��
	ps_takeDamege_box,       //�}�b�v�{�b�N�X����̃_���[�W�󂯏��
	ps_goByLine,             //���C���ɉ����āA�ړ�����
	ps_leaveHeart2,          //���C���ɉ����āA�n�[�g������ł����B
	ps_dead,                 //����
	ps_transBoxMove,         //�X�e�[�W�؂�ւ��{�b�N�X�Ɉړ�
	ps_transBoxStand,        //�X�e�[�W�؂�ւ��{�b�N�X�ɑҋ@
	ps_stageClear,           //�X�e�[�W�N���A
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
//player��HP�l���擾�B
int Player_GetHP();
int Player_GetMaxHP();

//player�̍��W���擾�B
float Player_GetPosX();
float Player_GetPosY();

//player�̏�ԁi�X�e�[�g�j���擾�B
PL_STATEe Player_GetState();

//player�̓����蔻��box���擾�B
CollisionRectangle Player_GetCollision();

//player�̖��G��Ԃ��擾�B
bool Player_GetStrong();
//************************************************************************
//************************Set//Set//Set//Set//Set*************************
//************************************************************************
//HP
void Player_SetHP(int hp);    //HP��ݒ肵�܂�, HP = hp;
void Player_PlusHP(int hp);   //HP�𑝉�, HP += hp;
void Player_MinusHP(int hp);  //HP������, HP -= hp;

void Player_SeedDamegeMessage(int hp, int dir);
void Player_SetDamegeFeedback(int dir);
//�d��

#endif // !PLAYERDATA_H


/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
�C�x���g���W���[��

�����:��������
�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/

#include "Event.h"
#include "GM.h"
#include "base_Sprite.h"
#include "keyloger.h"

#include "playerAction.h"
#include "playerCollision.h"
#include "PlayerData.h"
#include "uiDisplay.h"
#include "Map_Manager.h"
#include "FairyVH.h"
#include "Line.h"
#include "debugPrintf.h"

#include "InputManager.h"

typedef void(*EventFunction)(void);

//�X�e�[�W�P�̃A�N�V����
void Event_Stage1(void);

//�X�e�[�W�Q�̃A�N�V����
void Event_Stage2(void);

//�X�e�[�W�R�̃A�N�V����
void Event_Stage3(void);

//�X�e�[�W�S�̃A�N�V����
void Event_Stage4(void);
//��b�C�x���g
void Event_TalkEvent(void);

namespace ne
{
	int EventNumber;//�֐��|�C���^�̉��Ԗڂ����s���邩�w�肷�邽�߂̕ϐ�
	int StageNumber;

	EventFunction ActionEvent[] =
	{
	   Event_Stage1,      //���s�݂̂̃C�x���g
	   Event_Stage2, //�z���C�W�[(����)����
	   Event_Stage3,//�o�e�B�J(�c��)����
	   Event_Stage4,  //���ٓ_����
	};
}

void Event_Load(void)
{
	;//���̂Ƃ���̓i�V
}

void Event_Init(void)
{
	ne::EventNumber = EVENTTYPE_NONE;
}

void Event_Update(void)
{
	ne::ActionEvent[ne::StageNumber % 4]();

	//�f�o�b�O�p
	if (keylogger_Trigger(KL_L))
	{
		Event_SetStageEvent(Event_GetEventNumber() + 1);
	}


}

void Event_Unload(void)
{
	;//���̂Ƃ���̓i�V
}

void Event_Stage1(void)
{
	;
}

void Event_Stage2(void)
{
	;
}

void Event_Stage3(void)
{
	;
}

void Event_Stage4(void)
{
	;
}

void Event_TalkEvent(void)
{
	//�{�Ԃ̐��삵���e�L�X�g�v���O������}��

	//if (keylogger_Release(KL_ENTER))
	//{
	//	//�w��̃L�[����������Z���t�X�V
	//}
}

void Event_SetStageEvent(int type)
{
	ne::EventNumber = type;

	switch (ne::EventNumber)
	{
	case EVENTTYPE_WALK:
		SetKey_MoveA(true);
		SetKey_MoveD(true);
		SetKey_CallFairyV(false);
		SetKey_CallFairyH(false);
		SetKey_LineCreatV(false);
		SetKey_LineCreatH(false);
		SetKey_DestroyAll(false);
		SetKey_Attack(false);
		SetKey_LineDir(false);
		SetFairyMaxV(0);
		SetFairyMaxH(0);
		break;

	case EVENTTYPE_DRAW_HORIZY:
		SetKey_MoveA(true);
		SetKey_MoveD(true);
		SetKey_CallFairyV(false);
		SetKey_CallFairyH(true);
		SetKey_LineCreatV(false);
		SetKey_LineCreatH(true);
		SetKey_DestroyAll(true);
		SetKey_Attack(true);
		SetKey_LineDir(true);
		SetFairyMaxV(0);
		SetFairyMaxH(1);
		break;

	case EVENTTYPE_DRAW_VERTICA:
		SetKey_MoveA(true);
		SetKey_MoveD(true);
		SetKey_CallFairyV(true);
		SetKey_CallFairyH(true);
		SetKey_LineCreatV(true);
		SetKey_LineCreatH(true);
		SetKey_DestroyAll(true);
		SetKey_Attack(true);
		SetKey_LineDir(true);
		SetFairyMaxV(1);
		SetFairyMaxH(0);
		break;

	case EVENTTYPE_TALK:
		SetKey_MoveA(false);
		SetKey_MoveD(false);
		SetKey_CallFairyV(false);
		SetKey_CallFairyH(false);
		SetKey_LineCreatV(false);
		SetKey_LineCreatH(false);
		SetKey_DestroyAll(false);
		SetKey_Attack(false);
		SetKey_LineDir(false);
		SetFairyMaxV(1);
		SetFairyMaxH(1);
		break;

	default:
		SetKey_MoveA(true);
		SetKey_MoveD(true);
		SetKey_CallFairyV(true);
		SetKey_CallFairyH(true);
		SetKey_LineCreatV(true);
		SetKey_LineCreatH(true);
		SetKey_DestroyAll(true);
		SetKey_Attack(true);
		SetKey_LineDir(true);
		SetFairyMaxV(1);
		SetFairyMaxH(1);
		break;
	}
}

void Event_SetStageEvent(STAGE stage_num)
{
	if (stage_num == STAGE_1)
	{
		DebugPrintf("STAGE_1�͂����ł͖����ł��B�g�p���Ȃ��ł�������\n");
		return;
	}
	switch (stage_num)
	{
	case STAGE_2:
		SetKey_MoveA(true);
		SetKey_MoveD(true);
		SetKey_CallFairyV(true);
		SetKey_CallFairyH(true);
		SetKey_LineCreatV(true);
		SetKey_LineCreatH(true);
		SetKey_DestroyAll(true);
		SetKey_Attack(true);
		SetKey_LineDir(true);
		break;

	case STAGE_3:
		SetKey_MoveA(true);
		SetKey_MoveD(true);
		SetKey_CallFairyV(false);
		SetKey_CallFairyH(true);
		SetKey_LineCreatV(false);
		SetKey_LineCreatH(true);
		SetKey_DestroyAll(true);
		SetKey_Attack(true);
		SetKey_LineDir(true);
		SetFairyMaxV(0);
		SetFairyMaxH(2);
		break;

	case STAGE_4:
		SetKey_MoveA(true);
		SetKey_MoveD(true);
		SetKey_CallFairyV(true);
		SetKey_CallFairyH(true);
		SetKey_LineCreatV(true);
		SetKey_LineCreatH(true);
		SetKey_DestroyAll(true);
		SetKey_Attack(true);
		SetKey_LineDir(true);
		SetFairyMaxV(2);
		SetFairyMaxH(2);
		break;

	default:
		;
		break;
	}
}

int Event_GetEventNumber(void)
{
	return ne::EventNumber;
}
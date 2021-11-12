/*�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
�C�x���g���W���[��

�����:��������

�E�֐��|�C���^�̉��s�ڂ����s���邩���߂���yEventNumber�z�́A�����l��-1�������Ă���B

�E���i�K�ł́AU�L�[����������C�x���g���؂�ւ��A
�@S�L�[���������珉���l��-1������(��)�d�l�ɂȂ��Ă���

���C�x���g�ɂ���Ă͎g���Ȃ��L�[������
�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[*/
#pragma once
#ifndef EVENT_H_
#define EVENT_H_

#define EVENT_INVALID_NUMBER (-1)

//�C�x���g�w��p
//�{�Ԃł͂����p���ăC�x���g���̑���ƒʏ�̑����؂�ւ���
typedef enum EVENTTYPE_tag
{

	EVENTTYPE_NONE = EVENT_INVALID_NUMBER,//�C�x���g���I�����A�ʏ펞�̑���ɐ؂�ւ���
	EVENTTYPE_WALK,
	EVENTTYPE_DRAW_HORIZY,
	EVENTTYPE_DRAW_VERTICA,
	EVENTTYPE_CROSS_LINE,
	EVENTTYPE_TALK,
	EVENTTYPE_MAX
}EVENTTYPE;

typedef enum STAGE_tag
{
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_MAX,
}STAGE;

//�C�x���g���W���[���̃��[�h
void Event_Load(void);

//�C�x���g���W���[���̏�����
void Event_Init(void);

//�C�x���g���W���[���̍X�V
void Event_Update(void);

//�C�x���g���W���[���̏I������
void Event_Unload(void);

//�X�e�[�W1�̃C�x���g�w��
void Event_SetStageEvent(int type);

//�X�e�[�W2�`4�̃C�x���g�w��
void Event_SetStageEvent(STAGE stage_num);

//���ݍs���Ă���C�x���g�̔ԍ���Ԃ�
int Event_GetEventNumber(void);
#endif // !EVENT_H_


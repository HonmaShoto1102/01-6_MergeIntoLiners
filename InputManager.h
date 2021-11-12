#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define GO_HEART_COLLISION_OFF  (true)
#define CAMERA_FOCUS_FAIRY_OFF  (false)
#define SET_START_STAGE  (0)
#define SET_START_SCENE  (1)


//�ړ�����
void SetKey_MoveA(bool b);
void SetKey_MoveD(bool b);

bool GetKey_MoveA();
bool GetKey_MoveD();

//�d���o������
void SetKey_CallFairyV(bool b);
void SetKey_CallFairyH(bool b);

bool GetKey_CallFairyV();
bool GetKey_CallFairyH();

//���C������������
void SetKey_LineCreatV(bool b);
void SetKey_LineCreatH(bool b);

bool GetKey_LineCreatV();
bool GetKey_LineCreatH();

//�d���ƃ��C������������
void SetKey_DestroyAll(bool b);

bool GetKey_DestroyAll();

//�U���A����
void SetKey_Attack(bool b);

bool GetKey_Attack();

//�d�����΂߃��C��������������,player���n�[�g��̎��A�d�����΂߃��C�������\��AU�{�^�������������ł���
void SetKey_LineDir(bool b);
bool GetKey_LineDir();

//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�J�����{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
enum CAMERA_FOUCS
{
	cf_player,     //player���œ_
	cf_fariy,      //�d�����œ_
	cf_movingfairy,//�΂߃��C���Ɉړ����̗d��
	cf_event1,
};

void SetCamera_Foucs(CAMERA_FOUCS cf);
CAMERA_FOUCS GetCamera_Foucs();

//�d���Ăяo���鐔���w��
void SetFairyMaxV(int max);
void SetFairyMaxH(int max);

//�d���Ăяo���鐔���擾
int GetFairyMaxV();
int GetFairyMaxH();


//::::::::::::::::::::::::::::::::::::::���p�͈͕ύX::::::::::::::::::::::::::::::::::::::
void SetInCaves(bool on);
bool GetInCaves();


#endif // !INPUTMANAGER_H


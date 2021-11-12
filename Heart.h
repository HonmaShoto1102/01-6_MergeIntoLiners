#ifndef HEART_H
#define HEART_H
#include "base_Sprite.h"
#define HEARTMAX (8)
#define HEARTNULL (HEARTMAX + 1)
#define LINENUMBER_INV (-1)

//��_�̃^�C�v
enum HeartType
{
	Diagonal,       //���p�ł͂Ȃ�(���ʂ̌�_)
	RightAngle,     //���p�n�[�g(�n�[�g)
};

typedef struct HeartTag {
	SpriteC* sp;              
	int l1;                  //��_�𐶐����郉�C���P�̔ԍ�
	int l2;                  //��_�𐶐����郉�C���Q�̔ԍ�
	HeartType ht;            //��_�̎��
	int uiNumber;            //ui�ɓW�����鐔��
	bool active;
}Heart;

void Heart_Load();
void Heart_Init();
void Heart_Update();
void Heart_Final();


//int Heart_SetHeart(float x, float y);

//��_�����邩�𔻒肷��֐��B
bool Heart_GetFlag();

//next��_���擾,�g��Ȃ��ł��������B
Heart* Heart_GetHeart();

//��_�𐶐�����
int Heart_CreateHeart(float x, float y, int L1, int L2,HeartType HT);

//��_������
void Heart_DeleteHeart(int lineNum);

//��_�L�^�ԍ������Z�b�g
void Heart_ReSet();

//���̌�_�͍Ō�̌�_�ł����B
bool Heart_isEndHeart();

//�}�`�𐶐�
void Heart_CreateFigure();

//�}�`���ړ�
void Heart_MoveFigure(float x, float y);

//******************************************
//******************************************

//�����݂��Ă����_�̌�
int Heart_GetHeartCount();

//�ԍ��ɂ���āA��_���擾�B
Heart* Heart_GetHeart(int hNumber);

//�v���C���[�̌��ݒn�n�[�g�ԍ��擾
int Heart_GetCurrentHeartNum();




#endif // !HEART_H

#pragma once

/*!
	@file
	@brief    �Q�[�����[���h���̃I�u�W�F�N�g��UI�Ƃ��Ẳ��o��^���܂�
	@detales  Load,Init,Update,Unload�����ꂼ��K��̈ʒu�Ɏ���������A
	�@�@�@�@�@�Y���t�@�C���Ɂu uiDisplay.h �v���C���N���[�h���Ďg�p�\
		 �@�@ �ɂȂ�܂��B�����̌^�͂��ׂ�"SpriteC"�ɓ��ꂵ�܂��B
*/

#include "base_Sprite.h"
//#include "Fairy.h"

#ifndef _UI_SERIF_
#define _UI_SERIF_

/*--------------------  Public  ---------------------*/

void UiSerif_Load(void);
bool UiSerif_Init(void);
void UiSerif_Update(void);
void UiSerif_Unload(void);

/**------------------------------------------------------
�@@brief
	Vertica�EHorizy�̃��C���J�[�\����\������B
�@@detail
  �@�����Ɍ��݂̃v���C���[�̏��(Ground or Heart)�����
�@�@��ƁA����ɉ��������̃J�[�\����\�����܂��B
-------------------------------------------------------**/
//void UI_CursorTowardsVertica(PLAYER_STATE player_state);
//void UI_CursorTowardsHorizy(PLAYER_STATE player_state);
/**----------------------------------------------------**/


/**------------------------------------------------------
�@@brief
  �@�v���C���[�̊e�A�N�V�����ɑ΂���UI�I���o��^����
�@@detail
  �@AttackFromHeart...
	�n�[�g����̃A�^�b�N���Ɏg�p����B
	ReturnToOrigineAfterAttack...
	�A�^�b�N���G�l�~�[�ɓ������āA�����̍U����HP���O
	�ɂȂ����ۂɎg�p����B
-------------------------------------------------------**/
//void UI_AttackFromHeart(void);
//void UI_ReturnToOrigineAfterAttack(SpriteC* enemy);
/**----------------------------------------------------**/



/*--------------------  Private  ---------------------*/

// 

#endif // _UI_DISPLAY_

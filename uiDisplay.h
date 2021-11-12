/*---------------------------------------------------------------------------*/
//  FILE : uiDisplay.h
//
//         �@�@�@�@�@�@���[�U�[�C���^�[�t�F�[�X�̉��o
//
/*===========================================================================*/
//
//                                                          Author : R.Usui
/*---------------------------------------------------------------------------*/

/*!
	@file
	@brief    �Q�[�����[���h���̃I�u�W�F�N�g��UI�Ƃ��Ẳ��o��^���܂�
	@detail   Load,Init,Update,Unload�����ꂼ��K��̈ʒu�Ɏ���������A
	�@�@�@�@�@�Y���t�@�C���Ɂu uiDisplay.h �v���C���N���[�h���Ďg�p�\
		 �@�@ �ɂȂ�܂��B
*/
#pragma once

#include "Heart.h"

#ifndef _UI_DISPLAY_
#define _UI_DISPLAY_

void UI_Load(void);
void UI_Init(void);
void UI_Update(void);
void UI_Unload(void);

/**------------------------------------------------------
�@@brief
  �@�v���C���[�̊e�A�N�V�����ɑ΂��ĉ��o��^����B

�@@details
  �@AttackFromHeart...
    �n�[�g����̃A�^�b�N���Ɏg�p����B

	ReturnToOrigineAfterAttack...
	�A�^�b�N���G�l�~�[�ɓ������āA�����̍U����HP���O
	�ɂȂ����ۂɎg�p����B
	�����F�Y���̃G�l�~�[�̃X�v���C�g

	OneStickChangeToOne...
	��]����P����������^�C�~���O�̂����A�d�����Ăяo
	���Ƃ��Ɏg�p����B
	�����F�Y���̃n�[�g�C���X�^���X
*/
void UI_AttackFromHeart(void);
void UI_ReturnToOrigineAfterAttack(class Enemy* enemy);
void UI_OneStickChangetoOne(Heart* heart);
/*----------------------------------------------------**/

#endif /*_UI_DISPLAY_*/

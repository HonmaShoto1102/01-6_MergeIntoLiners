/*---------------------------------------------------------------------------*/
//  FILE : uiDisplay.h
//
//         　　　　　　ユーザーインターフェースの演出
//
/*===========================================================================*/
//
//                                                          Author : R.Usui
/*---------------------------------------------------------------------------*/

/*!
	@file
	@brief    ゲームワールド内のオブジェクトにUIとしての演出を与えます
	@detail   Load,Init,Update,Unloadをそれぞれ規定の位置に実装したら、
	　　　　　該当ファイルに「 uiDisplay.h 」をインクルードして使用可能
		 　　 になります。
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
　@brief
  　プレイヤーの各アクションに対して演出を与える。

　@details
  　AttackFromHeart...
    ハートからのアタック時に使用する。

	ReturnToOrigineAfterAttack...
	アタックがエネミーに当たって、かつその攻撃でHPが０
	になった際に使用する。
	引数：該当のエネミーのスプライト

	OneStickChangeToOne...
	回転する１を消去するタイミングのうち、妖精を呼び出
	すときに使用する。
	引数：該当のハートインスタンス
*/
void UI_AttackFromHeart(void);
void UI_ReturnToOrigineAfterAttack(class Enemy* enemy);
void UI_OneStickChangetoOne(Heart* heart);
/*----------------------------------------------------**/

#endif /*_UI_DISPLAY_*/

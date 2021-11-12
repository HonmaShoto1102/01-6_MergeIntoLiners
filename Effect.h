/*---------------------------------------------------------------------------*/
//  FILE : Effect.h
//
//         　　　　　　  　　エフェクト効果の実装
//
/*===========================================================================*/
//
//                                                          Author : R.Usui
/*---------------------------------------------------------------------------*/
/*!
	@file
	@brief    ゲームワールド内のオブジェクトにエフェクト効果を付与します
	@detail   Load,Init,Update,Unloadをそれぞれ規定の位置に実装したら、
	　　　　　該当ファイルに「 Effect.h 」をインクルードして使用可能
		 　　 になります。
*/
#pragma once
#ifndef _EFFECT_
#define _EFFECT_

#include <vector>
#include <string>
#include "base_Sprite.h"

void Effect_Load(void);
void Effect_Init(void);
void Effect_Update(void);
void Effect_Unload(void);


/**----------------------------------------------------------------------
  @brief
    該当の箇所で各々の引数を指定して使用します
  @detail
    第１引数 ：該当の.pngファイルの名前部分を指定
	第２引数 ：描画するオブジェクトの左上座標(ラインのStartPos)
	第３引数 ：エフェクトのスケーリング値
   (第４引数)：ライン描画の角度
*/
void ActivateEffect(std::string effectName, float2D position, float2D scale);
void ActivateLineEffect(std::string effectName, float2D start, float2D scale, float angle);
/*--------------------------------------------------------------------**/

#endif /*_EFFECT_*/

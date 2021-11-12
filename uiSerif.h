#pragma once

/*!
	@file
	@brief    ゲームワールド内のオブジェクトにUIとしての演出を与えます
	@detales  Load,Init,Update,Unloadをそれぞれ規定の位置に実装したら、
	　　　　　該当ファイルに「 uiDisplay.h 」をインクルードして使用可能
		 　　 になります。引数の型はすべて"SpriteC"に統一します。
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
　@brief
	Vertica・Horizyのラインカーソルを表示する。
　@detail
  　引数に現在のプレイヤーの状態(Ground or Heart)を入れ
　　ると、それに応じた個数のカーソルを表示します。
-------------------------------------------------------**/
//void UI_CursorTowardsVertica(PLAYER_STATE player_state);
//void UI_CursorTowardsHorizy(PLAYER_STATE player_state);
/**----------------------------------------------------**/


/**------------------------------------------------------
　@brief
  　プレイヤーの各アクションに対してUI的演出を与える
　@detail
  　AttackFromHeart...
	ハートからのアタック時に使用する。
	ReturnToOrigineAfterAttack...
	アタックがエネミーに当たって、かつその攻撃でHPが０
	になった際に使用する。
-------------------------------------------------------**/
//void UI_AttackFromHeart(void);
//void UI_ReturnToOrigineAfterAttack(SpriteC* enemy);
/**----------------------------------------------------**/



/*--------------------  Private  ---------------------*/

// 

#endif // _UI_DISPLAY_

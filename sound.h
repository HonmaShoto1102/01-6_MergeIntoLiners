//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{		
	SL_BGM_LastBoss,	
	SL_BGM_Stage1,	
	SL_BGM_Stage2,
	SL_BGM_Stage3,
	SL_BGM_Title,
	SL_BGM_GameOver,
	SL_stage_clear,
	SL_booboo,
	SL_break_crystal,
	SL_enemy_laugh,
	SL_game_over,
	SL_hud_refresh_a,
	SL_hud_refresh_b,
	SL_line_drawn_up,
	SL_pinpon,
	SL_enemy_damaged,
	SL_enemy_dead,
	SL_heart_shiny,
	SL_magic_charge,
	SL_magic_discharge,
	SL_menu_cancel,
	SL_menu_move,
	SL_menu_start,
	SL_mirror_locked,
	SL_mirror_unlocked,
	SL_player_attack,
	SL_player_telepote,
	SL_player_to_heart,
	SL_player_trans,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

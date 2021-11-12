/*ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
イベントモジュール

制作者:佐藤陸玖
ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー*/

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

//ステージ１のアクション
void Event_Stage1(void);

//ステージ２のアクション
void Event_Stage2(void);

//ステージ３のアクション
void Event_Stage3(void);

//ステージ４のアクション
void Event_Stage4(void);
//会話イベント
void Event_TalkEvent(void);

namespace ne
{
	int EventNumber;//関数ポインタの何番目を実行するか指定するための変数
	int StageNumber;

	EventFunction ActionEvent[] =
	{
	   Event_Stage1,      //歩行のみのイベント
	   Event_Stage2, //ホライジー(横線)生成
	   Event_Stage3,//バティカ(縦線)生成
	   Event_Stage4,  //特異点生成
	};
}

void Event_Load(void)
{
	;//今のところはナシ
}

void Event_Init(void)
{
	ne::EventNumber = EVENTTYPE_NONE;
}

void Event_Update(void)
{
	ne::ActionEvent[ne::StageNumber % 4]();

	//デバッグ用
	if (keylogger_Trigger(KL_L))
	{
		Event_SetStageEvent(Event_GetEventNumber() + 1);
	}


}

void Event_Unload(void)
{
	;//今のところはナシ
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
	//本間の制作したテキストプログラムを挿入

	//if (keylogger_Release(KL_ENTER))
	//{
	//	//指定のキーを押したらセリフ更新
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
		DebugPrintf("STAGE_1はここでは無効です。使用しないでください\n");
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
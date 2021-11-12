/*ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
イベントモジュール

制作者:佐藤陸玖

・関数ポインタの何行目を実行するか決められる【EventNumber】は、初期値に-1が入っている。

・現段階では、Uキーを押したらイベントが切り替わり、
　Sキーを押したら初期値の-1が入る(※)仕様になっている

※イベントによっては使えないキーもある
ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー*/
#pragma once
#ifndef EVENT_H_
#define EVENT_H_

#define EVENT_INVALID_NUMBER (-1)

//イベント指定用
//本番ではこれを用いてイベント時の操作と通常の操作を切り替える
typedef enum EVENTTYPE_tag
{

	EVENTTYPE_NONE = EVENT_INVALID_NUMBER,//イベントを終了し、通常時の操作に切り替える
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

//イベントモジュールのロード
void Event_Load(void);

//イベントモジュールの初期化
void Event_Init(void);

//イベントモジュールの更新
void Event_Update(void);

//イベントモジュールの終了処理
void Event_Unload(void);

//ステージ1のイベント指定
void Event_SetStageEvent(int type);

//ステージ2～4のイベント指定
void Event_SetStageEvent(STAGE stage_num);

//現在行われているイベントの番号を返す
int Event_GetEventNumber(void);
#endif // !EVENT_H_


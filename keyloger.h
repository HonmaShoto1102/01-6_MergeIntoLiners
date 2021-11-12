#ifndef KEYLOGER_H
#define KEYLOGER_H

//キー入力の記録制御

//キーロガーキー列挙型
typedef enum KeyloggerKey_tag 
{
	KL_W,
	KL_S,
	KL_A,
	KL_D,
	KL_J,	
	//KL_DECISION = KL_ATTACK,
	//KL_SPACE,
	//KL_CANCEL = KL_SPECIAL,
	KL_K,
	KL_L,	
	KL_HOME,
	KL_PGUP,
	KL_PGDN,
	KL_END,
	KL_ENTER,
	KL_SPACE,
	KL_RIGHTSHIFT,
	KL_U,
	KL_MAX
}KeyloggerKey;
//キーロガーモジュールの初期化
void Keylogger_Initialize();
//キーロガーモジュールの終了処理
void Keylogger_Finalize();
//キーロガーモジュールの更新
void Keylogger_Update();



//キー入力状態の取得
//
//引数：
//
//戻り値：押されていたらtrue
//
bool keylogger_Press(KeyloggerKey kl);

//キー入力状態の取得(押した瞬間)
//
//引数：
//
//戻り値：押されていたらtrue
//
bool keylogger_Trigger(KeyloggerKey kl);

//キー入力状態の取得(離した瞬間)
//
//引数：
//
//戻り値：離した瞬間だったらtrue
//
bool keylogger_Release(KeyloggerKey kl);



void Keylogger_RecordStart(int frame_max);
void Keylogger_RecordEnd();
void Keylogger_RecordLoad();
void Keylogger_RecordPlay();
bool Keylogger_IsRecordPlay();

#endif // !KEYLOGER_H


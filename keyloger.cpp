#define _CRT_SECURE_NO_DEPRECATE

#include "keyloger.h"
#include"keyboard.h"


typedef unsigned short KeyloggerType;
static  unsigned int g_CurrentKeyState = 0;//そのフレームでのキーの状態保持用

static unsigned int g_PrevKeysState = 0;//前フレームでのキー状態保持用

static unsigned int g_TriggerKeyState = 0;//
static unsigned int g_ReleaseKeyState = 0;

static int g_KeyloggerMode = 0;//0 - 通常  1 - 記録 2 - 再生
static unsigned int* g_pRecordCurrentDate = NULL;
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;
static int g_RecordFrameMax = 0;


//キーロガーからキーボードキーへの変換表
static const Keyboard_Keys g_KKs[KL_MAX] = {
	KK_W,
	KK_S,
	KK_A,
	KK_D,
	KK_J,
	//KK_SPACE,
	//KK_N,
	KK_K,
	KK_L,
	KK_HOME,
	KK_PAGEUP,
	KK_PAGEDOWN,
	KK_END,
	KK_ENTER,
	KK_SPACE,
	KK_RIGHTSHIFT,
	KK_U,
};






void Keylogger_Initialize()
{
	g_CurrentKeyState = 0;
	g_PrevKeysState = 0;
	g_TriggerKeyState = 0;//
	g_ReleaseKeyState = 0;

    g_KeyloggerMode = 0;
	g_pRecordCurrentDate = NULL;
	g_RecordFrame = 0;
	g_RecordPlayFrame = 0;
	g_RecordFrameMax = 0;
}

void Keylogger_Finalize()
{
	if (g_pRecordCurrentDate) {
		free(g_pRecordCurrentDate);
		g_pRecordCurrentDate = NULL;
	}
}

void Keylogger_Update()
{
	//前フレームのキー状態を保存しておく
	/*g_PrevKeysState = g_CurrentKeyState;
	//キーロガーモードによって、動作変更
	g_CurrentKeyState = 0;

	//キーロガーキーの状態取得
	for (int i = 0; i < KL_MAX; i++) {
		if (Keyboard_IsKeyDown(g_KKs[i])) {
			g_CurrentKeyState |= 1u << i;  //       ビット演算     <<:ビット桁移動
		}
		//押した瞬間と離した瞬間のキーを取得
		g_TriggerKeyState = (g_PrevKeysState^g_CurrentKeyState)&g_CurrentKeyState;
		g_ReleaseKeyState = (g_PrevKeysState^g_CurrentKeyState)&g_PrevKeysState;
	}*/

	g_PrevKeysState = g_CurrentKeyState;

	if (g_KeyloggerMode <= 1) {
		g_CurrentKeyState = 0;
		for (int i = 0; i < KL_MAX; i++) {
			if (Keyboard_IsKeyDown(g_KKs[i])) {
				g_CurrentKeyState |= 1u << i;
			}
		}
		//キー記録モード
		if (g_KeyloggerMode == 1) {

			if(g_RecordFrame<g_RecordFrameMax)
			g_pRecordCurrentDate[g_RecordFrame++] = g_CurrentKeyState;
		}
	}
	else {
		//再生モード
		//安全処置（記録フレーム数より多く再生しようとした
		if (g_RecordPlayFrame >= g_RecordFrame) {
			//g_RecordPlayFrame = g_RecordFrame;
			g_CurrentKeyState = 0;
			g_KeyloggerMode = 0;
		}
		else
		{
			g_CurrentKeyState = g_pRecordCurrentDate[g_RecordPlayFrame++];
		}
		//g_CurrentKeyState = g_RecordPlayFrame < g_RecordFrame ? g_pRecordCurrentDate[g_RecordPlayFrame++] : 0;
	}

	g_TriggerKeyState = (g_PrevKeysState ^ g_CurrentKeyState) & g_CurrentKeyState;
	g_ReleaseKeyState = (g_PrevKeysState ^ g_CurrentKeyState) & g_PrevKeysState;


}

bool keylogger_Trigger(KeyloggerKey kl)
{
	return g_TriggerKeyState & (1u<<kl);
}

bool keylogger_Release(KeyloggerKey kl)
{
	return g_ReleaseKeyState & (1u<<kl);
}

void Keylogger_RecordStart(int frame_max)
{
	if (g_pRecordCurrentDate) {
		free(g_pRecordCurrentDate);
	}

	g_pRecordCurrentDate = (unsigned int*)malloc(sizeof(unsigned char)*frame_max);
	g_KeyloggerMode = 1;
	g_RecordFrame = 0;
	g_RecordFrameMax = frame_max;
}

void Keylogger_RecordEnd()
{
	FILE* fp = fopen("Keylogger.dat", "wb");
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	fwrite(g_pRecordCurrentDate, sizeof(unsigned char), g_RecordFrame, fp);
	fclose(fp);

	g_KeyloggerMode = 0;

	if (g_pRecordCurrentDate) {
		free(g_pRecordCurrentDate);
		g_pRecordCurrentDate = NULL;
	}
}

void Keylogger_RecordLoad()
{
	FILE* fp = fopen("Keylogger.dat", "rb");
	fread(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);

	if (g_pRecordCurrentDate)free(g_pRecordCurrentDate);
	g_pRecordCurrentDate = (unsigned int*)malloc(g_RecordFrame);
	if(g_pRecordCurrentDate)fread(g_pRecordCurrentDate, sizeof(unsigned char), g_RecordFrame, fp);
	fclose(fp);

	//g_KeyloggerMode = 0;
}

void Keylogger_RecordPlay()
{
	g_RecordPlayFrame = 0;
	g_KeyloggerMode = 2;
}

bool Keylogger_IsRecordPlay()
{
	if (g_KeyloggerMode == 2) {
		return true;
	}
	return false;
}

bool keylogger_Press(KeyloggerKey kl)
{
	return g_PrevKeysState & (1u << kl);

}

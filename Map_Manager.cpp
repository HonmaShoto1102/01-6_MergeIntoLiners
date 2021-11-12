#include "Map_Manager.h"
#include "base_Sprite.h"
#include "GM.h"
#include "Stage.h"
#include "tinyxml2.h"
#include "Event.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "SceneManager.h"


static SpriteC* testMap;
static SpriteC* stcSprite;
static float stcSize = 0.0f;
static int stageNumber = SET_START_STAGE;

static SOUND_LABEL bgmList[STAGEMAX]{
	SL_BGM_Stage1,
	SL_BGM_Stage1,
	SL_BGM_Stage2,
	SL_BGM_Stage2,
	SL_BGM_Stage2,
	SL_BGM_Stage3,
	SL_BGM_Stage3,
	SL_BGM_Stage3,
	//SL_BGM_Stage4,
};

static int stageNum[3]{
	0,2,5
};

enum stcSt
{
	S_expand,//拡大
	S_narrow,//縮小
	S_wexpand,
	S_wnarrow,
	S_defalut,
};
static stcSt stageType = S_narrow;
static stcSt nextStype = S_narrow;
static int clearCount = 0;
void sTchangeCheck();
//void enventCheck();

void MapManager_Load()
{
	
	//testMap = new SpriteC("Asset/testbg.jpg", 1);
	stcSprite = new SpriteC("Asset/white_heart.png",15);
	Stage_Load();
	
}

void MapManager_Init()
{
	//testMap->Init();
	stcSprite->Init();
	stcSprite->SetPosition(0, 0);
	stcSprite->SetScale(20.0f, 20.0f);
	stcSprite->SetColor(0, 0, 0);
	stcSprite->SetAnchorPoint(ANCHOR_CENTER);
	stcSprite->SetActive(true);
	stcSprite->SetPosition(GM_mainCamera()->GetPosX(), GM_mainCamera()->GetPosY());
	//Stage_Translation(stageNumber);
	Stage_Init();
	//testMap->SetMultiple(1.0f, 1.0f);
	//testMap->SetPosition(-1000.0f, -750.0f);
	//testMap->SetPosition(0.0f, 0.0f);
	//GM_mainCamera()->SetBoundary(-1000, -1000, 8000, 1330);
	//GM_mainCamera()->SetBoundary(0, 0, 2560, 1080);
	SoundManager_PlayBGM(bgmList[stageNumber]);
}

void MapManager_Update()
{
	if (stageType == S_expand) {
		stcSize += 0.2f;
		stcSprite->SetScale(stcSize, stcSize);
		if (stcSize >= 20.0f) {
			stcSize = 20.0f;
			Stage_Translation(stageNumber);
			nextStype = S_narrow;
		}
	}
	if (stageType == S_narrow) {
		stcSize -= 0.2f;
		stcSprite->SetScale(stcSize, stcSize);
		if (stcSize <= 0.0f) {
			stcSize = 0.0f;
			nextStype = S_defalut;
			if(stageNumber != 6)SoundManager_PlayBGM(bgmList[stageNumber]);
		}
		stcSprite->SetPosition(GM_mainCamera()->GetPosX(), GM_mainCamera()->GetPosY());
	}

	if (stageType == S_wexpand) {
		stcSize += 0.2f;
		stcSprite->SetScale(stcSize, stcSize);
		if (stcSize > 20.0f) {
			stcSize = 20.0f;
			nextStype = S_wnarrow;
			Stage_Translation(stageNumber);
			SM_SceneChange(EClear);
		}
	}

	if (stageType == S_wnarrow) {
		stcSize -= 0.2f;
		stcSprite->SetScale(stcSize, stcSize);
		if (stcSize <= 0.0f) {
			stcSize = 0.0f;
			nextStype = S_defalut;
			SoundManager_PlayBGM(bgmList[stageNumber]);
		}
		stcSprite->SetPosition(GM_mainCamera()->GetPosX(), GM_mainCamera()->GetPosY());
	}
	

	Stage_Update();
	sTchangeCheck();
}

void MapManager_Final()
{
	
	SoundManager_StopBGM();
	Stage_Final();
	delete stcSprite;
	stcSprite = NULL;
}

void MapManager_StageTrans(int num)
{
	SoundManager_StopBGM();
	stageNumber = num;
	stcSprite->SetActive(true);
	stcSprite->SetColor(0, 0, 0);
	//stcSprite->SetPosition(GM_mainCamera()->GetPosX(), GM_mainCamera()->GetPosY());
	nextStype = S_expand;
}

void MapManager_StageClear()
{
	//clearCount++;
	SoundManager_StopBGM();
	stageNumber++;
	if (stageNumber >= 9) {

		stageNumber = 0;
	}
	//stageNumber = stageNum[clearCount];
	stcSprite->SetActive(true);
	stcSprite->SetColor(255, 255, 255);
	nextStype = S_wexpand;
}

int MapManager_GetTransHeart()
{
	return stageType;
}

int MapManager_GetStangeNumber()
{
	return stageNumber;
}

void sTchangeCheck() {
	if (stageType == nextStype)return;
	stcSprite->SetActive(false);
	stageType = nextStype;
	switch (stageType)
	{
	case S_expand:
		stcSprite->SetActive(true);
		break;
	case S_narrow:
		stcSprite->SetActive(true);
		break;
	case S_defalut:
		stcSprite->SetActive(false);
		break;
	case S_wexpand:
		stcSprite->SetActive(true);
		break;
	case S_wnarrow:
		stcSprite->SetActive(true);
		break;
	default:
		break;
	}
	stcSprite->SetPosition(GM_mainCamera()->GetPosX(), GM_mainCamera()->GetPosY());
}

//void EventBoxCheck() {
//
//	int evCount = Stage_GetNumberOfBlock(bl_eventBox);
//	for (int i = 0; i < evCount; i++)
//	{
//		M_eventBox* ev = Stage_GetEventBox_byNumber(i);
//		//カメラとか、プレイヤーとかを当たり判定
//		if (ev->GetTrigger() == false) {//触発してないeventを判断
//			EVENTTYPE eventNumber = (EVENTTYPE)ev->GetEventKey();//event番目を取得
//			Event_SetStageEvent(eventNumber);
//			ev->OnTrigger();
//		}
//	}
//
//
//
//
//	SetCamera_Foucs(cf_event1);
//	if (GetCamera_Foucs() == cf_event1) {
//		GM_mainCamera()->SetPos(x, y);
//		GM_mainCamera()->SetFocusLens(1.5f);
//	}
//
//	//eventが完了、デフォルトevent（通常状態）に戻るとき,
//	SetCamera_Foucs(cf_player);
//	GM_mainCamera()->SetFocusLens(1.0f);
//}
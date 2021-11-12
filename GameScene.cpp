#include "GameScene.h"
#include "base_Sprite.h"
#include "GM.h"
#include "keyloger.h"
#include "playerAction.h"
#include "playerCollision.h"
#include "PlayerData.h"
#include "uiDisplay.h"
#include "Map_Manager.h"
#include "SoundManager.h"
#include "FairyVH.h"
#include "Line.h"
#include "Figure.h"
#include "Effect.h"
#include "uiSerif.h"
#include "loadingScene.h"
#include "Enemy.h"
#include "Stage.h"
#include "playerEffect.h"


static int timeCount = 0;   
static int SceneNumber = 0;   //シーン番号
static float2D CameraOffpos = { 0,0 };
static float CameraMoveSpeed = 4.0f;
static int timeDeley = 1;


void Game::Load()
{
	LoadingTexture_Active(true);
	MapManager_Load();
	LoadEnemy();
	Line_Load();
	PlayerData_Load();
	PlayerAction_Load();
	PlayerCollision_Load();
	PlayerEffect_Load();
	UI_Load();
	FairyVH_Load();
	Figure_Load();
	Effect_Load();
	//UiSerif_Load();
	
}

void Game::Init()
{
	GM_mainCamera()->SetPos(0, 0);	
	GM_mainCamera()->SetLensDistance(1.4f);
	GM_mainCamera()->SetLensDistanceMax(1.5f);
	GM_mainCamera()->SetLensOff(0.008f);
	MapManager_Init();
	InitEnemy();
	Line_Init();
	PlayerData_Init();
	PlayerAction_Init();
	PlayerCollision_Init();
	PlayerEffect_Init();
	UI_Init();
	FairyVH_Init();
	Figure_Init();
	Effect_Init();
	//UiSerif_Init();
	LoadingTexture_Active(false);
	//SoundManager_PlayBGM(SL_BGM_Stage1);
}

void Game::Update()
{
	if (keylogger_Press(KL_HOME)) {
		/*CameraOffpos.x -= CameraMoveSpeed;
		GM_mainCamera()->SetPos(CameraOffpos.x, CameraOffpos.y);*/
		GM_mainCamera()->SetZoom(0.01f);
	}
	if (keylogger_Press(KL_END)) {
		/*CameraOffpos.x += CameraMoveSpeed;
		GM_mainCamera()->SetPos(CameraOffpos.x, CameraOffpos.y);*/
		GM_mainCamera()->SetZoom(-0.01f);
	}
	if (keylogger_Press(KL_PGUP)) {
		CameraOffpos.y -= CameraMoveSpeed;
		GM_mainCamera()->SetPos(CameraOffpos.x, CameraOffpos.y);
	}
	if (keylogger_Press(KL_PGDN)) {
		CameraOffpos.y += CameraMoveSpeed;
		GM_mainCamera()->SetPos(CameraOffpos.x, CameraOffpos.y);
	}
	if (keylogger_Trigger(KL_J)) {
		//Line_CreateLineH(300.0f, 600.0f, 900.0f, 900.0f);
	}
	if (keylogger_Trigger(KL_K)) {
		//Line_DeleteLineH();
	}
	MapManager_Update();
	UpdateEnemy();
	Line_Update();
	timeDeley = Player_GetBulletTime();
	PlayerData_Update();
	PlayerAction_Update();
	PlayerEffect_Update();
	if(MapManager_GetTransHeart()==4)PlayerCollision_Update();
	UI_Update();
	FairyVH_Update();
	Figure_Update();
	Effect_Update();
	
	timeCount++;
}

void Game::Final()
{
	
	MapManager_Final();
	UnloadEnemy();
	Line_Final();
	PlayerEffect_Final();
	PlayerData_Final();
	PlayerAction_Final();
	PlayerCollision_Final();
	UI_Unload();
	FairyVH_Final();
	Figure_Final();
	Effect_Unload();
	//UiSerif_Unload();
}

void Game::Draw()
{
	//UiSerif_Update();
}


void Game::LoadEnemy()
{
	int enemyBoxNum = Stage_GetNumberOfBlock(bl_enemyBox);
	for (int i = 0; i < enemyBoxNum; i++)
	{
		float enemyPosX = Stage_enemyBox_byNumber(i)->GetPosX();
		float enemyPosY = Stage_enemyBox_byNumber(i)->GetPosY();
		const char* enemyName = Stage_enemyBox_byNumber(i)->GetName();
		const char* dirTypeName = Stage_enemyBox_byNumber(i)->GetDirTypeName();
		if (strcmp(enemyName, "coronbot") == 0)
		{
			Enemy* coronbot = new Coronbot(this, enemyPosX, enemyPosY, dirTypeName);
			continue;
		}
		if (strcmp(enemyName, "digbot") == 0)
		{
			Enemy* digbot = new Digbot(this, enemyPosX, enemyPosY, dirTypeName);
			continue;
		}
		if (strcmp(enemyName, "garabot") == 0)
		{
			Enemy* garabot = new Garabot(this, enemyPosX, enemyPosY, dirTypeName);
			continue;
		}
		if (strcmp(enemyName, "wingy") == 0)
		{
			Enemy* wingy = new Wingy(this, enemyPosX, enemyPosY, dirTypeName);
			continue;
		}
		if (strcmp(enemyName, "liney") == 0)
		{
			Enemy* liney = new Liney(this, enemyPosX, enemyPosY, dirTypeName);
			continue;
		}
		if (strcmp(enemyName, "ghost") == 0)
		{
			Enemy* ghost = new Ghost(this, enemyPosX, enemyPosY, dirTypeName);
			continue;
		}
	}

	int en2Count = Stage_GetNumberOfBlock(bl_enemy2Box);
	for (int i = 0; i < en2Count; i++)
	{
		float enemyPosX = Stage_GetEnemy2Box_byNumber(i)->GetPosX();
		float enemyPosY = Stage_GetEnemy2Box_byNumber(i)->GetPosY();
		const char* name = Stage_GetEnemy2Box_byNumber(i)->GetName();
		const char* dirName = Stage_GetEnemy2Box_byNumber(i)->GetDirTypeName();
		int hiddenBoxID = Stage_GetEnemy2Box_byNumber(i)->GetHeartBoxID();

		if (strcmp(name, "coronbot") == 0)
		{
			Enemy* coronbot2 = new Coronbot(this, enemyPosX, enemyPosY, dirName, hiddenBoxID);
			continue;
		}
		if (strcmp(name, "digbot") == 0)
		{
			Enemy* digbot2 = new Digbot(this, enemyPosX, enemyPosY, dirName, hiddenBoxID);
			continue;
		}
		if (strcmp(name, "garabot") == 0)
		{
			Enemy* garabot2 = new Garabot(this, enemyPosX, enemyPosY, dirName, hiddenBoxID);
			continue;
		}
		if (strcmp(name, "wingy") == 0)
		{
			Enemy* wingy2 = new Wingy(this, enemyPosX, enemyPosY, dirName, hiddenBoxID);
			continue;
		}
		if (strcmp(name, "liney") == 0)
		{
			Enemy* liney2 = new Liney(this, enemyPosX, enemyPosY, dirName, hiddenBoxID);
			continue;
		}
		if (strcmp(name, "ghost") == 0)
		{
			Enemy* ghost2 = new Ghost(this, enemyPosX, enemyPosY, dirName, hiddenBoxID);
			continue;
		}
		if (strcmp(name, "Acies") == 0)
		{
			Enemy* acies = new Acies(this, enemyPosX, enemyPosY, dirName, hiddenBoxID);
			continue;
		}
	}
}

void Game::InitEnemy()
{
	for (auto enemy : mEnemies)
	{
		enemy->Init();
	}
}

void Game::UpdateEnemy()
{
	// 各pendingがカメラの矩形範囲に入ったかどうかを確認する
	float cameraRightX = GM_mainCamera()->GetOffsetPosX() +
		GM_mainCamera()->GetCameraWindowRectangle().w;
	float cameraLeftX = GM_mainCamera()->GetOffsetPosX();
	float cameraTopY = GM_mainCamera()->GetOffsetPosY();
	float cameraBottomY = GM_mainCamera()->GetOffsetPosY() +
		GM_mainCamera()->GetCameraWindowRectangle().h;
	// カメラの視界に入ったエネミーから順に更新をかけていく
	for (auto enemy : mEnemies)
	{
		if (!enemy->GetUpdateRequest())
		{
			Vector2 initPos = enemy->GetInitialPosition();
			if ((cameraRightX >= initPos.x &&
				(initPos.y >= cameraTopY && initPos.y <= cameraBottomY)) ||
				(cameraLeftX >= initPos.x &&
					(initPos.y >= cameraTopY && initPos.y <= cameraBottomY)))
			{
				enemy->SetUpdateRequest(true);
				enemy->SetInitialAIState(true);
			}
		}
		if (enemy->GetUpdateRequest())
		{
			enemy->Update();
		}
	}

	// EDeadステートのエネミーを一時配列deadEnemiesに追加
	std::vector<Enemy*> deadEnemies;
	for (auto actor : mEnemies)
	{
		if (actor->GetState() == Enemy::EDead)
		{
			deadEnemies.emplace_back(actor);
		}
	}

	// deadEnemies内のすべての要素を削除
	for (auto actor : deadEnemies)
	{
		delete actor;
	}
}

void Game::UnloadEnemy()
{
	while (!mEnemies.empty())
	{
		delete mEnemies.back();
	}
}

void Game::AddEnemy(Enemy* enemy)
{
	mEnemies.emplace_back(enemy);
}

void Game::RemoveEnemy(Enemy* enemy)
{
	auto iter = std::find(mEnemies.begin(), mEnemies.end(), enemy);
	if (iter != mEnemies.end())
	{
		std::iter_swap(iter, mEnemies.end() - 1);
		mEnemies.pop_back();
	}
}



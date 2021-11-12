#include "SceneManager.h"
#include "texture.h"

                                          
#include "TitleScene.h"   
#include "FailureScene.h"
#include "ClearScene.h"
#include "InputManager.h"

static Title TitleScene;
static Game GameScene;
static GameOver FailureScene;
static Clear ClearScene;

static int Now_SceneNumber = SET_START_SCENE;
static int Next_SceneNumber = SET_START_SCENE;

void NextSceneCheck();

void SM_Load() {
	switch (Now_SceneNumber)
	{
	case EGame:
		GameScene.Load();
		break;
	case ETitle:
		TitleScene.Load();
		break;
	case EFailure:
		FailureScene.Load();
		break;
	case EClear:
		ClearScene.Load();
		break;
	default:
		break;
	}

	if (Texture_Load() > 0) {
		MessageBox(NULL, "テクスチャの読み込みに失敗した", "error", MB_OK);
	}
}

void SM_Init()
{
	switch (Now_SceneNumber)
	{
	case EGame:
		GameScene.Init();
		break;
	case ETitle:
		TitleScene.Init();
		break;
	case EFailure:
		FailureScene.Init();
		break;
	case EClear:
		ClearScene.Init();
		break;
	default:
		break;
	}
}

void SM_Final()
{
	switch (Now_SceneNumber)
	{
	case EGame:
		GameScene.Final();
		break;
	case ETitle:
		TitleScene.Unload();
		break;
	case EFailure:
		FailureScene.Unload();
		break;
	case EClear:
		ClearScene.Unload();
		break;
	default:
		break;
	}
}

void SM_Update()
{
	switch (Now_SceneNumber)
	{
	case EGame:
		GameScene.Update();
		break;
	case ETitle:
		TitleScene.Update();
		break;
	case EFailure:
		FailureScene.Update();
		break;
	case EClear:
		ClearScene.Update();
		break;
	default:
		break;
	}
	NextSceneCheck();
}

void SM_Draw()
{
	switch (Now_SceneNumber)
	{
	case EGame:
		GameScene.Draw();
		break;
	default:
		break;
	}
}

void NextSceneCheck() {

	if (Now_SceneNumber == Next_SceneNumber)return;
	SM_Final();
	Now_SceneNumber = Next_SceneNumber;
	SM_Load();
	SM_Init();
}

void SM_SceneChange(int nextScene)
{
	Next_SceneNumber = nextScene;
	
}

class Game* GetGameScene()
{
	return &GameScene;
}

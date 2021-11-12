#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include "GameScene.h" 
enum EScene
{
	EGame = 0,
	ETitle,
	EFailure,
	EClear,
};

void SM_Load();
void SM_Init();
void SM_Final();
void SM_Update();
void SM_Draw();

void SM_SceneChange(int nextScene);

class Game* GetGameScene();

#endif

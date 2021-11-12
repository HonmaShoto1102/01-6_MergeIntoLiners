#include "GM.h"
#include "SceneManager.h"


#define SPRITEMAX (2048)
#define ANIMATIONMAX (128)
#define MOVEANIMATION (128)
#define PARTICLEMAX (128)
#define ONE_LAYER_SPRITEMAX (SPRITEMAX/16)

static CameraC* mainCamera;
static SpriteC* spriteList[SPRITEMAX];
static ParticleC* paticaleList[16][PARTICLEMAX];
static AnimationC* animationList[ANIMATIONMAX];
static AnimationMove* moveAnimationList[MOVEANIMATION];

void GM_Init()
{
	for (int i = 0; i < SPRITEMAX; i++)
	{
		spriteList[i] = NULL;
	}

	for (int i = 0; i < PARTICLEMAX; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			paticaleList[j][i] = NULL;
		}
	}

	for (int i = 0; i < ANIMATIONMAX; i++)
	{
		animationList[i] = 0;
	}

	for (int i = 0; i < MOVEANIMATION; i++)
	{
		moveAnimationList[i] = 0;
	}

	mainCamera = new CameraC(SCREEN_WIDTH, SCREEN_HEIGHT);
	mainCamera->Init();

	SM_Load();
	SM_Init();
}

void GM_Final()
{
	SM_Final();

	delete mainCamera;
	mainCamera = nullptr;
	
}

void GM_Update()
{
	for (int i = 0; i < ANIMATIONMAX; i++)
	{
		if (animationList[i] == 0)continue;
		if (animationList[i]->GetPlayF()) {
			animationList[i]->Update();
		}
	}

	for (int i = 0; i < MOVEANIMATION; i++)
	{
		if (moveAnimationList[i] == 0)continue;
		if (moveAnimationList[i]->GetPlayF()) {
			moveAnimationList[i]->Update();
		}
	}
	SM_Update();
	mainCamera->Update();
}


void GM_Draw()
{
	SM_Draw();
}

int GM_AddParticle(ParticleC * pParticle)
{

	for (int i = 0; i < PARTICLEMAX; i++)
	{
		if (paticaleList[pParticle->GetLayer()][i] == 0) {
			paticaleList[pParticle->GetLayer()][i] = pParticle;
			return i;
		}
	}
	return 0;
}

int GM_UnAddParticle(int pID,int layer)
{
	int Curf = 0;
	for (int i = 0; i < PARTICLEMAX; i++)
	{
		if (paticaleList[layer][i] != 0 && paticaleList[layer][pID]->GetArrayID() == paticaleList[layer][i]->GetArrayID()) {
			Curf = 1;
		}
	}
	if (paticaleList[layer][pID] != 0) {
		paticaleList[layer][pID] = 0;
	}
	return Curf;
}

int GM_AddSprite(SpriteC * pSprite)
{
	
	for (int i = ONE_LAYER_SPRITEMAX * pSprite->GetLayer(); i < ONE_LAYER_SPRITEMAX * (pSprite->GetLayer()+1); i++)
	{
		if (spriteList[i] == 0) {
			spriteList[i] = pSprite;
			return i;
		}
	}
	return 0;
}

int GM_UnAddSprite(int aID)
{
	int Curf = 0;
	for (int i = 0; i < SPRITEMAX; i++)
	{
		if (spriteList[i]!=0&&spriteList[aID]->GetID() == spriteList[i]->GetID()) {
			Curf = 1;
		}
	}
	if (spriteList[aID] != 0) {
		spriteList[aID] = 0;
	}
	return Curf;
}

int GM_AddAnimation(AnimationC * pAni)
{
	for (int i = 0; i < ANIMATIONMAX; i++)
	{
		if (animationList[i] == 0) {
			animationList[i] = pAni;
			return i;
		}
	}
	return 0;
}

int GM_UnAddAnimation(int aniID)
{
	
	if (animationList[aniID] != 0) {
		animationList[aniID] = NULL;
		return 0;
	}	
	return 0;
}

int GM_AddMoveAni(AnimationMove * mAni)
{
	for (int i = 0; i < MOVEANIMATION; i++)
	{
		if (moveAnimationList[i] == 0) {
			moveAnimationList[i] = mAni;
			return i;
		}
	}
	return 0;
}

int GM_UnAddMoveAni(int aniID)
{
	for (int i = 0; i < MOVEANIMATION; i++)
	{
		if (moveAnimationList[i] != 0) {
			moveAnimationList[i] = 0;
			return i;
		}
	}
	return 0;
}

CameraC * GM_mainCamera()
{
	return mainCamera;
}



void GM_DrawLayer()
{
	for (int i = 0; i < SPRITEMAX; i++)
	{
		if (i%ONE_LAYER_SPRITEMAX == 0) {
			if (paticaleList[i / ONE_LAYER_SPRITEMAX][0] != 0) {
				for (int j = 0; j < PARTICLEMAX; j++)
				{
					if (paticaleList[i / ONE_LAYER_SPRITEMAX][j] == 0)continue;
					if (paticaleList[i / ONE_LAYER_SPRITEMAX][j]->GetActive()) {
						paticaleList[i / ONE_LAYER_SPRITEMAX][j]->Draw(mainCamera);
					}
				}
			}
		}

		if (spriteList[i] == 0)continue;
		if (spriteList[i]->GetActive()) {
			spriteList[i]->Draw(mainCamera);
		}
		
	}
}

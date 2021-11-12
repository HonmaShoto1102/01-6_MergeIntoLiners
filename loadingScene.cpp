#include "loadingScene.h"
#include "texture.h"
#include "sprite.h"
#include "config.h"

static int loadingTex;
static int loadingTex2;
static float GoValue;
static float rectX;
static float rectY;
static float rectW;
static float rectH;
static bool endflag;

static float rectX2;
static float rectY2;
static float rectW2;
static float rectH2;
static int aniCount;

void LoadingScene_Init()
{
	LoadingTexture_Init();
	//int bb = LoadingTexture_SetTextureLoadFile("Asset/pure_heart.png");
	loadingTex = LoadingTexture_SetTextureLoadFile("Asset/horizy_line.png");
	loadingTex2 = LoadingTexture_SetTextureLoadFile("Asset/playerAni/player_run_right.png");
	LoadTexture_Load();
	GoValue = 0;
	rectX = 100;
	rectY = SCREEN_HEIGHT - 200;
	rectW = SCREEN_WIDTH - 200;
	rectH = 30;
	endflag = false;

	rectX2 = 100 - 48;
	rectY2 = rectY - 96;
	rectW2 = 96;
	rectH2 = 96;

	aniCount = 0;
}

void LoadingScene_Final()
{
	LoadingTexture_AllRelease();
}

void LoadingScene_Draw()
{
	SpriteDrawLoadTexture(loadingTex, rectX, rectY, rectW * GoValue, rectH, 0, 0, 1000, 1000, 1000, 1000, 0, { 1,1 }, 
		D3DCOLOR_RGBA(255, 255, 255, 255), ANCHOR_LU);

	SpriteDrawLoadTexture(loadingTex2, rectX2 + rectW*GoValue, rectY2, rectW2, rectH2, 256 * (aniCount % 6), 256 * (aniCount / 6), 256.0f, 256.0f, 1536.0f, 1536.0f, 0.0f, { 1.0f,1.0f },
		D3DCOLOR_RGBA(255, 255, 255, 255), ANCHOR_LU);
	aniCount++;
	if (aniCount >= 12)aniCount = 0;
}
void LoadingScene_SetValue(float value)
{
	GoValue = value;
	if (GoValue > 0.9f)endflag = true;
}

bool LoadingScene_Getflag()
{
	return endflag;
}

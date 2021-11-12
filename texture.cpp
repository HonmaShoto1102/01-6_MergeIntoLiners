#include "texture.h"
#include<d3dx9.h>
#include<string.h>
#include"myDirect3D.h"
#include"debugPrintf.h"
//#include "sprite.h"
#include "loadingScene.h"
#include "Main.h"

#define TEXTURE_MAX (1024)
#define LTEXTURE_MAX (32)

//テクスチャ管理テーブル構造体
typedef struct Texture_tag {
	//int textureId;
	LPDIRECT3DTEXTURE9 pTexture;
	unsigned long width;
	unsigned long height;
	char filename[TEXTURE_FILENAME_MAX];
}Texture;

//テクスチャ管理テーブル
static Texture g_Textures[TEXTURE_MAX];

static Texture loadingTextures[LTEXTURE_MAX];
static int TextureCount = 0;
static bool LoadTextureActive = false;
static int LoadTextureGoValue = 1;

void Texture_Initialize(void)
{
	for (int i = 0; i < TEXTURE_MAX; i++) {
		g_Textures[i].pTexture = NULL;
		//g_Textures[i].textureId = INVALID_TEXTURE_ID;
		g_Textures[i].width = 0;
		g_Textures[i].height = 0;
		g_Textures[i].filename[0] = 0;
	}
}

void Texture_Finalize(void)
{
	Texture_AllRelease();
}

int Texture_SetTextureLoadFile(const char * pFileName)
{
	for (int i = 0; i < TEXTURE_MAX; i++) {

		//テーブルの空き状態
		if (g_Textures[i].filename[0] == 0) {
			continue;
		}
		//すでに指定のファイルが予約されているか
		if (strcmp(pFileName, g_Textures[i].filename) == 0) {
			//予約されている

			return i;
		}
	}
	
	//新規予約
	for (int i = 0; i < TEXTURE_MAX; i++) {
		
		//テーブルが使用中だったらスキップ
		if (g_Textures[i].filename[0] != 0) {
			
			continue;
			
		}
		strcpy_s(g_Textures[i].filename, pFileName);
		TextureCount++;
		return i;

	}
	
	return 0;
}

int Texture_Load(void)
{
	int error_count = 0;
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {

	}

	int loadTextureCurrentNumber = 0;
	if (LoadTextureActive) {
		//LoadingTexture_Init();
		LoadingScene_Init();
	}
	for (int i = 0; i < TEXTURE_MAX; i++) {

		//テーブルが使用中だったらスキップ
		if (g_Textures[i].filename[0] == 0) {

			continue;

		}
		if (g_Textures[i].pTexture != NULL) {
			//すでに読み込まている
			continue;
		}
		//テクスチャの読み込み
		HRESULT hr = D3DXCreateTextureFromFile(pDevice, g_Textures[i].filename, &g_Textures[i].pTexture);
		if (FAILED(hr)) {
			DebugPrintf("読み込めなかったテクスチャファイル： %s\n", g_Textures[i].filename);
			error_count++;
		}
		else
		{
			//テクスチャの解像度（幅、高さ）の調査
			D3DXIMAGE_INFO info;
			D3DXGetImageInfoFromFile(g_Textures[i].filename, &info);
			g_Textures[i].width = info.Width;
			g_Textures[i].height = info.Height;

			if (LoadTextureActive) {
				loadTextureCurrentNumber++;
				if (loadTextureCurrentNumber%LoadTextureGoValue == 0||loadTextureCurrentNumber == TextureCount) {
										
					LoadingScene_SetValue((float)loadTextureCurrentNumber / TextureCount);
					LoadingSceneUpdate();
					//描画バッチ命令の終了					
				}
			}
			
		}
	}
	if (LoadTextureActive) {
		LoadingScene_Final();
	}
	return error_count;
}

void Texture_Release(int textureIds[], int count)
{
	
	for (int i = 0; i < count; i++) {

		if (g_Textures[textureIds[i]].pTexture) {
			g_Textures[textureIds[i]].pTexture->Release();
			g_Textures[textureIds[i]].pTexture = NULL;
			TextureCount--;
		}
		g_Textures[textureIds[i]].filename[0] = 0;
		g_Textures[textureIds[i]].width = 0;
		g_Textures[textureIds[i]].height = 0;
	}
}

void Texture_AllRelease(void)
{
	for (int i = 0; i < TEXTURE_MAX; i++) {

		if (g_Textures[i].pTexture) {
			g_Textures[i].pTexture->Release();
			g_Textures[i].pTexture = NULL;
			TextureCount--;
		}
		g_Textures[i].filename[0] = 0;
		g_Textures[i].width = 0;
		g_Textures[i].height = 0;
	}
}

unsigned long Texture_GetTextureWidth(int textureId)
{
	return g_Textures[textureId].width;
}

unsigned long Texture_GetTextureHeight(int textureId)
{
	return g_Textures[textureId].height;
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureId)
{
	
	return g_Textures[textureId].pTexture;
}

//********************************LoadingTexture*************************************

void LoadingTexture_Init()
{
	for (int i = 0; i < LTEXTURE_MAX; i++) {
		loadingTextures[i].pTexture = NULL;
		//g_Textures[i].textureId = INVALID_TEXTURE_ID;
		loadingTextures[i].width = 0;
		loadingTextures[i].height = 0;
		loadingTextures[i].filename[0] = 0;
	}
}

void LoadingTexture_Final()
{
	LoadingTexture_AllRelease();
}

void LoadingTexture_Active(bool active)
{
	LoadTextureActive = active;
}

void LoadingTexture_SetGoValue(int value)
{
}

int LoadingTexture_SetTextureLoadFile(const char * pFileName)
{
	for (int i = 0; i < LTEXTURE_MAX; i++) {

		//テーブルの空き状態
		if (loadingTextures[i].filename[0] == 0) {
			continue;
		}
		//すでに指定のファイルが予約されているか
		if (strcmp(pFileName, loadingTextures[i].filename) == 0) {
			//予約されている

			return i;
		}
	}

	//新規予約
	for (int i = 0; i < LTEXTURE_MAX; i++) {

		//テーブルが使用中だったらスキップ
		if (loadingTextures[i].filename[0] != 0) {

			continue;

		}
		strcpy_s(loadingTextures[i].filename, pFileName);
		return i;

	}

	return 0;
}

int LoadTexture_Load(void)
{
	int error_count = 0;
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {

	}
	
	for (int i = 0; i < LTEXTURE_MAX; i++) {

		//テーブルが使用中だったらスキップ
		if (loadingTextures[i].filename[0] == 0) {

			continue;

		}
		if (loadingTextures[i].pTexture != NULL) {
			//すでに読み込まている
			continue;
		}
		//テクスチャの読み込み
		HRESULT hr = D3DXCreateTextureFromFile(pDevice, loadingTextures[i].filename, &loadingTextures[i].pTexture);
		if (FAILED(hr)) {
			DebugPrintf("読み込めなかったテクスチャファイル： %s\n", loadingTextures[i].filename);
			error_count++;
		}
		else
		{
			//テクスチャの解像度（幅、高さ）の調査
			D3DXIMAGE_INFO info;
			D3DXGetImageInfoFromFile(loadingTextures[i].filename, &info);
			loadingTextures[i].width = info.Width;
			loadingTextures[i].height = info.Height;

		}
	}
	return error_count;
}

void LoadingTexture_AllRelease()
{
	for (int i = 0; i < LTEXTURE_MAX; i++) {

		if (loadingTextures[i].pTexture) {
			loadingTextures[i].pTexture->Release();
			loadingTextures[i].pTexture = NULL;
			//TextureCount--;
		}
		loadingTextures[i].filename[0] = 0;
		loadingTextures[i].width = 0;
		loadingTextures[i].height = 0;
	}
}

void LoadingTexture_Release(int textureIds[], int count)
{
	for (int i = 0; i < count; i++) {

		if (loadingTextures[i].pTexture) {
			loadingTextures[i].pTexture->Release();
			loadingTextures[i].pTexture = NULL;
			//TextureCount--;
		}
		loadingTextures[i].filename[0] = 0;
		loadingTextures[i].width = 0;
		loadingTextures[i].height = 0;
	}
}

LPDIRECT3DTEXTURE9 LoadTexture_GetTexture(int textureId)
{
	return loadingTextures[textureId].pTexture;
}

void LoadingTexture_SetZeroCount()
{
	TextureCount = 0;
}

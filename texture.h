#ifndef TEXTURE_H
#define TEXTURE_H
#include <d3d9.h>
#define TEXTURE_FILENAME_MAX (64) //テクスチャファイル名最大文字数
#define INVALID_TEXTURE_ID (-1)   //無効なテクスチャ管理番号

void Texture_Initialize(void);
void Texture_Finalize(void);

//テクスチャファイルの読み込み予約
int Texture_SetTextureLoadFile(const char* pFileName);

//テクスチャの読み込み
//戻り値　読み込めなかったファイル数
int Texture_Load(void);


//テクスチャの部分解放
//引数：textureIds[] ... 解放したいtextureIdが入ったint型配列の先頭アドレス
//count     解放するテクスチャの数.
void Texture_Release(int textureIds[], int count);

//テクスチャの全解放
void Texture_AllRelease(void);

unsigned long Texture_GetTextureWidth(int textureId);
unsigned long Texture_GetTextureHeight(int textureId);
LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureId);

//*************************************loading画面表示**********************************
void LoadingTexture_Init();
void LoadingTexture_Final();
void LoadingTexture_Active(bool active);
void LoadingTexture_SetGoValue(int value);
int LoadingTexture_SetTextureLoadFile(const char* pFileName);
int LoadTexture_Load(void);
void LoadingTexture_AllRelease();
void LoadingTexture_Release(int textureIds[], int count);
LPDIRECT3DTEXTURE9 LoadTexture_GetTexture(int textureId);
void LoadingTexture_SetZeroCount();

#endif // !TEXTURE_H

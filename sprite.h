#ifndef SPRITE_H
#define SPRITE_H
#include<d3dx9.h>

enum ANCHORPOINT
{
	ANCHOR_LU,
	ANCHOR_LD,
	ANCHOR_RU,
	ANCHOR_RD,
	ANCHOR_CENTER,
	ANCHOR_LC,
	ANCHOR_RC,
	ANCHOR_TC,
	ANCHOR_BC,
};

typedef struct int2Dst {
	int x;
	int y;
}int2D;

typedef struct float2Dst {
	float x;
	float y;
}float2D;

typedef struct int4Dst {
	int x;
	int y;
	int z;
	int a;
}int4D;

typedef struct Vertex2D_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 TexCoord;
}Vertex2D;

//typedef struct INT2D {
//	int x;
//	int y;
//};



bool Spirte_Initialize(void);

void Sprite_Finalaize(void);

void Sprite_Draw(int textureId, float dx, float dy);

int SpriteParticle_CreatBuffer(int Count);
void SpriteParticle_Draw(int textureId, Vertex2D* v, int partId);
void SpriteParticle_Release(int partId);

//スプライトポリゴンカラー設定
//void Sprite_SetColor(D3DCOLOR color);


//テクスチャの描画
//テクスチャ切り取りサイズのポリゴンで指定座標にびょうが
//
//引数：textureId... テクスチャ管理番号
//      dx       ... 描画座標ｘ
//      dy       ... 描画座標ｙ
//      tcx      ... テクスチャの切り取り座標ｘ
//      tcy      ... テクスチャの切り取り座標ｙ
//      tcw      ... テクスチャの切り取り幅
//　　　tch      ... テクスチャの切り取り高さ
void SpriteDraw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, int tw, int th, float angle,float2D scale, int alpha);

void SpriteDraw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, int tw, int th, float angle);

void SpriteDrawBuffer(int textureId, float dx, float dy, float dw, float dh, float tcx, float tcy, float tcw, float tch, float tw, float th, float angle, float2D scale, D3DCOLOR color,ANCHORPOINT anPoint);

//void SpriteDraw(SP2D sp);
void SpritePolygonDraw(int textureId, Vertex2D* v,int Count);

void SpriteDrawLoadTexture(int textureId, float dx, float dy, float dw, float dh, float tcx, float tcy, float tcw, float tch, float tw, float th, float angle, float2D scale, D3DCOLOR color, ANCHORPOINT anPoint);

void SpriteDrawParatial(int textureId, float dx, float dy, float dw, float dh, float tcx, float tcy, float tcw, float tch, float tw, float th, float angle, float2D scale, D3DCOLOR color, ANCHORPOINT anPoint,
float uvX,float uvY,float uvW, float uvH );



#endif // !SPRITE_H


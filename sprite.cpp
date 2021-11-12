#include "sprite.h"

#include"myDirect3D.h"
#include"texture.h"

typedef struct PartData {
	LPDIRECT3DVERTEXBUFFER9 g_pVertexBuff;
	LPDIRECT3DINDEXBUFFER9 g_pIndexBuff;
	bool active;
	int polygonCount;
};



#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define PDATAMAX (256)

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;  //頂点バッファインターフェース
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static D3DCOLOR g_Color = 0xffffffff;  //ポリゴンカラー;
//static LPDIRECT3DTEXTURE9 g_pTexture = NULL;//テクスチャインターフェース
//static LPDIRECT3DTEXTURE9 g_pTexture2 = NULL;
static PartData partData[PDATAMAX];


bool Spirte_Initialize(void)
{

	for (int i = 0; i < PDATAMAX; i++)
	{
		partData[i].active = false;
		partData[i].polygonCount = 0;
	}

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice) {
		return false;
	}

	pDevice->CreateVertexBuffer(
		sizeof(Vertex2D) * 4,       //頂点バッファの量
		D3DUSAGE_WRITEONLY,   //使い方
		FVF_VERTEX2D,         //FVF
		D3DPOOL_MANAGED,      //メモリの管理方法
		&g_pVertexBuffer,     //取得したインターフェースのアドレスを記録するためのポインタへの
		NULL
		);

	pDevice->CreateIndexBuffer(
		sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndexBuffer,
		NULL
	);
	/*LRESULT hrT;
	hrT = D3DXCreateTextureFromFile(MyDirect3D_GetDevice(), "Tex/airou.png", &g_pTexture);
	LRESULT hrT2 = D3DXCreateTextureFromFile(MyDirect3D_GetDevice(), "Tex/xg.png", &g_pTexture2);

	

	if (FAILED(hrT)) {
		MessageBox(NULL, "テクスチャ読み込むに失敗した", "Errra", MB_OK);
		return false;
	}
	if (FAILED(hrT2)) {
		MessageBox(NULL, "テクスチャ読み込むに失敗した", "Errra", MB_OK);
		return false;
	}*/
	//FVFの設定をする
	MyDirect3D_GetDevice()->SetFVF(FVF_VERTEX2D);

	MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	return true;
}

void Sprite_Finalaize(void)
{
	if (g_pVertexBuffer) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	//if (g_pTexture) {
	//	g_pTexture->Release();
	//	g_pTexture = NULL;
	//}


}



void Sprite_Draw(int textureId, float dx, float dy)
{
	

	//テクスチャセットします
	MyDirect3D_GetDevice()->SetTexture(0, Texture_GetTexture(textureId));

	unsigned long w = Texture_GetTextureWidth(textureId);
	unsigned long h = Texture_GetTextureHeight(textureId);

	Vertex2D y[] = {
		{D3DXVECTOR4(100.5f  ,100.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(0.0f ,0.0f)},
		{D3DXVECTOR4(800.5f ,100.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(1.0f ,0.0f)},
		{D3DXVECTOR4(100.5f ,500.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(0.0f ,1.0f)},
		{D3DXVECTOR4(800.5f ,500.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(1.0f ,1.0f)},

	};

	Vertex2D y2[] = {
		 {D3DXVECTOR4(200.5f ,200.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(0.0f ,0.0f)},
		 {D3DXVECTOR4(600.5f ,200.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(0.8f ,0.44f)},
		 {D3DXVECTOR4(200.5f ,400.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(0.0f ,0.9f)},
		 {D3DXVECTOR4(600.5f ,400.5f,1.0f,1.0f),g_Color,D3DXVECTOR2(0.8f ,0.9f)},

	};
	Vertex2D y3[] = {
		 {D3DXVECTOR4(600.5f ,200.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(0.81f ,0.0f)},
		 {D3DXVECTOR4(650.5f ,200.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(1.0f ,0.0f)},
		 {D3DXVECTOR4(600.5f ,250.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(0.81f ,0.185f)},
		 {D3DXVECTOR4(650.5f ,250.5f ,1.0f,1.0f),g_Color,D3DXVECTOR2(1.0f ,0.185f)},

	};
	//頂点バッファをロックしてデータを書き込む

	//インデックスバッファをロックしてデータを書き込む

	

	WORD index[] = {
		0,1,2,3,2,1
	};
	//unsigned short index[] = {
	//	0,1,2,3,2,1
	//};

	

	


	MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	//ポリゴンを描く(簡易版)
	//MyDirect3D_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, y, sizeof(Vertex2D));

	MyDirect3D_GetDevice()->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, 4, 2, index, D3DFMT_INDEX16, y, sizeof(Vertex2D));

	y[0].Position.x += 520.0f;
	y[1].Position.x += 520.0f;
	y[2].Position.x += 520.0f;
	y[3].Position.x += 520.0f;

	//MyDirect3D_GetDevice()->SetTexture(0, Texture_GetTexture(textureId));

	//MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);//D3DTEXT_LINEAR
	//MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);//D3DTEXT_ANISOTROPIC.異方性
	//MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	//MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, y2, sizeof(Vertex2D));

   // g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, y3, sizeof(Vertex2D));
	//D3DPT_TRIANGLELIST
	//D3DPT_TRIANGLESTRIP
	//D3DPT_POINTLIST
	//D3DPT_LINELIST
	//D3DPT_LINESTRIRIP
	//D3DPT_TRIANGLFAM

	
}



//void Sprite_SetColor(D3DCOLOR color)
//{

//}

void SpriteDrawBuffer(int textureId, float dx, float dy, float dw, float dh, float tcx, float tcy, float tcw, float tch, float tw, float th,float angle, float2D scale, D3DCOLOR  color,ANCHORPOINT anPoint) {

	MyDirect3D_GetDevice()->SetTexture(0, Texture_GetTexture(textureId));
	float ul = (float)tcx / tw;
	float ur = (float)(tcx + tcw) / tw;
	float vt = (float)tcy / th;
	float vb = (float)(tcy + tch) / th;
	Vertex2D v[] = { 
		{D3DXVECTOR4(dx      , dy      ,1.0f,1.0f),color,D3DXVECTOR2(ul , vt)},
		{D3DXVECTOR4(dx + dw , dy      ,1.0f,1.0f),color,D3DXVECTOR2(ur , vt)},
		{D3DXVECTOR4(dx      , dy + dh ,1.0f,1.0f),color,D3DXVECTOR2(ul , vb)},
		{D3DXVECTOR4(dx + dw , dy + dh ,1.0f,1.0f),color,D3DXVECTOR2(ur , vb)},
	};

	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	float x0 = dx + (dw / 2);
	float y0 = dy + (dh / 2);
	switch (anPoint)
	{
	case ANCHOR_LU:
		x0 = dx;
		y0 = dy;
		break;
	case ANCHOR_LD:
		x0 = dx;
		y0 = dy + dh;
		break;
	case ANCHOR_RU:
		x0 = dx + dw;
		y0 = dy;
		break;
	case ANCHOR_RD:
		x0 = dx + dw;
		y0 = dy + dh;
		break;
	case ANCHOR_CENTER:
		x0 = dx + (dw / 2);
		y0 = dy + (dh / 2);
		break;
	case ANCHOR_LC:
		x0 = dx;
		y0 = dy + (dh / 2);
		break;
	case ANCHOR_RC:
		x0 = dx + dw;
		y0 = dy + (dh / 2);
		break;
	case ANCHOR_TC:
		x0 = dx + (dw / 2);
		y0 = dy;
		break;
	case ANCHOR_BC:
		x0 = dx + (dw / 2);
		y0 = dy + dh;
		break;
	default:
		break;
	}

	//平行移動行列
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -x0, -y0, 0.0f);

	D3DXMATRIX mtxTranslationC2;
	D3DXMatrixTranslation(&mtxTranslationC2, x0, y0, 0.0f);

	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, 1.0f);


	//行列合成
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxRotation*mtxScale*mtxTranslationC2;//+ mtxTranslationC2 ;

	for (int i = 0; i < 4; i++)
	{

		D3DXVec4Transform(&v[i].Position, &v[i].Position, &mtxWorld);
	}

	Vertex2D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	//データを書き込む
	memcpy(pV, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	WORD* pI;
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, 0);
	pI[0] = 0;
	pI[1] = 1;
	pI[2] = 2;
	pI[3] = 3;
	pI[4] = 2;
	pI[5] = 1;
	g_pIndexBuffer->Unlock();

	

	//デイバスに利用する頂点バッファを指定する
	MyDirect3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));

	//MyDirect3D_GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	MyDirect3D_GetDevice()->SetIndices(g_pIndexBuffer);

	MyDirect3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void SpritePolygonDraw(int textureId, Vertex2D * v , int Count)
{
	MyDirect3D_GetDevice()->SetTexture(0, Texture_GetTexture(textureId));

	//int len = sizeof(v);

	MyDirect3D_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, Count - 2, v, sizeof(Vertex2D));
}

void SpriteDrawLoadTexture(int textureId, float dx, float dy, float dw, float dh, float tcx, float tcy, float tcw, float tch, float tw, float th, float angle, float2D scale, D3DCOLOR color, ANCHORPOINT anPoint)
{
	MyDirect3D_GetDevice()->SetTexture(0, LoadTexture_GetTexture(textureId));
	float ul = (float)tcx / tw;
	float ur = (float)(tcx + tcw) / tw;
	float vt = (float)tcy / th;
	float vb = (float)(tcy + tch) / th;
	Vertex2D v[] = {
		{D3DXVECTOR4(dx      , dy      ,1.0f,1.0f),color,D3DXVECTOR2(ul , vt)},
		{D3DXVECTOR4(dx + dw , dy      ,1.0f,1.0f),color,D3DXVECTOR2(ur , vt)},
		{D3DXVECTOR4(dx      , dy + dh ,1.0f,1.0f),color,D3DXVECTOR2(ul , vb)},
		{D3DXVECTOR4(dx + dw , dy + dh ,1.0f,1.0f),color,D3DXVECTOR2(ur , vb)},
	};

	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	float x0 = dx + (dw / 2);
	float y0 = dy + (dh / 2);
	switch (anPoint)
	{
	case ANCHOR_LU:
		x0 = dx;
		y0 = dy;
		break;
	case ANCHOR_LD:
		x0 = dx;
		y0 = dy + dh;
		break;
	case ANCHOR_RU:
		x0 = dx + dw;
		y0 = dy;
		break;
	case ANCHOR_RD:
		x0 = dx + dw;
		y0 = dy + dh;
		break;
	case ANCHOR_CENTER:
		x0 = dx + (dw / 2);
		y0 = dy + (dh / 2);
		break;
	case ANCHOR_LC:
		x0 = dx;
		y0 = dy + (dh / 2);
		break;
	case ANCHOR_RC:
		x0 = dx + dw;
		y0 = dy + (dh / 2);
		break;
	case ANCHOR_TC:
		x0 = dx + (dw / 2);
		y0 = dy;
		break;
	case ANCHOR_BC:
		x0 = dx + (dw / 2);
		y0 = dy + dh;
		break;
	default:
		break;
	}

	//平行移動行列
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -x0, -y0, 0.0f);

	D3DXMATRIX mtxTranslationC2;
	D3DXMatrixTranslation(&mtxTranslationC2, x0, y0, 0.0f);

	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, 1.0f);


	//行列合成
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxRotation*mtxScale*mtxTranslationC2;//+ mtxTranslationC2 ;

	for (int i = 0; i < 4; i++)
	{

		D3DXVec4Transform(&v[i].Position, &v[i].Position, &mtxWorld);
	}

	Vertex2D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	//データを書き込む
	memcpy(pV, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	WORD* pI;
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, 0);
	pI[0] = 0;
	pI[1] = 1;
	pI[2] = 2;
	pI[3] = 3;
	pI[4] = 2;
	pI[5] = 1;
	g_pIndexBuffer->Unlock();



	//デイバスに利用する頂点バッファを指定する
	MyDirect3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));

	//MyDirect3D_GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	MyDirect3D_GetDevice()->SetIndices(g_pIndexBuffer);

	MyDirect3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void SpriteDrawParatial(int textureId, float dx, float dy, float dw, float dh, float tcx, float tcy, float tcw, float tch, float tw, float th, float angle, float2D scale, D3DCOLOR color, ANCHORPOINT anPoint, float uvX, float uvY, float uvW, float uvH)
{
	MyDirect3D_GetDevice()->SetTexture(0, Texture_GetTexture(textureId));
	float ul = uvX;
	float ur = uvX + uvW;
	float vt = uvY;
	float vb = uvY + uvH;
	Vertex2D v[] = {
		{D3DXVECTOR4(dx + dw * ul , dy + dh * vt ,1.0f,1.0f),color,D3DXVECTOR2(ul , vt)},
		{D3DXVECTOR4(dx + dw * ur , dy + dh * vt ,1.0f,1.0f),color,D3DXVECTOR2(ur , vt)},
		{D3DXVECTOR4(dx + dw * ul , dy + dh * vb ,1.0f,1.0f),color,D3DXVECTOR2(ul , vb)},
		{D3DXVECTOR4(dx + dw * ur , dy + dh * vb ,1.0f,1.0f),color,D3DXVECTOR2(ur , vb)},
	};

	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	float x0 = dx + (dw / 2);
	float y0 = dy + (dh / 2);
	switch (anPoint)
	{
	case ANCHOR_LU:
		x0 = dx;
		y0 = dy;
		break;
	case ANCHOR_LD:
		x0 = dx;
		y0 = dy + dh;
		break;
	case ANCHOR_RU:
		x0 = dx + dw;
		y0 = dy;
		break;
	case ANCHOR_RD:
		x0 = dx + dw;
		y0 = dy + dh;
		break;
	case ANCHOR_CENTER:
		x0 = dx + (dw / 2);
		y0 = dy + (dh / 2);
		break;
	case ANCHOR_LC:
		x0 = dx;
		y0 = dy + (dh / 2);
		break;
	case ANCHOR_RC:
		x0 = dx + dw;
		y0 = dy + (dh / 2);
		break;
	case ANCHOR_TC:
		x0 = dx + (dw / 2);
		y0 = dy;
		break;
	case ANCHOR_BC:
		x0 = dx + (dw / 2);
		y0 = dy + dh;
		break;
	default:
		break;
	}

	//平行移動行列
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -x0, -y0, 0.0f);

	D3DXMATRIX mtxTranslationC2;
	D3DXMatrixTranslation(&mtxTranslationC2, x0, y0, 0.0f);

	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, 1.0f);


	//行列合成
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxRotation*mtxScale*mtxTranslationC2;//+ mtxTranslationC2 ;

	for (int i = 0; i < 4; i++)
	{

		D3DXVec4Transform(&v[i].Position, &v[i].Position, &mtxWorld);
	}

	Vertex2D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	//データを書き込む
	memcpy(pV, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	WORD* pI;
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, 0);
	pI[0] = 0;
	pI[1] = 1;
	pI[2] = 2;
	pI[3] = 3;
	pI[4] = 2;
	pI[5] = 1;
	g_pIndexBuffer->Unlock();



	//デイバスに利用する頂点バッファを指定する
	MyDirect3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));

	//MyDirect3D_GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	MyDirect3D_GetDevice()->SetIndices(g_pIndexBuffer);

	MyDirect3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void SpriteDraw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, int tw, int th, float angle, float2D scale, int alpha)
{
	//FVFの設定をする
	//MyDirect3D_GetDevice()->SetFVF(FVF_VERTEX2D);

	//テクスチャセットします
	MyDirect3D_GetDevice()->SetTexture(0, Texture_GetTexture(textureId));

	unsigned long w = Texture_GetTextureWidth(textureId);
	unsigned long h = Texture_GetTextureHeight(textureId);

	float ul = (float)tcx / tw;
	float ur = (float)(tcx + tcw) / tw;
	float vt = (float)tcy / th;
	float vb = (float)(tcy + tch) / th;

	

	Vertex2D y[] = {
		{D3DXVECTOR4(dx    , dy    ,1.0f,1.0f),D3DCOLOR_RGBA(225,255,255,alpha),D3DXVECTOR2(ul , vt)},
		{D3DXVECTOR4(dx + dw , dy    ,1.0f,1.0f),D3DCOLOR_RGBA(225,255,255,alpha),D3DXVECTOR2(ur , vt)},
		{D3DXVECTOR4(dx    , dy + dh ,1.0f,1.0f),D3DCOLOR_RGBA(225,255,255,alpha),D3DXVECTOR2(ul , vb)},
		{D3DXVECTOR4(dx + dw , dy + dh ,1.0f,1.0f),D3DCOLOR_RGBA(225,255,255,alpha),D3DXVECTOR2(ur , vb)},
	};
	//回転行列
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	float x0 = dx + (dw / 2);
	float y0 = dy + (dh / 2);

	//平行移動行列
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -x0, -y0, 0.0f);

	D3DXMATRIX mtxTranslationC2;
	D3DXMatrixTranslation(&mtxTranslationC2, x0, y0, 0.0f);

	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, 1.0f);


	//行列合成
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxRotation*mtxScale*mtxTranslationC2;           //+ mtxTranslationC2 ;

	

	

	for (int  i = 0; i < 4; i++)
	{
		
		D3DXVec4Transform(&y[i].Position, &y[i].Position, &mtxWorld);
	}

	//D3DXVec4Transform(&y[i], &y[i], &mtxRotation);
	

	//画面クリア       //部分クリア
	//MyDirect3D_GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 80, 200, 255), 1.0f, 0);
	//描画バッチ命令の開始
	//MyDirect3D_GetDevice()->BeginScene();

	//MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	//MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	
	//ポリゴンを描く(簡易版)
	MyDirect3D_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, y, sizeof(Vertex2D));

	//描画バッチ命令の終了
	//MyDirect3D_GetDevice()->EndScene();
	//バックバッファをフリップ（タイミングはD3DPRESENT_PARAMETERSの設定にする
	//MyDirect3D_GetDevice()->Present(NULL, NULL, NULL, NULL);
}

void SpriteDraw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, int tw, int th, float angle)
{
	//テクスチャセットします
	MyDirect3D_GetDevice()->SetTexture(0, Texture_GetTexture(textureId));

	unsigned long  w = Texture_GetTextureWidth(textureId);
	unsigned long h = Texture_GetTextureHeight(textureId);

	float ul = (float)tcx / tw;
	float ur = (float)(tcx + tcw) / tw;
	float vt = (float)tcy / th;
	float vb = (float)(tcy + tch) / th;



	Vertex2D y[] = {
		{D3DXVECTOR4(dx    , dy    ,1.0f,1.0f),D3DCOLOR_RGBA(225,255,255,255),D3DXVECTOR2(ul , vt)},
		{D3DXVECTOR4(dx + dw , dy    ,1.0f,1.0f),D3DCOLOR_RGBA(225,255,255,255),D3DXVECTOR2(ur , vt)},
		{D3DXVECTOR4(dx    , dy + dh ,1.0f,1.0f),D3DCOLOR_RGBA(225,255,255,255),D3DXVECTOR2(ul , vb)},
		{D3DXVECTOR4(dx + dw , dy + dh ,1.0f,1.0f),D3DCOLOR_RGBA(225,255,255,255),D3DXVECTOR2(ur , vb)},
	};
	//回転行列
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	float x0 = dx + (dw / 2);
	float y0 = dy + (dh / 2);

	//平行移動行列
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -x0, -y0, 0.0f);

	D3DXMATRIX mtxTranslationC2;
	D3DXMatrixTranslation(&mtxTranslationC2, x0, y0, 0.0f);

	D3DXMATRIX mtxScale;
	D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);


	//行列合成
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxRotation*mtxScale*mtxTranslationC2;//+ mtxTranslationC2 ;





	for (int i = 0; i < 4; i++)
	{

		D3DXVec4Transform(&y[i].Position, &y[i].Position, &mtxWorld);
	}

	//D3DXVec4Transform(&y[i], &y[i], &mtxRotation);


	//画面クリア       //部分クリア
	//MyDirect3D_GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 80, 200, 255), 1.0f, 0);
	//描画バッチ命令の開始
	//MyDirect3D_GetDevice()->BeginScene();

	//MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	//MyDirect3D_GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	//ポリゴンを描く(簡易版)
	MyDirect3D_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, y, sizeof(Vertex2D));

}


int SpriteParticle_CreatBuffer(int Count)
{
	int ID = -1;
	for (int i = 0; i < PDATAMAX; i++)
	{
		if (partData[i].active)continue;
		ID = i;
		break;
	}

	if (ID == -1)return ID;

	partData[ID].polygonCount = Count;

	LPDIRECT3DDEVICE9 mDevice = MyDirect3D_GetDevice();


	mDevice->CreateVertexBuffer(
		sizeof(Vertex2D) * 4 * Count,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX2D,
		D3DPOOL_MANAGED,
		&partData[ID].g_pVertexBuff,
		NULL
	);

	mDevice->CreateIndexBuffer(
		sizeof(DWORD) * 6 * Count,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&partData[ID].g_pIndexBuff,
		NULL
	);

	partData[ID].active = true;

	return ID;
}

void SpriteParticle_Draw(int textureId, Vertex2D* v, int partId) {

	LPDIRECT3DDEVICE9 mDevice = MyDirect3D_GetDevice();
	mDevice->SetTexture(0, Texture_GetTexture(textureId));
	Vertex2D* pV;
	partData[partId].g_pVertexBuff->Lock(0, 0, (void**)&pV, 0);
	for (int i = 0; i < partData[partId].polygonCount * 4; i++)
	{
		pV[i].Position = v[i].Position;
		pV[i].Color = v[i].Color;
		pV[i].TexCoord = v[i].TexCoord;
	}
	partData[partId].g_pVertexBuff->Unlock();

	DWORD* pI;
	partData[partId].g_pIndexBuff->Lock(0, 0, (void**)&pI, 0);

	for (int i = 0; i < partData[partId].polygonCount; i++)
	{
		pI[0 + i * 6] = 0 + 4 * i;
		pI[1 + i * 6] = 1 + 4 * i;
		pI[2 + i * 6] = 2 + 4 * i;
		pI[3 + i * 6] = 3 + 4 * i;
		pI[4 + i * 6] = 2 + 4 * i;
		pI[5 + i * 6] = 1 + 4 * i;
	}
	partData[partId].g_pIndexBuff->Unlock();

	
	mDevice->SetIndices(partData[partId].g_pIndexBuff);
	mDevice->SetStreamSource(0, partData[partId].g_pVertexBuff, 0, sizeof(Vertex2D));	
	mDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, partData[partId].polygonCount * 4, 0, partData[partId].polygonCount * 2);
}
void SpriteParticle_Release(int partId) {

	if (partData[partId].active) {
		partData[partId].g_pIndexBuff->Release();
		partData[partId].g_pVertexBuff->Release();
		partData[partId].g_pIndexBuff = NULL;
		partData[partId].g_pVertexBuff = NULL;
		partData[partId].active = false;
		partData[partId].polygonCount = 0;
	}
}








#ifndef BASE_SPRITE_H
#define BASE_SPRITE_H
#include <d3dx9.h>
#include"base_Camera.h"
#include"texture.h"
#include "sprite.h"
#include "Math.h"



enum SPRITETYPE {
	SPRITE_OBJ,
	SPRITE_UI,
	SPRITE_POLYGON,
	SPRITE_PARTIAL,
	SPRITE_ALPHABLEND,
	SPRITE_PARTICLE,
};

class SpData {
public:
	SpData();
	virtual ~SpData();
public:
	float posX;                        //ポリゴン座標X
	float posY;                        //ポリゴン座標Y

//この部分が
protected:
	float width;                         //ポリゴン横幅
	float height;					       //ポリゴン縦幅
	float2D HVratio;

	float texture_width;                 //テクスチャ横幅
	float texture_height;				 //テクスチャ縦幅
	float texture_cutX;                  //テクスチャ切り取り座標X
	float texture_cutY;                  //テクスチャ切り取り座標Y
	float texture_cutW;                  //テクスチャ切り取り横幅
	float texture_cutH;                  //テクスチャ切り取り縦幅

	float angle;                       //回転角度
	D3DCOLOR color;                     //r,g,b,a;
	int4D colorData;

	float2D scale;			           //ポリゴンのサイズ変換
	float2D multiple;                  //座標変換時、の変換倍数。
	float cameraOffsetX;               //multiple.xが1ではない場合、座標計算用。
	float cameraOffsetY;               //multiple.yが1ではない場合、座標計算用。


	int2D textureDirection;            //テクスチャプリント方向
	int2D textureRegionNumber;         //テクスチャ区画番号
	int2D textureRegionTotal;		   //テクスチャ区画数

	ANCHORPOINT anchorPoint;           //アンカーポイント
	float anchorX;                     //スプライトのアンカーポイントと左上の距離x
	float anchorY;                     //スプライトのアンカーポイントと左上の距離y

	bool active;                       //アクティブ状態フラグ

public:
	//ポジションを設定
 	virtual void SetPosition(float x, float y) { posX = x; posY = y; }
	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }

	//アクティブ状態設定
	void SetActive(bool actf) { active = actf; }
	//アクティブ状態を取得。
	bool GetActive() { return active; }

	//回転角度を設定
	void SetAngle(float ang) { angle = ang; }

	//透明度を設定
	void SetAlpha(float al);

	//スプライトの拡大、縮小倍数を指定
	void SetScale(float scaleX, float scaleY);
	float2D GetScale() { return { scale.x,scale.y }; }

	void SetAnchorPoint(ANCHORPOINT aPoint);

	//テクスチャの貼り方向、-1 or 1 を指定してください。（x,横方向.ｙ、縦方向）
	void SetSprteDirection(int x, int y) { textureDirection.x = x; textureDirection.y = y; }

	//色変え
	void SetColor(int cR, int cG, int cB);
	void SetColor(D3DCOLOR d3dcolor);

	//スプライトの長さと高さを指定,setCutSize()と違う、
	void SetWidth(float x);
	void SetHeight(float y);
	void SetSpriteSize(float x, float y);

	//スプライトの長さと高さを獲得
	float GetWidth() { return width * scale.x; }
	float GetHeight() { return height * scale.y; }

	//テクスチャ貼り方向を取得。
	int GetDirX() { return textureDirection.x; }
	int GetDirY() { return textureDirection.y; }

	//透明度を取得。
	float GetAlpha() { return ((float)colorData.a) / 255.0f; }

	float GetAngle() const { return angle; }

	//座標を取得。
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }

	void SetTextureSize(float x, float y);

	ANCHORPOINT GetAnchorPoint() { return anchorPoint; }

	D3DCOLOR GetD3DColor() { return color; }

	float2D GetLUpos() { return { posX - anchorX * scale.x,posY - anchorY * scale.y }; }
	float2D GetLDpos() { return { posX - anchorX * scale.x,posY - anchorY * scale.y + GetHeight() }; }
	float2D GetRUpos() { return { posX - anchorX * scale.x + GetWidth(),posY - anchorY * scale.y }; }
	float2D GetRDpos() { return { posX - anchorX * scale.x + GetWidth(), posY - anchorY * scale.y + GetHeight() }; }
	float2D GetLUUV();
	float2D GetLDUV();
	float2D GetRUUV();
	float2D GetRDUV();
};

class SpriteC :public SpData{
public:
	SpriteC() {};
	SpriteC(const char* pFilename, const char* Name,int Layer = 9,SPRITETYPE sptype = SPRITE_OBJ);
	SpriteC(const char* pFilename, int Layer = 9, SPRITETYPE sptype = SPRITE_OBJ);
	virtual ~SpriteC();
	void SpriteCparameteSet(const char* pFilename, const char* Name, int Layer = 9, SPRITETYPE sptype = SPRITE_OBJ);
public:
	//float posX;                        //ポリゴン座標X
	//float posY;                        //ポリゴン座標Y

//この部分が
protected:
	//float width;                         //ポリゴン横幅
	//float height;					       //ポリゴン縦幅
	//float2D HVratio;
	//
	//float texture_width;                 //テクスチャ横幅
	//float texture_height;				 //テクスチャ縦幅
	//float texture_cutX;                  //テクスチャ切り取り座標X
	//float texture_cutY;                  //テクスチャ切り取り座標Y
	//float texture_cutW;                  //テクスチャ切り取り横幅
	//float texture_cutH;                  //テクスチャ切り取り縦幅

	//float angle;                       //回転角度
	//D3DCOLOR color;                     //r,g,b,a;
	//int4D colorData;
	//
	//float2D scale;			           //ポリゴンのサイズ変換
	//float2D multiple;                  //座標変換時、の変換倍数。
	//float cameraOffsetX;               //multiple.xが1ではない場合、座標計算用。
	//float cameraOffsetY;               //multiple.yが1ではない場合、座標計算用。


	//int2D textureDirection;            //テクスチャプリント方向
	//int2D textureRegionNumber;         //テクスチャ区画番号
	//int2D textureRegionTotal;		   //テクスチャ区画数

	//ANCHORPOINT anchorPoint;           //アンカーポイント
	//float anchorX;                     //スプライトのアンカーポイントと左上の距離x
	//float anchorY;                     //スプライトのアンカーポイントと左上の距離y

	char name[64];
	
	int textureID;                     //texture管理ID
	int layer;					       //レイヤー
	int arrayID;                       //sprite管理ID

	SPRITETYPE spriteType;             //スプライトのタイプ
	//bool deleteFlag;

public:
	void Init();
	//void Update();
	virtual void Draw(CameraC* ca);
	//void Final();

	//スプライトのタイプ指定
	void SetSpriteType(SPRITETYPE sptype) { spriteType = sptype; }
	//カメラに相対的座標変換倍数設定
	void SetMultiple(float x, float y);
	//スプライトのカートサイズ指定、（スプライトサイズとテクスチャの描画範囲を同時に設定）テクスチャのUV座標と合わせてください。
	void SetCutSize(int size_w, int size_h);
	
	//テクスチャの描画範囲を指定（カートサイズを単位として、１ずつで指定）
	void SetRegion(int x, int y);
	
	//レイヤー変更
	void SetLayerChange(int laye);
	
	//テクスチャ管理番号を取得。
	int GetID() { return textureID; }
	//スプライト管理番号を取得。
	int GetArrayID() { return arrayID; }
	//レイヤーを獲得
	int GetLayer() { return layer; }
	//テクスチャ区画数を取得。
	int GetRegionTotalX() { return textureRegionTotal.x; }
	int GetRegionTotalY() { return textureRegionTotal.y; }
	
	
	//multiple(座標換算比率）が１ではない場合、換算後の座標を取得。
	float GetCameraOffsetPosX() { return posX + cameraOffsetX; }
	float GetCameraOffsetPosY() { return posY + cameraOffsetY; }
	
	const char* GetName() { return name; }
	
	Vector2 GetPosition() const { return Vector2(posX, posY); }
	void SetPosition(float x, float y)override;
	void SetPosition(const Vector2& position) { posX = position.x, posY = position.y; }
};

//UIスプライト、カメラに相対的静止なので、カメラの左上は座標（0,0）
class SpriteUI :public SpriteC {
public:
	SpriteUI(const char* pFilename, const char* Name, int Layer = 15, SPRITETYPE sptype = SPRITE_UI) : SpriteC(pFilename, Name, Layer, sptype) { lens = 1; }
	SpriteUI(const char* pFilename, int Layer = 15, SPRITETYPE sptype = SPRITE_UI) :SpriteC(pFilename, Layer, sptype) { lens = 1; };
	~SpriteUI();

public:
	void Draw(CameraC* ca) override;
	//UIがステージ上の座標を取得（GetPosX()とGetPosYがカメラの左上に相対的座標を取得なので、UIとステージ内の物と当たり判定にしたいなら、この関数を使って）
	float GetCameraOffsetWidth() { return width * scale.x * lens; }    //カメラを参照して、相対座標を取得。
	float GetCameraOffsetHeight() { return height * scale.y * lens; }
private:
	//カメラと画面の距離
	float lens;    
};

//多角形スプライト、デフォルトは矩形, 
class SpritePL :public SpriteC {
public:
	SpritePL(const char* pFilename,const char* Name,int Layer = 9,SPRITETYPE sp = SPRITE_POLYGON):SpriteC(pFilename,Name,Layer,sp){	}
	SpritePL(const char* pFilename,int Layer = 9,SPRITETYPE sp = SPRITE_POLYGON):SpriteC(pFilename,Layer,sp){}
	~SpritePL();

public:
	void InitPL();
	void Draw(CameraC* ca)override;

	//多角形の頂点を指定。
	void SetPolygonPoint(float2D* vList,int Count);
private:
	//頂点
	Vertex2D* v2dList;
	//頂点とテクスチャ位置関係
	float2D* pvl;
	//頂点数
	int verCount;

	//多角形の頂点描画調整
	void DrawPolygon(float pX, float pY, float w, float h, float tc_posX, float tc_posY, float tcW, float tcH);
};


//部分描画スプライト
class SpritePA :public SpriteC {
public:
	SpritePA(const char* pFilename, const char* Name, int Layer = 9, SPRITETYPE sp = SPRITE_PARTIAL) :SpriteC(pFilename, Name, Layer, sp) {
		partialX = partialY = 0.0f;
		partialW = partialH = 1.0f;
		pAnchorPoint = ANCHOR_LU;
	}
	SpritePA(const char* pFilename, int Layer = 9, SPRITETYPE sp = SPRITE_PARTIAL) :SpriteC(pFilename, Layer, sp) {
		partialX = partialY = 0.0f;
		partialW = partialH = 1.0f;
		pAnchorPoint = ANCHOR_LU;
	}
	~SpritePA();

public:
	//描画部分の比率横幅指定
	void SetPartialWidth(float w);
	//描画部分の比率の縦幅を指定
	void SetPartialHeight(float h);
	//描画比率設定参考ポイント
	void SetPartialAnchorPoint(ANCHORPOINT ap);

	void Draw(CameraC* ca)override;
private:
	float partialX;
	float partialY;
	float partialW;
	float partialH;
	ANCHORPOINT pAnchorPoint;
	//描画部分再計算。
	//void ParitalPosReSet(float x, float y);
};

//アルファブレンド処理できるスプライト
class SpriteAB :public SpriteC {
public:
	SpriteAB(const char* pFilename, const char* Name, int Layer = 14, SPRITETYPE sp = SPRITE_ALPHABLEND) :SpriteC(pFilename,Name, Layer, sp) {

	}
	SpriteAB(const char* pFilename, int Layer = 14, SPRITETYPE sp = SPRITE_ALPHABLEND) :SpriteC(pFilename, Layer, sp) {

	}
	~SpriteAB();

	enum 
	{
		dest_one,
	};

	void SetAlphaBlendDest(int blendType);
	void SetAlphaBlendSrc(int blendType);
public:
	void Draw(CameraC* ca)override;
	int destType;
	int srcType;
	
};


class ParticleC {
public:
	ParticleC(const char* pFilename, int Count, int Layer = 14);
	~ParticleC();
public:
	float posX;
	float posY;
public:
	void Init();

	SpData* GetPdata(int number) { return &pSpData[number]; }
	int GetPcount() { return pCount; }
	int GetLayer() { return layer; }
	void SetActive(bool act) { active = act; }
	bool GetActive() { return active; }
	int GetArrayID() { return arrayID; }
	int GetTextureID() { return textureID; }
	float2D GetPostion() { return { posX, posY }; }

	void SetSpDataAngleAll(float ang);
	void Set_SpData_ScaleAll(float x, float y);
	void SetPostion(float x, float y) { posX = x; posY = y; }
private:
	int pCount;
	SpData* pSpData;
	Vertex2D* pVertex2D;
	int textureID;
	int layer;
	bool active;
	int partID;
	int arrayID;

public:
	void Draw(CameraC * ca);
};

#endif // !BASE_SPRITE_H


#ifndef BASE_CAMERA_H
#define BASE_CAMERA_H
#include "collision.h"

class CameraC {
public:
	CameraC(int width,int height);
	~CameraC();

	//void SpritesLoad();
	void Init();
	void Update();
	//void Draw();
	void Final();
	void SetFocusPos(float x, float y);
	void SetFocusPosX(float x);
	void SetFocusPosY(float y);
	void SetPos(float x, float y);
	void SetBoundary(int x, int y, int w, int h);
	void SetLensDistance(float lens);         //欲しいZoom率を設定(瞬間に変化)
	void SetLensDistanceMax(float lenMax);    //Zoom率の最大値を設定
	void SetZoom(float tLens);                //指定の速さでZoom率を拡大縮小
	void SetLensOff(float loff);              //Zoom率の変化率設定（Zoom変化の速さ）
	void SetFocusLens(float lens,float loff); //lens:欲しいZoom率を設定、loff:変化率を設定,緩やかに変化
	void SetFocusLens(float lens);            //欲しいZoom率を設定、緩やかに変化

	float GetOffsetPosX() { return offsetPosX; }
	float GetOffsetPosY() { return offsetPosY; }
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }
	//Zoom率を獲得できる
	float GetLensDistance() { return lensDistance; }
	float GetScreenCameraWidth() { return ScreenWidth; }
	float GetScreenCameraHeight() { return ScreenHeight; }
	float GetBoundrayX() { return BoundaryX; }
	float GetBoundrayY() { return BoundaryY; }
	float GetBoundrayW() { return BoundaryW; }
	float GetBoundrayH() { return BoundaryH; }
	float GetBoundrayBottem() { return BoundaryY + BoundaryH; }
	float GetBoundrayRight() { return BoundaryX + BoundaryW; }
	CollisionRectangle GetCameraWindowRectangle();

private:
	float focusPosX;        //目標位置ｘ
	float focusPosY;        //目標位置ｙ
	float posX;             //カメラ位置ｘ
	float posY;             //カメラ位置 y
	float offsetPosX;       //Sprite描画用計算座標X
	float offsetPosY;       //Sprite描画用計算座標Y
	float lensDistance;     //レンズ距離
	float lensDistanceMax;
	float focusLensDistance;
	float ScreenWidth;        //カメラ視角画面横幅
	float ScreenHeight;       //カメラ視角画面縦幅
	float baseScreenWidth;    //参照画面横幅
	float baseScreenHeight;   //参照画面縦幅
	float BoundaryX;          //カメラ運動限界BOXの起点X
	float BoundaryY;          //カメラ運動限界BOXの起点Y
	float BoundaryW;          //カメラ運動限界BOXの横幅
	float BoundaryH;          //カメラ運動限界BOXの縦幅
	float LensOff;
	
private:
	void focusLensUpdate();
};



#endif // !BASE_CAMERA_H

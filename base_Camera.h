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
	void SetLensDistance(float lens);         //—~‚µ‚¢Zoom—¦‚ğİ’è(uŠÔ‚É•Ï‰»)
	void SetLensDistanceMax(float lenMax);    //Zoom—¦‚ÌÅ‘å’l‚ğİ’è
	void SetZoom(float tLens);                //w’è‚Ì‘¬‚³‚ÅZoom—¦‚ğŠg‘åk¬
	void SetLensOff(float loff);              //Zoom—¦‚Ì•Ï‰»—¦İ’èiZoom•Ï‰»‚Ì‘¬‚³j
	void SetFocusLens(float lens,float loff); //lens:—~‚µ‚¢Zoom—¦‚ğİ’èAloff:•Ï‰»—¦‚ğİ’è,ŠÉ‚â‚©‚É•Ï‰»
	void SetFocusLens(float lens);            //—~‚µ‚¢Zoom—¦‚ğİ’èAŠÉ‚â‚©‚É•Ï‰»

	float GetOffsetPosX() { return offsetPosX; }
	float GetOffsetPosY() { return offsetPosY; }
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }
	//Zoom—¦‚ğŠl“¾‚Å‚«‚é
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
	float focusPosX;        //–Ú•WˆÊ’u‚˜
	float focusPosY;        //–Ú•WˆÊ’u‚™
	float posX;             //ƒJƒƒ‰ˆÊ’u‚˜
	float posY;             //ƒJƒƒ‰ˆÊ’u y
	float offsetPosX;       //Sprite•`‰æ—pŒvZÀ•WX
	float offsetPosY;       //Sprite•`‰æ—pŒvZÀ•WY
	float lensDistance;     //ƒŒƒ“ƒY‹——£
	float lensDistanceMax;
	float focusLensDistance;
	float ScreenWidth;        //ƒJƒƒ‰‹Šp‰æ–Ê‰¡•
	float ScreenHeight;       //ƒJƒƒ‰‹Šp‰æ–Êc•
	float baseScreenWidth;    //QÆ‰æ–Ê‰¡•
	float baseScreenHeight;   //QÆ‰æ–Êc•
	float BoundaryX;          //ƒJƒƒ‰‰^“®ŒÀŠEBOX‚Ì‹N“_X
	float BoundaryY;          //ƒJƒƒ‰‰^“®ŒÀŠEBOX‚Ì‹N“_Y
	float BoundaryW;          //ƒJƒƒ‰‰^“®ŒÀŠEBOX‚Ì‰¡•
	float BoundaryH;          //ƒJƒƒ‰‰^“®ŒÀŠEBOX‚Ìc•
	float LensOff;
	
private:
	void focusLensUpdate();
};



#endif // !BASE_CAMERA_H

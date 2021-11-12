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
	void SetLensDistance(float lens);         //�~����Zoom����ݒ�(�u�Ԃɕω�)
	void SetLensDistanceMax(float lenMax);    //Zoom���̍ő�l��ݒ�
	void SetZoom(float tLens);                //�w��̑�����Zoom�����g��k��
	void SetLensOff(float loff);              //Zoom���̕ω����ݒ�iZoom�ω��̑����j
	void SetFocusLens(float lens,float loff); //lens:�~����Zoom����ݒ�Aloff:�ω�����ݒ�,�ɂ₩�ɕω�
	void SetFocusLens(float lens);            //�~����Zoom����ݒ�A�ɂ₩�ɕω�

	float GetOffsetPosX() { return offsetPosX; }
	float GetOffsetPosY() { return offsetPosY; }
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }
	//Zoom�����l���ł���
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
	float focusPosX;        //�ڕW�ʒu��
	float focusPosY;        //�ڕW�ʒu��
	float posX;             //�J�����ʒu��
	float posY;             //�J�����ʒu y
	float offsetPosX;       //Sprite�`��p�v�Z���WX
	float offsetPosY;       //Sprite�`��p�v�Z���WY
	float lensDistance;     //�����Y����
	float lensDistanceMax;
	float focusLensDistance;
	float ScreenWidth;        //�J�������p��ʉ���
	float ScreenHeight;       //�J�������p��ʏc��
	float baseScreenWidth;    //�Q�Ɖ�ʉ���
	float baseScreenHeight;   //�Q�Ɖ�ʏc��
	float BoundaryX;          //�J�����^�����EBOX�̋N�_X
	float BoundaryY;          //�J�����^�����EBOX�̋N�_Y
	float BoundaryW;          //�J�����^�����EBOX�̉���
	float BoundaryH;          //�J�����^�����EBOX�̏c��
	float LensOff;
	
private:
	void focusLensUpdate();
};



#endif // !BASE_CAMERA_H

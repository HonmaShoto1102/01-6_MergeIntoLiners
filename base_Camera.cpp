#include "base_Camera.h"

CameraC::CameraC(int width, int height)
{
	ScreenWidth = (float)width;
	ScreenHeight =(float)height;
	baseScreenWidth = ScreenWidth;
	baseScreenHeight = ScreenHeight;
	focusPosX = 0;
	focusPosY = 0;
	posX = 0;
	posY = 0;
	offsetPosX = posX - ScreenWidth / 2;
	offsetPosY = posY - ScreenHeight / 2;
	BoundaryX = -1000;
	BoundaryY = -1000;
	BoundaryW = 3000;
	BoundaryH = 3000;
	lensDistance = 1.0f;
	focusLensDistance = 1.0f;
	LensOff = 0.01f;
	lensDistanceMax = 1.0f;
}

CameraC::~CameraC()
{
}

void CameraC::Init()
{
	SetPos((float)(ScreenWidth / 2), (float)(ScreenHeight / 2));
}

void CameraC::Update()
{
	if (posX != focusPosX) {
		if (focusPosX > posX) {
			float temp = (focusPosX - posX) / 15;
			//if (temp <= 0.5)temp = 0.5f;
			posX += temp;
			if ((int)(posX + 0.5f) >= focusPosX)posX = focusPosX;
		}
		if (focusPosX < posX) {
			float temp = (focusPosX - posX) / 15;
			//if (temp >= -0.5)temp = -0.5f;
			posX += temp;
			if ((int)(posX - 0.5f) <= focusPosX)posX = focusPosX;
		}
	}
	if (posY != focusPosY) {
		if (focusPosY > posY) {
			float temp = (focusPosY - posY) / 15;
			//if (temp <= 0.5)temp = 0.5f;
			posY += temp;
			if ((int)(posY + 0.5f) >= focusPosY)posY = focusPosY;
		}
		if (focusPosY < posY) {
			float temp = (focusPosY - posY) / 15;
			//if (temp >= -0.5)temp = -0.5f;
			posY += temp;
			if ((int)(posY - 0.5f) <= focusPosY)posY = focusPosY;
		}
	}
	offsetPosX = posX - ScreenWidth / 2;
	offsetPosY = posY - ScreenHeight / 2;

	if (offsetPosX < BoundaryX)offsetPosX = BoundaryX;
	if (offsetPosX + ScreenWidth > BoundaryX + BoundaryW)offsetPosX = BoundaryX + BoundaryW - ScreenWidth;
	if (offsetPosY < BoundaryY)offsetPosY = BoundaryY;
	if (offsetPosY + ScreenHeight > BoundaryY + BoundaryH)offsetPosY = BoundaryY + BoundaryH - ScreenHeight;

	posX = offsetPosX + ScreenWidth / 2;
	posY = offsetPosY + ScreenHeight / 2;

	focusLensUpdate();
}

void CameraC::Final()
{
}

void CameraC::SetFocusPos(float x, float y)
{
	focusPosX = x;
	focusPosY = y;
}

void CameraC::SetFocusPosX(float x)
{
	focusPosX = x;
}

void CameraC::SetFocusPosY(float y)
{
	focusPosY = y;
}

void CameraC::SetPos(float x, float y)
{
	focusPosX = x;
	focusPosY = y;
	posX = focusPosX;
	posY = focusPosY;
}

void CameraC::SetBoundary(int x, int y, int w, int h)
{
	BoundaryX = (float)x;
	BoundaryY = (float)y;
	BoundaryW = (float)w;
	BoundaryH = (float)h;
}

void CameraC::SetLensDistance(float lens)
{
	lensDistance = lens;
	if (lensDistance <= 0.2f) {
		lensDistance = 0.2f;
	}
	if (lensDistance > lensDistanceMax)lensDistance = lensDistanceMax;

	ScreenWidth = (baseScreenWidth * lensDistance);
	ScreenHeight = (baseScreenHeight * lensDistance);
	
	//offsetPosX = posX - ScreenWidth / 2;
	//offsetPosY = posY - baseScreenHeight / 2;
}

void CameraC::SetLensDistanceMax(float lenMax)
{
	lensDistanceMax = lenMax;
}

void CameraC::SetZoom(float tLens)
{
	lensDistance += tLens;
	if (lensDistance <= 0.2f) {
		lensDistance = 0.2f;
	}

	if (lensDistance > lensDistanceMax)lensDistance = lensDistanceMax;

	ScreenWidth = (baseScreenWidth * lensDistance);
	ScreenHeight = (baseScreenHeight * lensDistance);

	if (ScreenWidth > BoundaryW) {
		lensDistance = BoundaryW / baseScreenWidth;
		ScreenWidth = BoundaryW;
		ScreenHeight = (baseScreenHeight * lensDistance);
	}
	if (ScreenHeight > BoundaryH) {
		lensDistance = BoundaryH / baseScreenHeight;;
		ScreenHeight = BoundaryH;
		ScreenWidth = baseScreenWidth * lensDistance;
	}
}

void CameraC::SetLensOff(float loff)
{
	LensOff = loff;
}

void CameraC::SetFocusLens(float lens, float loff)
{
	focusLensDistance = lens;
	LensOff = loff;
}

void CameraC::SetFocusLens(float lens)
{
	focusLensDistance = lens;
}

CollisionRectangle CameraC::GetCameraWindowRectangle()
{
	CollisionRectangle wColl{
		offsetPosX,
		offsetPosY,
		ScreenWidth,
		ScreenHeight
	};

	return wColl;
}

void CameraC::focusLensUpdate()
{
	if (lensDistance == focusLensDistance)return;
	if (fabsf(focusLensDistance - lensDistance) <= LensOff)lensDistance = focusLensDistance;

	if (lensDistance < focusLensDistance) {
		SetZoom(LensOff);
	}
	else if (lensDistance > focusLensDistance) {
		SetZoom(-LensOff);
	}
}


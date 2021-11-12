#ifndef FAIRYSTATES_H
#define FAIRYSTATES_H
#include "base_State.h"
#include "FairyVH.h"
#include "Line.h"



class Fs_Stand :public baseState<FAIRYSTATEe> {
public:
	Fs_Stand(FAIRYSTATEe fs,FAIRY* fa);
	~Fs_Stand();

	void Init()override;
	void Update()override;
	void Final()override;
	void SetCoolTimeMax(int tim);
	int GetCoolTime() { return CoolTime; }
	int GetCoolTimeMax() { return CoolTimeMax; }
		
private:
	FAIRY* fairy;
	int CoolTime;
	int CoolTimeMax;

};

class Fs_Appear :public baseState<FAIRYSTATEe> {
public:
	Fs_Appear(FAIRYSTATEe fs, FAIRY* fa);
	~Fs_Appear();

	void Init()override;
	void Update()override;
	void Final()override;
	int fairyCountDownTime;
	int fairyDruationTime;
	void SetDir(int dir) { fdir = dir; }
	
private:
	FAIRY* fairy;
	float startPosX;
	float endPosX;
	float startPosY;
	float endPosY;
	float posX;
	float posY;
	int timeCount;
	int fdir;
	float epX;
	float epY;
	FAIRY_LINEe FL;
	float htPosx;
	float htPosy;
	int ClearLineNum;
	float zf;//êUïù
	float wtha;//à ëä
	float Hz; //ïpìx
	SpriteC* targetCusour;
};

class Fs_LineBecame :public baseState<FAIRYSTATEe> {
public:
	Fs_LineBecame(FAIRYSTATEe fs, FAIRY* fa);
	~Fs_LineBecame();

	void Init()override;
	void Update()override;
	void Final()override;

	int lineCountDownTime;
	int lineDruationTime;

	
private:
	FAIRY* fairy;
	
};

class Fs_OblMoving :public baseState<FAIRYSTATEe> {
public:
	Fs_OblMoving(FAIRYSTATEe fs, FAIRY* fa);
	~Fs_OblMoving();

	

	void Init()override;
	void Update()override;
	void Final()override;

	int fairyCountDownTime;
	int fairyDruationTime;

	
private:
	FAIRY* fairy;
	SpriteC* startPoint;
	SpriteC* endPoint;
	float startPosX;
	float endPosX;
	float startPosY;
	float endPosY;
	float startPosXtemp;
	float startPosYtemp;
	float endPosXtemp;
	float endPosYtemp;
	float posX;
	float posY;
	int timeCount;
	int fdir;
	float angle[4];//äpìx
	int angNum;
	float screenLeft;
	float screenTop;
	void AllInput();
	void MoveInFairyLine(ltp tp,float tx,float ty);
	void StrongLineCheck();
	ltp currentltp;
	FAIRY_LINEe FL;
	float htPosX;
	float htPosY;
	int ClearLineNum;

	float CameraScreenW;
	float CameraScreenH;

	SpriteC* targetCusour;
};
//class Fs_OblMoving:public baseState<FAIR>

#endif // !FAIRYSTATES_H


#ifndef BASE_ANIMATION_H
#define BASE_ANIMATION_H
#include "base_Sprite.h"

class AnimationC {
public:
	//スプライト、
	//アニメーションのフレーム数、
	//アニメーションの区画起点、
	//フレーム切り替えの時間間隔
	AnimationC(SpriteC* pSrite, int aniNum, int2D startRegion, int timeInter = 5,const char* defname = "defname");
	~AnimationC();

	void Init();
	void Stop();
	void Update();
	void End();
	void Play(bool isloop);
	void Pause();
	void RePlay(bool isloop = true);
	int GetTimeCount() { return timeCount; }
	const char* GetName() {return name;}
	bool GetPlayF();
	int GetFrameCount() { return frameCount; }
	int GetFrameCountForLoop() { return frameCount % textureRegionMax; }
private:
	char name[32];
	bool loopF;
	bool playF;
	int timeCount;
	int textureRegion;
	int textureRegionMax;
	int timeInterval;
	int frameCount;
	int aniID;
	int2D offRegion;
	SpriteC* sp;
};

class AnimationMove {
public:
	AnimationMove();
	virtual ~AnimationMove();

	virtual void Init() { timeCount = 0; };
	void Play() { playF = true; }
	void End() { playF = false; }
	void Stop() { playF = false; }
	virtual void Update()=0;

	bool GetPlayF() { return playF; }
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }
	int GetTime() { return timeCount; }
protected:
	bool playF;
	int timeCount;
	int timeMax;
	float targetX;
	float targetY;
	float startX;
	float startY;
	float posX;
	float posY;
	float speedX;
	float speedY;
	int moveType;
	int aniID;
};

class AnimationMoveStraight:public AnimationMove {
public:
	AnimationMoveStraight();
	AnimationMoveStraight(float stx, float sty, float tax, float tay, float speed,int type = 0);
	~AnimationMoveStraight();
	//moveType  0:終点に到達したら、動画終わり
	//moveType  1:放物線運動
	//moveType  2:減速直線運動
	void Init(float stx, float sty, float tax, float tay, float speed,int type = 0);
	//減速直線運動
	void Init(float stx, float sty, float tax, float tay, float speed, float js, int type = 2);
	void DecelerationMode(float redRatio);

	void Update()override;

	float GetSpeedX() { return speedX; }
	float GetSpeedY() { return speedY; }
private:
	float jsx;
	float jsy;
};

class AnimationMoveParabola :public AnimationMove{
public:
	AnimationMoveParabola();
	AnimationMoveParabola(float stx, float sty, float tax, float tay, float stSpeed,float vH, int type = 0);
	~AnimationMoveParabola();

	void Init(float stx, float sty, float tax, float tay, float stSpeed, float vH,int type = 0);
	void Update()override;

private:
	float gravity;
	float timeMaxf;
};

class AnimationMoveParabola_2 : public AnimationMove {
public:
	AnimationMoveParabola_2() {};
	~AnimationMoveParabola_2() {};

	void Init(float2D startpoint, float angle, float speed, float grav);
	void Update() override;
	float GetSpeedX() { return speedX; }
	float GetSpeedY() { return speedY; }
private:
	float gravity;
};

#endif // !BASE_ANIMATION_H


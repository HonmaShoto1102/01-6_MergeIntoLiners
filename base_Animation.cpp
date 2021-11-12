#include "base_Animation.h"
#include "GM.h"
#include <math.h>

AnimationC::AnimationC(SpriteC * pSrite, int aniNum, int2D startRegion, int timeInter, const char* defname)
{
	sp = pSrite;
	timeInterval = timeInter;
	timeCount = 0;
	textureRegion = 0;
	textureRegionMax = aniNum;
	playF = false;
	offRegion = startRegion;
	aniID = GM_AddAnimation(this);
	frameCount = 0;
	strcpy_s(name, defname);
}

AnimationC::~AnimationC()
{
	GM_UnAddAnimation(aniID);
}

void AnimationC::Init()
{
	timeCount = 0;
	textureRegion = 0;
	frameCount = 0;
}

void AnimationC::Stop()
{
	playF = false;
}

void AnimationC::Update()
{
	if (playF == false)return;

	timeCount++;
	if (timeCount < timeInterval)return;

	timeCount = 0;
	textureRegion++;
	frameCount++;
	if (textureRegion >= textureRegionMax) {
		textureRegion = 0;
		if (loopF == false) {
			playF = false;
			return;
		}
	}
	int regX = ((int)(offRegion.x + textureRegion)) % sp->GetRegionTotalX();
	int regY = ((int)(offRegion.y + textureRegion)) / sp->GetRegionTotalX() + (int)offRegion.y;
	sp->SetRegion(regX,regY);
}

void AnimationC::End()
{
	playF = false;
	timeCount = 0;
	textureRegion = 0;
	frameCount = 0;
}

void AnimationC::Play(bool isloop)
{
	loopF = isloop;
	playF = true;
	sp->SetRegion(offRegion.x, offRegion.y);
}

void AnimationC::Pause()
{
	playF = false;
}

void AnimationC::RePlay(bool isloop)
{
	loopF = isloop;
	playF = true;
}

bool AnimationC::GetPlayF()
{
	return playF;
}

//********************************************************
//********************移動アニメーション******************
//********************************************************

AnimationMove::AnimationMove()
{
	aniID = GM_AddMoveAni(this);
}

AnimationMove::~AnimationMove()
{
	GM_UnAddMoveAni(aniID);
}

//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
//直線移動アニメーション。＊＊＊＊＊＊＊＊＊＊＊
//＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
AnimationMoveStraight::AnimationMoveStraight()
{
	playF = false;
	timeCount = 0;
	timeMax = 0;
	targetX = targetY = startX = startY = 0;
	posX = posY = 0;
	speedX = speedY = 0;
	moveType = 0;
	jsx = jsy = 0;
}

AnimationMoveStraight::AnimationMoveStraight(float stx, float sty, float tax, float tay, float speed,int type)
{
	playF = false;
	startX = stx;
	startY = sty;
	targetX = tax;
	targetY = tay;
	posX = stx;
	posY = sty;
	float ofx = targetX - startX;
	float ofy = targetY - startY;
	float b = fabsf(ofx / ofy);
	speedY = sqrtf((speed * speed) / (1 + b * b));
	speedX = speedY * b;
	if (targetY < startY)speedY = -speedY;
	if (targetX < startX)speedX = -speedX;
	timeCount = 0;
	timeMax = (int)(fabsf((ofy / speedY))) + 1;
	moveType = type;
}

AnimationMoveStraight::~AnimationMoveStraight()
{
}

void AnimationMoveStraight::Init(float stx, float sty, float tax, float tay, float speed,int type)
{
	playF = false;
	startX = stx;
	startY = sty;
	targetX = tax;
	targetY = tay;
	posX = stx;
	posY = sty;
	float ofx = targetX - startX;
	float ofy = targetY - startY;
	float b = fabsf(ofx / ofy);
	speedY = sqrtf((speed * speed) / (1 + b * b));	
	speedX = speedY * b;
	if (targetY < startY)speedY = -speedY;
	if (targetX < startX)speedX = -speedX;
	timeCount = 0;
	moveType = type;
	timeMax = (int)(fabsf((ofy / speedY))) + 1;
}

void AnimationMoveStraight::Init(float stx, float sty, float tax, float tay, float speed, float js, int type)
{
	Init(stx, sty, tax, tay, speed, type);
	jsx = speedX * (js / speed);
	jsy = speedY * (js / speed);
}

void AnimationMoveStraight::DecelerationMode(float redRatio)
{
	if (moveType == 2)return;
	moveType = 2;
	jsx = speedX * redRatio;
	jsy = speedY * redRatio;
}


void AnimationMoveStraight::Update()
{
	if (playF == false)return;
	if (timeCount >= timeMax&&moveType == 0) {
		playF = false;
		return;
	}
	if (moveType == 2) {
		speedX -= jsx;
		speedY -= jsy;
		if (fabsf(speedX) <= 0.5f && fabsf(speedY) <= 0.5f) {
			playF = false;
		}
	}
	posX += speedX;
	posY += speedY;

	if (fabsf(posX - targetX) < 0.8f && fabsf(posY - targetY)<0.8f && moveType == 0) {
		posX = targetX;
		posY = targetY;
		playF = false;
		return;
	}
	timeCount++;
}



//放物線移動アニメーション

AnimationMoveParabola::AnimationMoveParabola()
{
	startX = 0;
	startY = 0;
	targetX = 0;
	targetY = 0;
	posX = 0;
	posY = 0;
	timeCount = 0;
	timeMaxf = 0.0f;
	timeMax = 0;	
	speedX =0;	
	speedX =0;
	speedY =0;
	gravity =0;
	moveType = 0;
}

AnimationMoveParabola::AnimationMoveParabola(float stx, float sty, float tax, float tay, float stSpeed,float vH, int type)
{
	startX = stx;
	startY = sty;
	targetX = tax;
	targetY = tay;
	posX = stx;
	posY = sty;
	float ofx = targetX - startX;
	float ofy = targetY - startY;
	timeCount = 0;
	timeMaxf = fabsf(ofx) / stSpeed;
	timeMax = (int)timeMaxf + 1;
	if (ofx >= 0) {
		speedX = stSpeed;
	}
	else {
		speedX = -stSpeed;
	}
	speedY = vH + ofy / timeMaxf;
	if (ofy > 0) {
		gravity = 2 * (ofy - speedY * timeMaxf) / (timeMaxf * timeMaxf);
	}
	else
	{
		gravity = 2 * (ofy - speedY * timeMaxf) / (timeMaxf * timeMaxf);
	}
	moveType = 0;
}

AnimationMoveParabola::~AnimationMoveParabola()
{
}

void AnimationMoveParabola::Init(float stx, float sty, float tax, float tay,float stSpeed, float vH,int type)
{
	startX = stx;
	startY = sty;
	targetX = tax;
	targetY = tay;
	posX = stx;
	posY = sty;
	float ofx = targetX - startX;
	float ofy = targetY - startY;
	timeCount = 0;
	timeMaxf = fabsf(ofx) / stSpeed;
	timeMax = (int)timeMaxf + 1;
	if (ofx >= 0) {
		speedX = stSpeed;
	}
	else {
		speedX = -stSpeed;
	}
	speedY = vH + ofy/timeMaxf;
	if (ofy > 0) {
		gravity = 2 * (ofy - speedY * timeMaxf) / (timeMaxf * timeMaxf);
	}
	else
	{
		gravity = 2 * (ofy - speedY * timeMaxf) / (timeMaxf * timeMaxf);
	}
	moveType = 0;
}


void AnimationMoveParabola::Update()
{
	if (playF == false)return;

	if (timeCount >= timeMaxf&&moveType==0) {
		playF = false;
		return;
	}
	float vHori = fabsf(speedY + timeCount * gravity);

	if (fabsf(targetX - posX) <= speedX * 0.5f&&fabsf(targetY - posY) <= vHori + 0.5f) {
		playF = false;
		posX = targetX;
		posY = targetY;
	}
	posX += speedX;
	posY = startY + speedY * timeCount + 0.5f*gravity*(timeCount*timeCount);

	timeCount++;
}


void AnimationMoveParabola_2::Init(float2D startpoint, float angle, float speed, float grav)
{
	startX = startpoint.x;
	startY = startpoint.y;
	//targetX = endpoint.x;
	//targetY = endpoint.y;
	posX = startpoint.x;
	posY = startpoint.y;
	gravity = grav;
	timeCount = 0;
	playF = false;
	
	speedX = speed * sinf(angle);
	speedY = -speed * cosf(angle);
}

void AnimationMoveParabola_2::Update()
{
	if (!playF)return;

	speedY += gravity;

	posX += speedX;
	posY += speedY;

	timeCount++;
}

#include "playerAction.h"
#include "PlayerData.h"
#include"config.h"
#include "GameScene.h"
//#define PI (3.141592653)


//ローカルプロトタイプ宣言
void AnimationChange_Update();
//void ReturnStandby();
void OneStickAni_Update();
//static playerDate Date;
void SetSpriteTranslucent(float alpha);


//static SpriteC* playerSprite;
static SpriteC* sprite_run;
static SpriteC* sprite_standby;
static SpriteC* sprite_onHeart;
static SpriteC* sprite_onAir;
static SpriteC* oneStick;
static SpriteC* sprite_goHeart;
static SpriteC* sprite_attck;
static SpriteC* sprite_backToOrigin;
static SpriteC* sprite_damege;
static SpriteC* sprite_dead;
//static SpriteC* sprite_falling;
static float oneStickAngle = 0;
static float oneStickRotateDir = 1;

static AnimationC* standbyAni;                            //立ち止まり
static AnimationC* moveAni;                               //移動
static AnimationC* airDownAni;                            //落下
static AnimationC* leaveHeartAni;                         //攻撃
static AnimationC* callVertica;                           //バティカ呼び出す
static AnimationC* callHolizy;                            //ホライジー呼び出す
static AnimationC* damegeAni;                             //ダメージ受け
static AnimationC* goHeartAni;                            //特異点に移動
static AnimationC* goHeartUpAni;                          //特異点に移動２
static AnimationC* heartRotate;                           //特異点に回る
static AnimationC* heartCallVertica;                      //特異点にバティカ呼び出す
static AnimationC* heartCallHolizy;                       //特異点にホライジー呼び出す
static AnimationC* backToOrigin;                          //原点に戻る
static AnimationC* deadAni;                               //倒された動画
//static AnimationC* attackAni;

static ANIe Now_aniState = ani_standby;
static ANIe Next_aniState = ani_standby;
static int actionTimeCount = 0;
static int actionTimeCountMax = 0;
static bool oneSticKModel = true;

void PlayerAction_Load()
{
	sprite_run = new SpriteC("Asset/playerAni/player_run_right.png");
	sprite_standby = new SpriteC("Asset/player_stand_right.png");
	sprite_onHeart = new SpriteC("Asset/playerAni/player_on_heart_right.png");
	sprite_onAir = new SpriteC("Asset/playerAni/player_falling_right.png");
	sprite_goHeart = new SpriteC("Asset/playerAni/player_go_heart_right.png");
	sprite_backToOrigin = new SpriteC("Asset/playerAni/player_after_attack_right.png");
	sprite_damege = new SpriteC("Asset/playerAni/player_damaged_right.png");
	//sprite_falling = new SpriteC("Asset/playerAni/player_falling_right.png");
	sprite_attck = new SpriteC("Asset/playerAni/player_attack_right.png");

	//playerSprite = new SpriteC("Asset/cs_player.png", "playerSprite");
	oneStick = new SpriteC("Asset/one_stick.png", "oneStick",13);
	sprite_dead = new SpriteC("Asset/player_down.png");
}

void PlayerAction_Init()
{
	oneStick->Init();
	oneStick->SetAnchorPoint(ANCHOR_RD);
	oneStick->SetScale(1.0f, 1.0f);
	oneStick->SetActive(false);

	sprite_run->Init();//1024x512
	sprite_run->SetAnchorPoint(ANCHOR_CENTER);
	sprite_run->SetCutSize(256, 256);
	sprite_run->SetScale(0.8f*PLAYER_WIDTH/128.0f, 0.8f*PLAYER_HEIGHT/192.0f);
	sprite_run->SetActive(false);

	sprite_standby->Init();//512x512
	sprite_standby->SetAnchorPoint(ANCHOR_CENTER);
	sprite_standby->SetScale(0.4f*PLAYER_WIDTH / 128.0f, 0.4f*PLAYER_HEIGHT / 192.0f);
	sprite_standby->SetActive(false);
	sprite_onHeart->Init();//1024x1024
	sprite_onHeart->SetAnchorPoint(ANCHOR_CENTER);
	//sprite_onHeart->SetScale(0.5f, 0.5f);
	sprite_onHeart->SetCutSize(256, 256);
	sprite_onHeart->SetSpriteSize(96.0f*PLAYER_WIDTH / 64.0f, 96.0f*PLAYER_HEIGHT / 96.0f);
	sprite_onHeart->SetActive(false);
	
	sprite_onAir->Init();//512x512
	sprite_onAir->SetAnchorPoint(ANCHOR_CENTER);
	sprite_onAir->SetCutSize(256, 256);
	sprite_onAir->SetSpriteSize(108 * PLAYER_WIDTH / 64.0f, 108 * PLAYER_HEIGHT / 96.0f);
	//sprite_onAir->SetScale(0.2f, 0.2f);
	sprite_onAir->SetActive(false);

	sprite_goHeart->Init();
	sprite_goHeart->SetAnchorPoint(ANCHOR_CENTER);
	sprite_goHeart->SetCutSize(256, 256);
	//playerGoHeart->SetWidth(64.0f);
	//playerGoHeart->SetHeight(96.0f)
	sprite_goHeart->SetSpriteSize(96.0f*PLAYER_WIDTH / 64.0f, 96.0f*PLAYER_HEIGHT / 96.0f);
	sprite_goHeart->SetActive(false);

	sprite_backToOrigin->Init();
	sprite_backToOrigin->SetAnchorPoint(ANCHOR_CENTER);
	sprite_backToOrigin->SetCutSize(256, 256);
	sprite_backToOrigin->SetSpriteSize(160 * PLAYER_WIDTH / 64.0f, 160 * PLAYER_HEIGHT / 96.0f);
	sprite_backToOrigin->SetActive(false);


	sprite_damege->Init();
	sprite_damege->SetCutSize(512, 512);
	sprite_damege->SetAnchorPoint(ANCHOR_CENTER);
	sprite_damege->SetScale(0.22f*PLAYER_WIDTH / 64.0f, 0.22f*PLAYER_HEIGHT / 96.0f);
	sprite_damege->SetActive(false);

	sprite_attck->Init();
	sprite_attck->SetAnchorPoint(ANCHOR_CENTER);
	sprite_attck->SetCutSize(256, 256);
	sprite_attck->SetSpriteSize(160 * PLAYER_WIDTH / 64.0f, 160 * PLAYER_HEIGHT / 96.0f);
	sprite_attck->SetActive(false);

	sprite_dead->Init();
	sprite_dead->SetAnchorPoint(ANCHOR_CENTER);
	sprite_dead->SetCutSize(512, 512);
	sprite_dead->SetSpriteSize(160 * PLAYER_WIDTH / 64.0f, 160 * PLAYER_HEIGHT / 96.0f);
	sprite_dead->SetActive(false);

	standbyAni = new AnimationC(sprite_standby, 1, { 0,0 },20);
	standbyAni->Play(true);
	moveAni = new AnimationC(sprite_run, 12, { 0,0 }, 3);
	airDownAni = new AnimationC(sprite_onAir, 10, { 0,0 },1);
	//moveAni->Play(true);
	leaveHeartAni = new AnimationC(sprite_attck, 11, { 0,0 }, 3);
	//attakAni->Play(true);
	//callVertica= new AnimationC(playerSprite, 3, { 0,3 }, 10);
	//callHolizy = new AnimationC(playerSprite, 3, { 0,3 }, 10);
	damegeAni = new AnimationC(sprite_damege, 25, { 0,0 }, 1);

	goHeartAni = new AnimationC(sprite_onAir, 1, { 0,0 }, 3);
	//goHeartUpAni = new AnimationC(playerSprite, 1, { 0,5 }, 10);
	heartRotate = new AnimationC(sprite_onHeart, 30, { 0,0 }, 4);
	//heartCallVertica = new AnimationC(playerSprite, 3, { 0,3 }, 10);
	//heartCallHolizy = new AnimationC(playerSprite, 3, { 0,3 }, 10);
	backToOrigin = new AnimationC(sprite_backToOrigin, 12, { 0,0 }, 3);
	deadAni = new AnimationC(sprite_dead, 60, { 0,0 }, 3);
	//attackAni = new AnimationC(sprite_attck, 11, { 0,0 }, 5);
}

void PlayerAction_Update()
{
	//playerSprite->SetPosition(posX, posY);
	OneStickAni_Update();
	AnimationChange_Update();

	if (Player_GetStrong()) {
		SetSpriteTranslucent(0.5f);
	}
	else {
		SetSpriteTranslucent(1.0f);
	}
	//ReturnStandby();
}

void PlayerAction_Final()
{
	delete deadAni;
	delete heartCallHolizy;
	delete heartCallVertica;
	delete heartRotate;
	delete goHeartUpAni;
	delete goHeartAni;
	delete damegeAni;
	delete callHolizy;
	delete callVertica;
	delete airDownAni;
	delete standbyAni;
	delete leaveHeartAni;
	delete moveAni;
	delete backToOrigin;
	//delete attackAni;

	delete sprite_dead;
	//delete playerSprite;
	delete oneStick;
	delete sprite_goHeart;
	delete sprite_backToOrigin;
	delete sprite_attck;
}

void PlayerAction_SetPosition(float x, float y)
{
	//playerSprite->SetPosition(x, y);
	sprite_run->SetPosition(x, y);
	sprite_onAir->SetPosition(x, y);
	sprite_onHeart->SetPosition(x, y);
	sprite_standby->SetPosition(x, y);
	sprite_goHeart->SetPosition(x, y);
	sprite_backToOrigin->SetPosition(x, y);
	sprite_damege->SetPosition(x, y);
	sprite_attck->SetPosition(x, y);
	sprite_dead->SetPosition(x, y);
}

void PlayerAction_SetDirction(int dirx, int diry)
{
	//playerSprite->SetSprteDirection(dirx, diry);
	sprite_run->SetSprteDirection(dirx, diry);
	sprite_onAir->SetSprteDirection(dirx, diry);
	sprite_onHeart->SetSprteDirection(dirx, diry);
	sprite_standby->SetSprteDirection(dirx, diry);
	sprite_goHeart->SetSprteDirection(dirx, diry);
	sprite_backToOrigin->SetSprteDirection(dirx, diry);
	sprite_damege->SetSprteDirection(dirx, diry);
	sprite_attck->SetSprteDirection(dirx, diry);
	sprite_dead->SetSprteDirection(dirx, diry);
}

void SetSpriteTranslucent(float alpha) {
	//playerSprite->SetAlpha(alpha);
	sprite_run->SetAlpha(alpha);
	sprite_onAir->SetAlpha(alpha);
	sprite_onHeart->SetAlpha(alpha);
	sprite_standby->SetAlpha(alpha);
	sprite_goHeart->SetAlpha(alpha);
	sprite_backToOrigin->SetAlpha(alpha);
	sprite_damege->SetAlpha(alpha);
	sprite_attck->SetAlpha(alpha);
}

void PlayerAction_SetAction(ANIe ani,int time)
{
	if (ani == Next_aniState)return;
	if (ani == ani_heartRotate) {
		oneSticKModel = true;
	}
	Next_aniState = ani;	

}

void PlayerAction_SetOneStickPos(float x, float y,int Dir)
{
	//oneStickAngle = PI * 0.5f;
	oneStickAngle = 0;
	oneStickRotateDir = (float)Dir;
	//playerSprite->SetSprteDirection(Dir, 1);
	oneStick->SetPosition(x, y);
	oneStick->SetAngle(oneStickAngle);
}

void PlayerAction_SetSpriteAngle(float anl)
{
	
	//playerSprite->SetAngle(anl);
}

float PlayerAction_GetOneStickAngle()
{
	return oneStickAngle;
}

void PlayerAction_SetOneStickAngle(float ang)
{
	oneStickAngle = ang;
	oneStick->SetAngle(oneStickAngle);
}

void PlayerAction_SetOneStickModel(bool b)
{
	oneSticKModel = b;
	oneStick->SetActive(b);
}

SpriteC * PlayerAction_GetOneStickSprite()
{
	return oneStick;
}





//**********************************ローカル関数********************************
void AnimationChange_Update() {
	if (Now_aniState == Next_aniState)return;
	
	switch (Now_aniState)
	{
	case ani_standby:
		sprite_standby->SetActive(false);
		standbyAni->End();
		break;
	case ani_move:
		sprite_run->SetActive(false);
		moveAni->End();
		break;
	case ani_airUp:
		break;
	case ani_airDown:
		sprite_onAir->SetActive(false);
		airDownAni->End();
		break;
	case ani_jumpGrund:
		break;
	case ani_jumpAir:
		break;
	case ani_callVertica:
		break;
	case ani_callHolizy:
		break;
	case ani_damege:
		sprite_damege->SetActive(false);
		damegeAni->End();
		break;
	case ani_goHeart:
		sprite_onAir->SetActive(false);
		goHeartAni->End();		
		break;
	case ani_goHeartUp:
		//playerSprite->SetActive(false);
		//goHeartUpAni->End();
		break;
	case ani_heartRotate:
		sprite_onHeart->SetActive(false);
		heartRotate->End();
		oneStick->SetActive(false);
		break;
	case ani_leaveHeart:
		sprite_attck->SetActive(false);
		leaveHeartAni->End();
		//playerSprite->SetAngle(0.0f);
		break;
	case ani_heartCallVertica:
		break;
	case ani_heartCallHolizy:
		break;
	case ani_backToOrigin:
		sprite_backToOrigin->SetActive(false);
		backToOrigin->End();
		break;
	case ani_heartBoxMove:
		break;
	case ani_dead:
		sprite_dead->SetActive(false);
		deadAni->End();
		break;
	default:
		break;
	}

	Now_aniState = Next_aniState;
	switch (Now_aniState)
	{
	case ani_standby:
		sprite_standby->SetActive(true);
		standbyAni->Init();
		standbyAni->Play(true);
		break;
	case ani_move:
		sprite_run->SetActive(true);
		moveAni->Init();
		moveAni->Play(true);
		//Next_aniState = ani_standby;
		break;
	case ani_airUp:
		break;
	case ani_airDown:
		sprite_onAir->SetActive(true);
		airDownAni->Init();
		airDownAni->Play(false);
		break;
	case ani_jumpGrund:
		break;
	case ani_jumpAir:
		break;
	case ani_callVertica:
		break;
	case ani_callHolizy:
		break;
	case ani_damege:
		sprite_damege->SetActive(true);
		damegeAni->Init();
		damegeAni->Play(false);
		break;
	case ani_goHeart:
		sprite_onAir->SetActive(true);
		goHeartAni->Init();
		goHeartAni->Play(true);
		break;
	case ani_goHeartUp:
		//playerSprite->SetActive(true);
		//goHeartUpAni->Init();
		//goHeartUpAni->Play(true);
		break;
	case ani_heartRotate:
		sprite_onHeart->SetActive(true);
		heartRotate->Init();
		heartRotate->Play(true);
		if(oneSticKModel)oneStick->SetActive(true);
		actionTimeCount = 0;
		break;
	case ani_leaveHeart:
		sprite_attck->SetActive(true);
		leaveHeartAni->Init();
		leaveHeartAni->Play(false);
		break;
	case ani_heartCallVertica:
		break;
	case ani_heartCallHolizy:
		break;
	case ani_backToOrigin:
		sprite_backToOrigin->SetActive(true);
		backToOrigin->Init();
		backToOrigin->Play(false);
		break;
	case ani_heartBoxMove:
		break;
	case ani_dead:
		sprite_dead->SetActive(true);
		deadAni->Init();
		deadAni->Play(false);
		break;
	default:
		break;
	}
}


void OneStickAni_Update() {
	if (Now_aniState == ani_heartRotate&&oneSticKModel) {
		oneStickAngle += (PI/45) * oneStickRotateDir;
		if (oneStickAngle > 2.5f * PI) {
			if (actionTimeCount % 10 > 5) {
				oneStick->SetActive(false);
			}
			else
			{
				oneStick->SetActive(true);
			}
		}
		oneStick->SetAngle(oneStickAngle);
	}
	actionTimeCount++;
}

#include "playerCollision.h"
//#include "testScene.h"
#include "playerAction.h"
#include "base_Animation.h"
#include "keyloger.h"

#include "uiDisplay.h"
#include "GM.h"
#include "Stage.h"
#include "typeLine.h"

//#include "testEnemy.h"
//#include "Fairy.h"

#include "Heart.h"
#include "PlayerData.h"
#include "Line.h"
#include "InputManager.h"
#include "FairyVH.h"
#include "Effect.h"
#include "Enemy.h"
#include "Map_Manager.h"
#include "SoundManager.h"
#include "MapCollision.h"
#include "playerEffect.h"
#include "SceneManager.h"

#define GRAVITY (0.5f)
#define ACC (0.5f)


//using namespace playerDate;
enum TOUCHDOWNe {
	touchDown_onGrund,
	touchDown_onAirUp,
	touchDown_onAirDown,
};



//プライバシー関数(ローカル関数)**********************************************
void Speed_Update();
void CollisionTrigger_Update();

void Default_Update();
void GoHeart_Update();
void GoHeartUp_Update();
void HeartRotate_Update();
void LeaveHeart_Update();
void BackToOrigin_Update();
void TakeDamegeEenemy_Update();
//void TakeDamegeBox_Update();
void Teleport_Update();
void heartBoxMove_Update();
void GoByLine_Update();
void Dead_Update();
void TransBoxMove_Update();
void TransBoxStand_Update();
void StageClear_Update();

//マップのインタラクト
void MapDamegeBoxCheck();
int MapCollisionBoxCheck();
void EnemyCollisionBoxCheck();

static float posX = 400;
static float posY = 500;
static float oldX = 400;
static float oldY = 500;
static float speed = PLAYER_SPEED;
static int Dir = 1;

static bool movingF = false;
static bool isReturn = false;
static float bulletTime = 1.0f;

static Heart* CurrentHeart;   //目標ハートポインター    
static CollisionRectangle heartBox;
//static CollisionRectangle testBox = {
//	-1000,200,2000,2
//};
//static SpriteC* testEnemy[3];
//static CollisionRectangle enemyBox[3];


//***************************************************************************
static AnimationMoveStraight* playStrAni;           //特異点に移動
static AnimationMoveStraight* playStrAniUp;         //特異点に登る
static AnimationMoveParabola_2* LeaveHeartMove;       //特異点から飛んでいく、
static AnimationMoveParabola* ToOriginMove;         //原点戻り
static AnimationMoveStraight* move_DamegeEnemy;     //敵からのダメージ受け移動
static float originPosX = 0;
static float originPosY = 0;

static TOUCHDOWNe touchDownSt = touchDown_onGrund;
static PL_STATEe collisionSt = ps_default;
static int heartRotateTime = 180;
static int teleportTime = 180;
static int transStageWatingTime = 20;
static int callVerticaTime = 120;
static int callHorizyTime = 120;
static int DeadCount = 300;
static CollisionRectangle playerCollision_body;
static CollisionRectangle LastMapBox;
static float speed_H = 0.0f;
static float speed_V = 0.0f;

//testCollision

//*********************************テスト用**********************************
void InputTest() {
	

	//***************************************test************************************
	if (keylogger_Trigger(KL_J)&&collisionSt == ps_heartRotate) {
		Player_SetState_GobyLine();//ラインに沿って移動する
	}

	if (keylogger_Trigger(KL_RIGHTSHIFT)&&GetKey_Attack()) {
		PlayerCollision_LeaveHeart();//ハートから飛んでいく
	}
	if (keylogger_Trigger(KL_U)&&GetKey_LineDir()) {
		if (collisionSt == ps_default) {
			Player_SetDamege(LIFT);
		}
	}

	if (keylogger_Press(KL_A) && GetKey_MoveA()) {
		PlayerCollision_InputA();
	}
	if (keylogger_Press(KL_D) && GetKey_MoveD()) {
		PlayerCollision_InputD();
	}

	//***************************************test************************************
}


void PlayerCollision_Load()
{
	//*********************************テスト用**********************************
	//heart = new SpriteC("Asset/heart.png", 7);
	
	//*********************************テスト用**********************************
	CurrentHeart = NULL;
}

void PlayerCollision_Init()
{
	//*********************************テスト用**********************************
	//heart->Init();
	//heart->SetAnchorPoint(ANCHOR_CENTER);
	//heart->SetScale(4.0f, 1.0f);
	//heart->SetPosition(800.0f, 400.0f);
	//heartBox.x = heart->GetPosX() - 32;
	//heartBox.y = heart->GetPosY() - 8;
	//heartBox.w = 64;
	//heartBox.h = 16;
	//heart->SetColor(100, 100, 100);
	LastMapBox = { 0,0,0,0 };
	
	DeadCount = 300;
	//*********************************テスト用**********************************
		//playerCollision_body.x = oldX - 8;
		//playerCollision_body.y = oldY - 16;
	playerCollision_body.w = PLAYER_WIDTH;
	playerCollision_body.h = PLAYER_HEIGHT;

	playStrAni = new AnimationMoveStraight();
	playStrAniUp = new AnimationMoveStraight();
	LeaveHeartMove = new AnimationMoveParabola_2();
	ToOriginMove = new AnimationMoveParabola();
	move_DamegeEnemy = new AnimationMoveStraight();
}

void PlayerCollision_Update()
{
	InputTest();
	Speed_Update();
	CollisionTrigger_Update();

	PlayerAction_SetPosition(oldX, oldY);
	if (GetCamera_Foucs() == cf_player) {
		GM_mainCamera()->SetFocusPos(oldX + 50 * Dir, oldY);
	}
}

void PlayerCollision_Final()
{
	delete playStrAni;
	playStrAni = NULL;
	delete playStrAniUp;
	playStrAniUp = NULL;
	delete LeaveHeartMove;
	LeaveHeartMove = NULL;
	delete ToOriginMove;
	ToOriginMove = NULL;
	//***************************************test************************************
	//delete heart;
	//heart = NULL;
	
	//***************************************test************************************
}
//--------------------------------------------------------------------------------
//------------------------------入力反応関数--------------------------------------
//--------------------------------------------------------------------------------
//ハートに行く（触発）
void PlayerCollision_ToHeart()
{
	//if (strAniPlayF)return;
	if (Heart_GetFlag()==false)return;   //ハートがあるかないか
	if (collisionSt != ps_default && collisionSt!= ps_heartRotate&&collisionSt!= ps_teleport)return;//Playerの状態判断
	//Heart ht;
	CurrentHeart = Heart_GetHeart();           //存在するハートを取得。
	//playStrAni.Init(oldX, oldY, x, y, 15.0f);
	if (CurrentHeart->sp->GetActive()) {
		if (Heart_isEndHeart()&&CurrentHeart->ht == Diagonal) {
			playStrAni->Init(oldX, oldY, CurrentHeart->sp->GetPosX(), CurrentHeart->sp->GetPosY() - PLAYER_HEIGHT / 2, 30.0f,1);//移動動画を初期化
		}
		else
		{
			playStrAni->Init(oldX, oldY, CurrentHeart->sp->GetPosX(), CurrentHeart->sp->GetPosY() - PLAYER_HEIGHT / 2, 30.0f);//移動動画を初期化
		}
		
		if (CurrentHeart->sp->GetPosX() > oldX)Dir = 1;
		if (CurrentHeart->sp->GetPosX() < oldX)Dir = -1;
		PlayerAction_SetDirction(Dir, 1);    //終点と起点に比較、方向を設定
		playStrAni->Play();                  //移動動画再生

		if (collisionSt == ps_default) {
			originPosX = oldX;                   //原点を記録
			originPosY = oldY;
		}		
		collisionSt = ps_goHeart;            //ハート行く状態になる
		PlayerAction_SetAction(ani_goHeart); //ハート行くのアニメーションに変更
		SetCamera_Foucs(cf_player);
		GM_mainCamera()->SetFocusLens(1.3f);
	}
	SoundManager_PlaySE(SL_player_to_heart);
}
//ハートから飛んでいく（触発）
void PlayerCollision_LeaveHeart()
{
	if (collisionSt != ps_heartRotate)return;    //playerの状態判断
	float ang = PlayerAction_GetOneStickAngle(); //"1"の目指す方向を取得。
	PlayerAction_SetSpriteAngle(ang);            //playerのスプライトの方向変更
	float pX = CurrentHeart->sp->GetPosX();
	float pY = CurrentHeart->sp->GetPosY();
	float ptx = sinf(ang) + pX;
	float pty = -cosf(ang) + pY;
	if (pX > ptx)Dir = -1;
	if (pX < ptx)Dir = 1;
	PlayerAction_SetDirction(Dir, 1);    //終点と起点に比較、方向を設定
	LeaveHeartMove->Init({ pX, pY }, ang, 30.0f, 0.6f);//飛んでいく移動動画を初期化
	LeaveHeartMove->Play();
	PlayerAction_SetAction(ani_leaveHeart);       //飛んでいくアニメーションに切り替え
	collisionSt = ps_leaveHeart;                //飛んでいく状態になる
	//heart->SetActive(false);
	Line_DeleteLineAll();
	Heart_ReSet();
	GM_mainCamera()->SetFocusLens(1.0f);
	
	UI_AttackFromHeart();             //敵の当たりUIを呼び出す
	//Heart_HeartDestory(0);               //ハットを消す
	SoundManager_PlaySE(SL_player_attack);
}

void PlayerCollision_CallVertica() {
	if (collisionSt == ps_default) {
		//collisionSt = ps_callVertica;
		callVerticaTime = 120;
	}
	if (collisionSt == ps_heartRotate) {
		//collisionSt = ps_callVerticaOnHeart;
		callVerticaTime = 120;
	}
}

void PlayerCollision_CallHorizy() {
	if (collisionSt == ps_default) {
		//collisionSt = ps_callHorizy;
		callHorizyTime = 120;
	}
	if (collisionSt == ps_heartRotate) {
		//collisionSt = ps_callHorizyOnHeart;
		callHorizyTime = 120;
	}
}

void PlayerCollision_StageClear(float x,float y)
{
	playStrAni->Init(oldX, oldY, x, y, 30.0f);
	if (x > oldX)Dir = 1;
	if (x < oldX)Dir = -1;
	PlayerAction_SetDirction(Dir, 1);    //終点と起点に比較、方向を設定
	playStrAni->Play();                  //移動動画再生
	collisionSt = ps_transBoxMove;       //ハート行く状態になる
	PlayerAction_SetAction(ani_goHeart); //ハート行くのアニメーションに変更
}

//----------------------------------------------------------------------------------

CollisionRectangle PlayerCollision_GetCollision()
{
	playerCollision_body.x = posX - PLAYER_WIDTH/2;
	playerCollision_body.y = posY - PLAYER_HEIGHT/2;
	return playerCollision_body;
}

CollisionRectangle PlayerCollision_GetOldCollision()
{
	playerCollision_body.x = oldX - PLAYER_WIDTH/2;
	playerCollision_body.y = oldY - PLAYER_HEIGHT/2;
	return playerCollision_body;
}

//原点に戻った時、trueを戻る
bool Player_isReturn()
{
	if (isReturn == false) {
		return false;
	}
	return true;
}

void Player_SetReturn(bool Re)
{
	isReturn = Re;
}

float Player_GetBulletTime()
{
	return bulletTime;
}

PL_DIR Player_GetDirection()
{
	if (Dir == 1)return RIGHT;
	if (Dir == -1)return LIFT;
	return RIGHT;
}

PL_STATEe Player_GetState()
{
	return collisionSt;
}




float Player_GetPosX()
{
	return oldX;
}

float Player_GetPosY()
{
	return oldY;
}

PL_DIR Player_OnStackDir()
{
	float an = PlayerAction_GetOneStickAngle();
	if (sinf(an) >= 0) {
		return RIGHT;
	}
	else {
		return LIFT;
	}
	return PL_DIR();
}
float Player_GetOnStackAngle()
{
	return PlayerAction_GetOneStickAngle();
}
float2D Player_GetHeartPos()
{
	float2D po = { CurrentHeart->sp->GetPosX(),CurrentHeart->sp->GetPosY() };
	return po;
}
SpriteC * Player_GetOneStickSprite()
{
	return PlayerAction_GetOneStickSprite();
}
void SetAreaport(float x, float y)
{
	playStrAni->Init(oldX, oldY, x, y, 30.0f);
	if (x > oldX)Dir = 1;
	if (x < oldX)Dir = -1;
	PlayerAction_SetDirction(Dir, 1);    //終点と起点に比較、方向を設定
	playStrAni->Play();                  //移動動画再生
	collisionSt = ps_transBoxMove;            //ハート行く状態になる
	PlayerAction_SetAction(ani_goHeart); //ハート行くのアニメーションに変更

}
void SetTeleport(float x, float y)
{
	playStrAni->Init(oldX, oldY, x, y, 30.0f);
	if (x > oldX)Dir = 1;
	if (x < oldX)Dir = -1;
	PlayerAction_SetDirction(Dir, 1);    //終点と起点に比較、方向を設定
	playStrAni->Play();                  //移動動画再生
	collisionSt = ps_heartBoxMove;            //ハート行く状態になる
	PlayerAction_SetAction(ani_heartBoxMove); //ハート行くのアニメーションに変更
	ActivateEffect("effect_to_heart_box", { oldX,oldY }, { 1.0f,1.0f });
	SoundManager_PlaySE(SL_player_telepote);
}
void Player_SetDamege(int dir)
{
	//ダメージ受け判断
	Dir = dir;
	collisionSt = ps_takeDamege_enemy;
	move_DamegeEnemy->Init(oldX, oldY, oldX - Dir * 50, oldY-200.0f,20.0f);
	move_DamegeEnemy->Play();
	PlayerAction_SetDirction(Dir,1);
	PlayerAction_SetAction(ani_damege);
}
void Player_SetState_backToOrigin(float x, float y)
{
	Heart_MoveFigure(x, y);
	collisionSt = ps_backToOrigin;   //原点に戻る状態になる
	speed_H = 0;               //重力影響初期化
	PlayerAction_SetAction(ani_backToOrigin);//原点に戻るアニメーションに切り替え
	ToOriginMove->Init(posX, posY, originPosX, originPosY, 28.0f, -15.0f, 1);//移動動画初期化
	ToOriginMove->Play();
	//UI_ReturnToOrigineAfterAttack(testEnemy[0]);   //UIの処理触発

}
//ラインに沿って移動する
void Player_SetState_GobyLine()
{
	//if (strAniPlayF)return;
	//if (Heart_GetFlag() == false)return;   //ハートがあるかないか
	if (collisionSt != ps_heartRotate && collisionSt != ps_default)return;//Playerの状態判断
	//Heart ht;
	if (Heart_isEndHeart()) {
		if (CurrentHeart->ht == RightAngle)return;
		LINE* line = Line_GetEndLine();
		playStrAni->Init(oldX, oldY, line->currentEpos.x, line->currentEpos.y - PLAYER_HEIGHT / 2, 30.0f);
		if (line->endPos.x > oldX)Dir = 1;
		if (line->endPos.x < oldX)Dir = -1;
		PlayerAction_SetDirction(Dir, 1);    //終点と起点に比較、方向を設定
		playStrAni->Play();                  //移動動画再生
		float osAngle = atan2f((line->currentEpos.y - oldY),(line->currentEpos.x - oldX));
		PlayerAction_SetOneStickAngle(osAngle + PI/2);

		collisionSt = ps_goByLine;            //ハート行く状態になる
		PlayerAction_SetAction(ani_goHeart); //ハート行くのアニメーションに変更
		SetCamera_Foucs(cf_player);
		GM_mainCamera()->SetFocusLens(1.3f);

		CurrentHeart = Heart_GetHeart();
	}
	else {
		CurrentHeart = Heart_GetHeart();
		playStrAni->Init(oldX, oldY, CurrentHeart->sp->GetPosX(), CurrentHeart->sp->GetPosY() - PLAYER_HEIGHT / 2, 30.0f);//移動動画を初期化
		//存在するハートを取得。
	//playStrAni.Init(oldX, oldY, x, y, 15.0f);
		if (CurrentHeart->sp->GetActive()) {
			
			if (CurrentHeart->sp->GetPosX() > oldX)Dir = 1;
			if (CurrentHeart->sp->GetPosX() < oldX)Dir = -1;
			PlayerAction_SetDirction(Dir, 1);    //終点と起点に比較、方向を設定
			playStrAni->Play();                  //移動動画再生

			//if (collisionSt == ps_default) {
			//	originPosX = oldX;                   //原点を記録
			//	originPosY = oldY;
			//}
			collisionSt = ps_goByLine;            //ハート行く状態になる
			PlayerAction_SetAction(ani_goHeart); //ハート行くのアニメーションに変更
			SetCamera_Foucs(cf_player);
			GM_mainCamera()->SetFocusLens(1.3f);
		}
	}
	
}
void Player_SetState_Dead()
{
	collisionSt = ps_dead;
	PlayerAction_SetAction(ani_dead);
	SoundManager_StopBGM();
	SoundManager_PlaySE(SL_game_over);
	DeadCount = 300;
}

void Player_PositionReSet(float x, float y)
{
	posX = x;
	posY = y;
	speed_H = 0;
	speed_V = 0;
	collisionSt = ps_default;
	GM_mainCamera()->SetPos(posX,posY);
}
//左に移動
void PlayerCollision_InputA()
{
	if (collisionSt != ps_default)return;
	if (speed_V > 0)speed_V = 0;
	speed_V -= ACC;
	if (speed_V <= -speed) {
		speed_V = -speed;
	}
	//posX += speedHorizy;
	if (speed_V < 0) {
		Dir = -1;
	}
	else {
		Dir = 1;
	}
	PlayerAction_SetDirction(Dir, 1);
	PlayerAction_SetAction(ani_move);
	movingF = true;
}

//右に移動
void PlayerCollision_InputD()
{
	if (collisionSt != ps_default)return;
	if (speed_V < 0)speed_V = 0;
	speed_V += ACC;
	if (speed_V >= speed) {
		speed_V = speed;
	}
	//posX += speedHorizy;
	if (speed_V < 0) {
		Dir = -1;
	}
	else {
		Dir = 1;
	}
	PlayerAction_SetDirction(Dir, 1);
	PlayerAction_SetAction(ani_move);
	movingF = true;
}


//******************ローカル関数********************************

//重力処理
void Speed_Update() {
	if (speed_H == 0) {
		speed_H += 6.5f;
	}
	else {
		speed_H += GRAVITY;
	}	
	if (speed_H >= 20.0f)speed_H = 20.0f;
	//PlayerAction_SetPosition(oldX, oldY);
	//oldX = posX;
	//oldY = posY;
}


//状態によって、Update処理
void CollisionTrigger_Update() {

	switch (collisionSt)
	{
	case ps_default:
		Default_Update();
		break;
	case ps_goHeart:
		GoHeart_Update();
		break;
	case ps_goHeartUp:
		GoHeartUp_Update();
		break;
	case ps_heartRotate:
		HeartRotate_Update();
		break;
	case ps_leaveHeart:
		bulletTime = 0;
		LeaveHeart_Update();
		break;
	case ps_backToOrigin:
		BackToOrigin_Update();
		break;
	case ps_takeDamege_box:
		//TakeDamegeBox_Update();
		break;
	case ps_takeDamege_enemy:
		TakeDamegeEenemy_Update();
		break;
	case ps_teleport:
		Teleport_Update();
		break;
	case ps_heartBoxMove:
		heartBoxMove_Update();
		break;
	case ps_goByLine:
		GoByLine_Update();
		break;
	case ps_transBoxMove:
		TransBoxMove_Update();
		break;
	case ps_transBoxStand:
		TransBoxStand_Update();
		break;
	case ps_stageClear:
		StageClear_Update();
		break;
	case ps_dead:
		Dead_Update();
		break;
	default:
		break;
	}


	oldX = posX;    //位置更新
	oldY = posY;
	if (speed_V > 0&&!movingF) {
		speed_V -= ACC;
		if (speed_V < 0)speed_V = 0;
	}
	else if (speed_V < 0&&!movingF) {
		speed_V += ACC;
		if (speed_V > 0)speed_V = 0;
	}

	movingF = false;
}

//デフォルト状態update
void Default_Update() {

	posY += speed_H;
	posX += speed_V;
	
	MapCollisionBoxCheck();
	/*int bo = CollsiionWithMap(&coll.x, &coll.y, oldl.x, oldl.y, coll);
	if (bo == 1 || bo == 3) {
		speed_H = 0;
	}
	posX = coll.x + coll.w / 2;
	posY = coll.y + coll.h / 2;*/


	MapDamegeBoxCheck();
	PlayerCollision_ToHeart();
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	
	

	if (speed_H < 0) {                       //playerが上昇する時、
		touchDownSt = touchDown_onAirUp;
		PlayerAction_SetAction(ani_airUp);        //上昇動画再生
	}
	else if (speed_H > 0) {
		touchDownSt = touchDown_onAirDown;
		PlayerAction_SetAction(ani_airDown);       //落下動画再生
	}
	
}

//ハートに行く
void GoHeart_Update() {

	if (playStrAni->GetPlayF()) {
		//playStrAni->Update();
		posX = playStrAni->GetPosX();       //Player位置更新
		posY = playStrAni->GetPosY();	
	}

	//**************************************************************************************
	//マップとの当たり判定
	/*CollisionRectangle coll = { 0,0,0,0 };
	CollisionRectangle oldC = { oldX - 32,oldY - 48,64,96 };
	coll.x = posX - 32;
	coll.y = posY - 48;
	coll.w = 64;
	coll.h = 96;

	int boxCount = Stage_GetNumberOfBlock(bl_collisionBox);
	for (int i = 0; i < boxCount; i++)
	{
		M_collsionBOX* cbox = Stage_collisionBOX_hit(&coll, i);
		if (cbox == NULL) continue;
		collisionSt = ps_default;
		if (oldC.y + oldC.h <= cbox->GetColl().y) {
			posY = cbox->GetColl().y - 48;
			speedVertical = 0;
			if (movingF == false) {
				PlayerAction_SetAction(ani_standby);
			}
			continue;
		}

		if (oldC.y >= cbox->GetColl().y + cbox->GetColl().h) {
			posY = cbox->GetColl().y + 48;
			speedVertical = 0;
			continue;
		}

		if (oldC.x + oldC.w <= cbox->GetColl().x) {
			posX = cbox->GetColl().x - 33;
			speedVertical = 0;
			continue;
		}

		if (oldC.x >= cbox->GetColl().x + cbox->GetColl().w) {
			posX = cbox->GetColl().x + cbox->GetColl().w + 33;
			speedVertical = 0;
			continue;
		}
	}*/
	
	if (playStrAni->GetPlayF() == false) {  //動画再生終わったら（終点ハートに到達）
		speed_H = 0;
		//playerCollision_body.x = oldX - 64;
		//playerCollision_body.y = oldY - 96;

		if (CurrentHeart != NULL) {
			heartBox.x = CurrentHeart->sp->GetPosX() - 32;
			heartBox.y = CurrentHeart->sp->GetPosY() - 8;
			heartBox.w = 64;
			heartBox.h = 64;
			//playerとハートに当たり判定をして、
			if (CurrentHeart->ht == RightAngle) {
				//if (Collision_RectangleAndRectangleHit(&playerCollision_body, &heartBox)) {
					collisionSt = ps_heartRotate;//ハートに登る状態になる
					//playStrAniUp->Init(oldX, oldY, CurrentHeart->sp->GetPosX(), CurrentHeart->sp->GetPosY() - 56, 4);//ハートに登る移動動画初期化
					//playStrAniUp->Play();
					//Heart_CreateFigure();
					SoundManager_PlaySE(SL_heart_shiny);
					PlayerAction_SetAction(ani_heartRotate);//ハート登るアニメーションに切り替え
					PlayerAction_SetOneStickPos(CurrentHeart->sp->GetPosX(), CurrentHeart->sp->GetPosY(), Dir);//”１”の位置を設定
					heartRotateTime = 1800;        //回転時間初期化
				//}
			}
			else if (CurrentHeart->ht == Diagonal) {
				collisionSt = ps_default;
				PlayerCollision_ToHeart();
			}
		}
		
		
		
	}

	if (GO_HEART_COLLISION_OFF)return;
	int b = MapCollisionBoxCheck();
	if (b) {
		collisionSt = ps_default;
		Line_DeleteLineAll();
		Heart_ReSet();
	}
}
//ハート登る
void GoHeartUp_Update() {
	if (playStrAniUp->GetPlayF()) {
		//playStrAniUp->Update();
		posX = playStrAniUp->GetPosX();//位置更新
		posY = playStrAniUp->GetPosY();
		
	}
	if (playStrAniUp->GetPlayF() == false) {
		PlayerAction_SetAction(ani_heartRotate);//"1"回転時のアニメーションに切り替え
		PlayerAction_SetOneStickPos(CurrentHeart->sp->GetPosX(), CurrentHeart->sp->GetPosY(), Dir);//”１”の位置を設定
		collisionSt = ps_heartRotate;  //"1"回転状態になる
		heartRotateTime = 180;        //回転時間初期化
	}
}
//"1"回転ときのUpdate処理
void HeartRotate_Update() {

	
	bulletTime = 1;
	if (heartRotateTime <= 0||CurrentHeart->sp->GetActive()==false) {//時間が終わったら、デフォルト状態に戻る
		collisionSt = ps_default;
		heartRotateTime = 0;
		speed_H = 0;
		bulletTime = 0;
		Line_DeleteLineAll();
		Heart_ReSet();
		//canInput = true;
		//CurrentHeart->sp->SetActive(false);//ハートを隠す
	}
	//if (FairyVH_GetStateH() == fs_stand && FairyVH_GetStateV() == fs_stand) {
		heartRotateTime--;
	//}

	PlayerCollision_ToHeart();
}
//ハートから飛んでいくUpdate処理
void LeaveHeart_Update() {
	if (LeaveHeartMove->GetPlayF()) {
		//LeaveHeartMove->Update();
		if (LeaveHeartMove->GetTime() >= 300) {
			//LeaveHeartMove->DecelerationMode(0.015f);
			speed_V = LeaveHeartMove->GetSpeedX();
			speed_H = LeaveHeartMove->GetSpeedY();
			LeaveHeartMove->End();
			collisionSt = ps_default;
		}
		else
		{
			speed_V = 0;
			speed_H = 0;
			posX += LeaveHeartMove->GetSpeedX();//位置更新
		    posY += LeaveHeartMove->GetSpeedY();
		}		
		posY += speed_H;
		posX += speed_V;

	}
	CollisionRectangle coll = PlayerCollision_GetCollision();
	CollisionRectangle oldC = PlayerCollision_GetOldCollision();
//********************敵との当たり判定**************************************************

	//CollisionRectangle enBox = testEnemy_GetCollision();
	

	int mirrCount = Stage_GetNumberOfBlock(bl_mirrorBox);
	for (int i = 0; i < mirrCount; i++)
	{
		M_mirorrBox* mirB = Stage_GetMirrorBox_byNumber(i);
		CollisionRectangle cr_m = mirB->GetColl();
		if (mirB != NULL) {
			if (Collision_RectangleAndRectangleHit(&coll, &cr_m)) {
				collisionSt = ps_backToOrigin;
				speed_H = 0;
				PlayerAction_SetAction(ani_backToOrigin);
				ToOriginMove->Init(posX, posY, originPosX, originPosY, 28.0f, -15.0f, 1);
				ToOriginMove->Play();
				mirB->SetMirorrRotate();
			}
		}
	}
//**************************************************************************************
	//マップとの当たり判定
	/*int boxCount = Stage_GetNumberOfBlock(bl_collisionBox);
	for (int i = 0; i < boxCount; i++)
	{
		M_collsionBOX* cbox = Stage_collisionBOX_hit(&coll, i);
		if (cbox == NULL) continue;
		collisionSt = ps_default;
		if (oldC.y + oldC.h <= cbox->GetColl().y) {
			posY = cbox->GetColl().y - 48;
			speed_H = 0;
			if (movingF == false) {
				PlayerAction_SetAction(ani_standby);
			}
			continue;
		}

		if (oldC.y >= cbox->GetColl().y + cbox->GetColl().h) {
			posY = cbox->GetColl().y + 48;
			speed_H = 0;
			continue;
		}

		if (oldC.x + oldC.w <= cbox->GetColl().x) {
			posX = cbox->GetColl().x - 33;
			speed_H = 0;
			continue;
		}

		if (oldC.x >= cbox->GetColl().x + cbox->GetColl().w) {
			posX = cbox->GetColl().x + cbox->GetColl().w + 33;
			speed_H = 0;
			continue;
		}
	}*/
	int b = MapCollisionBoxCheck();
	if (b)collisionSt = ps_default;

	MapDamegeBoxCheck();
}
//原点に戻る処理
void BackToOrigin_Update() {

	if (ToOriginMove->GetPlayF()) {
		//ToOriginMove->Update();
		posX = ToOriginMove->GetPosX();//位置更新
		posY = ToOriginMove->GetPosY();
		isReturn = false;
		

		
	}
	if (ToOriginMove->GetPlayF() == false) {//着地してから、デフォルト状態になる
		collisionSt = ps_default;
		//canInput = true;
		isReturn = true;    //着地戻り値がtrueになる
	}
}


void TakeDamegeEenemy_Update() {

	posY += speed_H;
	//posX += speed_V;
	if (move_DamegeEnemy->GetPlayF()) {
		posX += move_DamegeEnemy->GetSpeedX();		
	}
	if (!move_DamegeEnemy->GetPlayF()) {
		collisionSt = ps_default;
	}
	//MapDamegeBoxCheck();
	MapCollisionBoxCheck();
}

void Teleport_Update() {

	if (teleportTime <= 0) {
		teleportTime = 0;
		collisionSt = ps_default;
		speed_H = 0;
		Line_DeleteLineAll();
		Heart_ReSet();
	}

	if (FairyVH_GetStateH(0) == fs_stand && FairyVH_GetStateV(0) == fs_stand) {
		teleportTime--;
	}

	if (collisionSt == ps_teleport && keylogger_Trigger(KL_D)) {
		Dir = 1;
		PlayerAction_SetDirction(Dir, 1);
		FairyVH_SetFairyDirH(Dir);
	}
	if (collisionSt == ps_teleport && keylogger_Trigger(KL_A)) {
		Dir = -1;
		PlayerAction_SetDirction(Dir, 1);
		FairyVH_SetFairyDirH(Dir);
	}

	PlayerCollision_ToHeart();
}

void heartBoxMove_Update() {
	if (playStrAni->GetPlayF()) {
		//playStrAni->Update();
		posX = playStrAni->GetPosX();       //Player位置更新
		posY = playStrAni->GetPosY();
	}

	if (playStrAni->GetPlayF() == false) {
		int hb = Stage_GetNumberOfBlock(bl_heartBox);
		for (int i = 0; i < hb; i++)
		{
			M_heartBox* hbx = Stage_heartBox_hitWithPoint(posX, posY, i);
			if (hbx != NULL) {
				collisionSt = ps_teleport;
				PlayerAction_SetAction(ani_heartRotate);
				PlayerAction_SetOneStickModel(false);
				teleportTime = 180;

				Line_DeleteLineAll();
				Heart_ReSet();
				ActivateEffect("effect_on_heart_box", { oldX,oldY }, { 1.0f,1.0f });
			}
		}
	}
}

void MapDamegeBoxCheck() {
	int dbC = Stage_GetNumberOfBlock(bl_damegeBox);
	CollisionRectangle co = PlayerCollision_GetCollision();
	for (int i = 0; i < dbC; i++)
	{
		
		M_damegeBox* dbox = Stage_damegeBox_hit(co, i);
		if (dbox != NULL) {
			if (posX > (LastMapBox.w/2 + LastMapBox.x)) {
				posX = LastMapBox.w + LastMapBox.x - co.w;
				posY = LastMapBox.y - (co.h / 2);
			}
			else {
				posX = LastMapBox.x + co.w;
				posY = LastMapBox.y - (co.h / 2);
			}
		}
	}

	float bian = GM_mainCamera()->GetBoundrayBottem();
	if (posY > bian + 400) {
		if (posX > (LastMapBox.w / 2 + LastMapBox.x)) {
			posX = LastMapBox.w + LastMapBox.x - co.w;
			posY = LastMapBox.y - (co.h / 2);
		}
		else {
			posX = LastMapBox.x + co.w;
			posY = LastMapBox.y - (co.h / 2);
		}
	}
}

int MapCollisionBoxCheck() {
	//**********************************マップと当たり判定*************************************
	//int texBoxCount = Stage_GetNumberOfBlock(bl_textureBox);
	//for (int i = 0; i < texBoxCount; i++)
	//{
	//	M_textureBOX* tbox = Stage_textureBOX_hit(&coll, i);
	//	if (tbox != NULL) {
	//		tbox->Play();
	//	}
	//}
	int RetureType = 0;

	CollisionRectangle coll = PlayerCollision_GetCollision();
	CollisionRectangle oldC = PlayerCollision_GetOldCollision();


	

	
	//マップとの当たり判定
	int boxCount = Stage_GetNumberOfBlock(bl_collisionBox);
	for (int i = 0; i < boxCount; i++)
	{
		M_collsionBOX* cbox = Stage_collisionBOX_hit(&coll, i);
		if (cbox == NULL) continue;
		if (oldC.y + oldC.h <= cbox->GetColl().y) {
			posY = cbox->GetColl().y - PLAYER_HEIGHT/2 - 1;
			speed_H = 0;
			if (movingF == false&& collisionSt == ps_default) {                  //移動ボタン押さないと待機状態
				PlayerAction_SetAction(ani_standby);
			}
			LastMapBox = cbox->GetColl();
			RetureType = 1;
			continue;
		}

		if (oldC.y >= cbox->GetColl().y + cbox->GetColl().h) {
			posY = cbox->GetColl().y + cbox->GetColl().h + PLAYER_HEIGHT / 2;
			speed_H = 0;
			RetureType = 1;
			continue;
		}

		if (oldC.x + oldC.w <= cbox->GetColl().x) {
			posX = cbox->GetColl().x - PLAYER_WIDTH/2 -1;
			RetureType = 1;
			continue;
		}

		if (oldC.x >= cbox->GetColl().x + cbox->GetColl().w-2) {
			posX = cbox->GetColl().x + cbox->GetColl().w -2 + PLAYER_WIDTH / 2 +1;
			RetureType = 1;
			continue;
		}
	}


	/*int StCount = Stage_GetNumberOfBlock(bl_stageTransBox);
	for (int i = 0; i < StCount; i++)
	{
		M_stageTransBox* stb = Stage_transBox_hit(&oldC, i);
		if (stb != NULL) {
			MapManager_StageTrans(stb->GetNextName());		
		}
	}*/

	coll = PlayerCollision_GetCollision();
	//斜めの地面との当たり判定*******************************************
	int DiCount = Stage_GetNumberOfBlock(bl_diagonalBox);
	for (int i = 0; i < DiCount; i++)
	{
		M_diagonalCollisionBox* dib = Stage_diagonalBox_byNumber(i);
		if (dib != NULL) {
			LineStraightC* hill = dib->GetDiaLine();

			CollisionLine botl = { coll.x,coll.y + coll.h,coll.x + coll.w +2,coll.y + coll.h };
			CollisionLine hillline = hill->GetLine();
			Cross_imf cr = Collision_LineAndLineHit(botl, hillline);
			if (cr.flag) {
				float Y1, Y2;
				hill->GetY_formX(&Y1, botl.sx);
				hill->GetY_formX(&Y2, botl.ex);
				float minSEy = min(hillline.sy, hillline.ey);
				float maxSEy = max(hillline.sy, hillline.ey);
				if (Y1 > maxSEy) {
					Y1 = maxSEy;
				}
				if (Y2 < minSEy) {
					Y2 = minSEy;
				}

				float offY1 = botl.sy - Y1;
				float offY2 = botl.ey - Y2;
				float MaxY = max(offY1, offY2);
				posY -= MaxY;
				speed_H = 0;
				if (movingF == false && collisionSt == ps_default) {                  //移動ボタン押さないと待機状態
					PlayerAction_SetAction(ani_standby);
				}
				RetureType = 1;
			}
		}
	}

	

	return RetureType;
}

void EnemyCollisionBoxCheck()
{
	/*Game* gameSc;
	gameSc->GetEnemies();
	std::vector<Enemy*> enes = gameSc->GetEnemies();
	for (size_t i = 0; i < enes.size(); i++)
	{
		
	}*/
}

void GoByLine_Update() {
	if (playStrAni->GetPlayF()) {
		//playStrAni->Update();
		posX = playStrAni->GetPosX();       //Player位置更新
		posY = playStrAni->GetPosY();
	}

	if (playStrAni->GetPlayF() == false) {  //動画再生終わったら（終点ハートに到達）
		speed_H = 0;
		//playerCollision_body.x = oldX - 64;
		//playerCollision_body.y = oldY - 96;

		if (CurrentHeart != NULL&&CurrentHeart->active) {
			heartBox.x = CurrentHeart->sp->GetPosX() - 32;
			heartBox.y = CurrentHeart->sp->GetPosY() - 8;
			heartBox.w = 64;
			heartBox.h = 64;
			//playerとハートに当たり判定をして、
			if (CurrentHeart->ht == RightAngle) {
				//if (Collision_RectangleAndRectangleHit(&playerCollision_body, &heartBox)) {
				collisionSt = ps_heartRotate;//ハートに登る状態になる
				//playStrAniUp->Init(oldX, oldY, CurrentHeart->sp->GetPosX(), CurrentHeart->sp->GetPosY() - 56, 4);//ハートに登る移動動画初期化
				//playStrAniUp->Play();
				//Heart_CreateFigure();
				PlayerAction_SetAction(ani_heartRotate);//ハート登るアニメーションに切り替え
				PlayerAction_SetOneStickPos(CurrentHeart->sp->GetPosX(), CurrentHeart->sp->GetPosY(), Dir);//”１”の位置を設定
				heartRotateTime = 1800;        //回転時間初期化
			//}
			}
			else if (CurrentHeart->ht == Diagonal) {
				collisionSt = ps_default;
				Player_SetState_GobyLine();
			}
		}
		else {
			collisionSt = ps_heartRotate;
			PlayerCollision_LeaveHeart();
			Line_DeleteLineAll();
			Heart_ReSet();
			GM_mainCamera()->SetFocusLens(1.0f);
		}
	}
	/*int b = MapCollisionBoxCheck();
	if (b) {
		Line_DeleteLineAll();
		Heart_ReSet();
		GM_mainCamera()->SetFocusLens(1.0f);
		collisionSt = ps_default;
	}*/
}

void Dead_Update() {
	if (DeadCount <= 0) {
		DeadCount = 0;
		SM_SceneChange(EFailure);
	}
	DeadCount--;
}


void TransBoxMove_Update() {
	if (playStrAni->GetPlayF()) {
		//playStrAni->Update();
		posX = playStrAni->GetPosX();       //Player位置更新
		posY = playStrAni->GetPosY();
	}

	if (playStrAni->GetPlayF() == false) {
		CollisionRectangle co = PlayerCollision_GetCollision();
		int hb = Stage_GetNumberOfBlock(bl_stageTransBox);
		for (int i = 0; i < hb; i++)
		{
			M_stageTransBox* hbx = Stage_transBox_hit(&co, i);
			if (hbx != NULL&&hbx->GetActive()) {
				collisionSt = ps_transBoxStand;
				PlayerAction_SetAction(ani_heartRotate);
				PlayerAction_SetOneStickModel(false);
				transStageWatingTime = 20;

				Line_DeleteLineAll();
				Heart_ReSet();
				
			}
		}
		int gb = Stage_GetNumberOfBlock(bl_goalBox);
		for (int i = 0; i < gb; i++)
		{
			M_goalBox* gbx = Stage_GetGoalBox_byNumber(i);
			CollisionRectangle cr_g = gbx->GetColl();
			if (gbx != NULL) {
				if (Collision_RectangleAndRectangleHit(&co, &cr_g)) {
					collisionSt = ps_stageClear;
					PlayerAction_SetAction(ani_heartRotate);
					PlayerAction_SetOneStickModel(false);
					transStageWatingTime = 20;
					Line_DeleteLineAll();
					Heart_ReSet();
				}				
			}
		}
	}
}

void TransBoxStand_Update() {
	if (transStageWatingTime <= 0) {
		transStageWatingTime = 0;

		CollisionRectangle co = PlayerCollision_GetCollision();
		int hb = Stage_GetNumberOfBlock(bl_stageTransBox);
		for (int i = 0; i < hb; i++)
		{
			M_stageTransBox* hbx = Stage_transBox_hit(&co, i);
			if (hbx != NULL) {
				SoundManager_PlaySE(SL_player_trans);
				MapManager_StageTrans(hbx->GetNextName());
				//collisionSt = ps_default;
				//speed_H = 0;
			}
		}
	}
	transStageWatingTime--;
}

void StageClear_Update() {
	if (transStageWatingTime <= 0) {
		transStageWatingTime = 0;
		MapManager_StageClear();
	}
	transStageWatingTime--;
}


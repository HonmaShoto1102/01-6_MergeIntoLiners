#include "FairyVH.h"
//#include "FairyStates.h"
//#include "Heart.h"
#include "FairyClass.h"
#include "InputManager.h"
#include "drawNumber.h"

//static FAIRY F_vertica;
//static FAIRY F_horizy;
//static stateMachineC<FAIRYSTATEe>* stm_v;
//static stateMachineC<FAIRYSTATEe>* stm_h;
//static Fs_Stand* fs_stand_v;
//static Fs_Appear* fs_appear_v;
//static Fs_LineBecame* fs_linebecome_v;
//static Fs_OblMoving* fs_oblmoving_v;
//
//static Fs_Stand* fs_stand_h;
//static Fs_Appear* fs_appear_h;
//static Fs_LineBecame* fs_linebecome_h;
//static Fs_OblMoving* fs_oblmoving_h;



static int Fv_Current = 0;
static int Fh_Current = 0;
//static bool lockSwitchV = false;
//static bool lockSwitchH = false;

static FairyClass* fairyV[FMAX];
static FairyClass* fairyH[FMAX];

//static float2D heartPoint;
//static int heartNo;


void FairyVH_Load()
{
	SetFairyMaxV(2);
	SetFairyMaxH(3);

	Heart_Load();
	for (int i = 0; i <FMAX; i++)
	{
		fairyV[i] = new FairyClass(VERTICA, "Asset/vertica.png");
		fairyH[i] = new FairyClass(HORIZY, "Asset/horizy.png");
		fairyV[i]->SetFairyID(i);
		fairyH[i]->SetFairyID(i);
	}
	/*stm_v = new stateMachineC<FAIRYSTATEe>();
	stm_h = new stateMachineC<FAIRYSTATEe>();
	F_vertica.sprite = new SpriteC("Asset/vertica.png");
	F_vertica.endPoint = new SpriteC("Asset/cursor_vertica.png");
	F_vertica.name = VERTICA;
	F_horizy.sprite = new SpriteC("Asset/horizy.png");
	F_horizy.endPoint = new SpriteC("Asset/cursor_horizy.png");
	F_horizy.name = HORIZY;

	fs_stand_v = new Fs_Stand(fs_stand, &F_vertica);
	fs_appear_v = new Fs_Appear(fs_appear, &F_vertica);
	fs_linebecome_v = new Fs_LineBecame(fs_lineBecome, &F_vertica);
	fs_oblmoving_v = new Fs_OblMoving(fs_oblmoving, &F_vertica);

	fs_stand_h = new Fs_Stand(fs_stand, &F_horizy);
	fs_appear_h = new Fs_Appear(fs_appear, &F_horizy);
	fs_linebecome_h = new Fs_LineBecame(fs_lineBecome, &F_horizy);
	fs_oblmoving_h = new Fs_OblMoving(fs_oblmoving, &F_horizy);

	stm_v->AddState(fs_stand_v);
	stm_v->AddState(fs_appear_v);
	stm_v->AddState(fs_linebecome_v);
	stm_v->AddState(fs_oblmoving_v);

	stm_h->AddState(fs_stand_h);
	stm_h->AddState(fs_appear_h);
	stm_h->AddState(fs_linebecome_h);
	stm_h->AddState(fs_oblmoving_h);*/
}

void FairyVH_Init()
{
	Heart_Init();
	for (int i = 0; i < FMAX; i++)
	{
		fairyV[i]->Init();
		fairyH[i]->Init();		
	}
	
	//F_vertica.sprite->Init();
	//F_vertica.endPoint->Init();
	////F_vertica.endPoint->SetAlpha(0.3f);
	//F_vertica.endPoint->SetAnchorPoint(ANCHOR_CENTER);
	//F_vertica.endPoint->SetActive(false);
	//F_vertica.endPoint->SetScale(0.6f, 0.6f);
	//F_vertica.sprite->SetScale(0.6f, 0.6f);
	//F_vertica.sprite->SetAnchorPoint(ANCHOR_CENTER);
	//F_vertica.sprite->SetActive(false);
	//F_horizy.sprite->Init();
	//F_horizy.endPoint->Init();
	////F_horizy.endPoint->SetAlpha(0.3f);
	//F_horizy.endPoint->SetActive(false);
	//F_horizy.endPoint->SetAnchorPoint(ANCHOR_CENTER);
	//F_horizy.endPoint->SetScale(0.6f, 0.6f);
	//F_horizy.sprite->SetScale(0.6f, 0.6f);
	//F_horizy.sprite->SetAnchorPoint(ANCHOR_CENTER);
	//F_horizy.sprite->SetActive(false);

	//stm_v->Init();
	//stm_h->Init();
}

void FairyVH_Update()
{
	//stm_v->Update();
	//stm_h->Update();
	//for (int i = 0; i < Fv_Current; i++)
	//{
	//	fairyV[i]->Update();
	//	//fairyH[i]->Update();
	//}
	//for (int i = 0; i < Fh_Current; i++)
	//{
	//	fairyH[i]->Update();
	//}
	//DrawNumber_ReSet();

	
	
	for (int i = 1; i < GetFairyMaxV(); i++)
	{
		if ((fairyV[i - 1]->GetCallLock() == false&&fairyV[i]->GetCallLock())||
			fairyV[i]->GetState()!=fs_stand) {
			/*if (!(fairyV[i].GetState() == fs_stand && fairyV[i]->GetCallLock() == false)) {

			}*/
			fairyV[i]->Update();
		}	
	}
	for (int i = 1; i < GetFairyMaxH(); i++)
	{
		if ((fairyH[i - 1]->GetCallLock() == false&&fairyH[i]->GetCallLock())||		
			fairyH[i]->GetState()!= fs_stand) {
			fairyH[i]->Update();
		}
	}

	if (fairyV[0]->GetCallLock() || fairyV[0]->GetState() != fs_stand) {
		fairyV[0]->Update();
	}
	if (fairyH[0]->GetCallLock() || fairyH[0]->GetState() != fs_stand) {
		fairyH[0]->Update();
	}
	
	Heart_Update();

}

void FairyVH_Final()
{
	Heart_Final();
	
	for (int i = 0; i < FMAX; i++)
	{
		delete fairyV[i];
		delete fairyH[i];
	}
	
	/*delete stm_v;
	delete stm_h;
	delete fs_appear_h;
	delete fs_appear_v;
	delete fs_stand_h;
	delete fs_stand_v;
	delete fs_linebecome_h;
	delete fs_linebecome_v;
	delete fs_oblmoving_h;
	delete fs_oblmoving_v;
	delete F_vertica.sprite;
	delete F_vertica.endPoint;
	delete F_horizy.sprite;
	delete F_horizy.endPoint;*/
}

void FairyVH_TransNextFairy(FAIRYNAMEe fse)
{
	switch (fse)
	{
	case VERTICA:
		Fv_Current++;
		if (Fv_Current > GetFairyMaxV())Fv_Current = GetFairyMaxV();
		break;
	case HORIZY:
		Fh_Current++;
		if (Fh_Current > GetFairyMaxH())Fh_Current = GetFairyMaxH();
		break;
	default:
		break;
	}
}

void FairyVH_SetLockV(bool loc,int num)
{
	fairyV[num]->SetCallLock(loc);
}

void FairyVH_SetLockH(bool loc,int num)
{
	fairyH[num]->SetCallLock(loc);
}

void FairyVH_SetLockAll(bool loc)
{
	for (int i = 0; i < FMAX; i++)
	{
		fairyV[i]->SetCallLock(loc);
		fairyH[i]->SetCallLock(loc);
	}
}

void FairyVH_SetLockAllV(bool loc)
{
	for (int i = 0; i < FMAX; i++)
	{
		fairyV[i]->SetCallLock(loc);
		//fairyH[i]->SetCallLock(loc);
	}
}

void FairyVH_SetLockAllH(bool loc)
{
	for (int i = 0; i < FMAX; i++)
	{
		//fairyV[i]->SetCallLock(loc);
		fairyH[i]->SetCallLock(loc);
	}
}

void FairyVH_DeleteFairyV(int fairyNum)
{
	fairyV[fairyNum]->GetSTM().StateTrans(fs_stand);
}

void FairyVH_DeleteFairyH(int fairyNum)
{
	fairyH[fairyNum]->GetSTM().StateTrans(fs_stand);
}

bool FairyVH_GetboolByFocus()
{
	//bool re = false;
	for (int i = 0; i < FMAX; i++)
	{
		if (fairyV[i]->GetState() == fs_appear||
			fairyV[i]->GetState() == fs_oblmoving)return true;
		if (fairyH[i]->GetState() == fs_appear||
			fairyH[i]->GetState() == fs_oblmoving)return true;
	}
	if (Line_GetActiveLineH())return true;
	if (Line_GetActiveLineV())return true;
	return false;
}

FAIRY * FairyVH_GetVertica(int id)
{
	return fairyV[id]->GetFairy();
}

FAIRY * FairyVH_GetHorizy(int id)
{
	return fairyH[id]->GetFairy();
}

FAIRYSTATEe FairyVH_GetStateV(int id)
{
	return fairyV[id]->GetState();
}

FAIRYSTATEe FairyVH_GetStateH(int id)
{
	return fairyH[id]->GetState();
}

bool FairyVH_GetStateForAllV(FAIRYSTATEe fs)
{
	for (int i = 0; i < GetFairyMaxV(); i++)
	{
		if (fairyV[i]->GetState() == fs)return true;
	}
	return false;
}

bool FairyVH_GetStateForAllH(FAIRYSTATEe fs)
{

	for (int i = 0; i < GetFairyMaxH(); i++)
	{
		if (fairyH[i]->GetState() == fs)return true;
	}
	return false;
}

CollisionCircle FairyVH_GetCollisionV(int id)
{
	CollisionCircle cc;
	cc.center.x = fairyV[id]->GetFairy()->sprite->GetPosX();
	cc.center.y = fairyV[id]->GetFairy()->sprite->GetPosY();
	cc.radius = 50;
	return cc;
}

CollisionCircle FairyVH_GetCollisionH(int id)
{
	CollisionCircle cc;
	cc.center.x = fairyH[id]->GetFairy()->sprite->GetPosX();
	cc.center.y = fairyH[id]->GetFairy()->sprite->GetPosY();
	cc.radius = 50;
	return cc;
}

CollisionCircle FairyVH_GetCurrentCollisionV()
{
	int cu = 0;
	for (int i = 0; i < GetFairyMaxV(); i++)
	{
		if (fairyV[i]->GetState() == fs_appear || fairyV[i]->GetState() == fs_oblmoving) {
			cu = i;
		}
	}
	CollisionCircle co;
	co.center.x = fairyV[cu]->GetFairy()->sprite->GetPosX();
	co.center.y = fairyV[cu]->GetFairy()->sprite->GetPosY();
	co.radius = 50;
	return co;
}

CollisionCircle FairyVH_GetCurrentCollisionH()
{
	int cu = 0;
	for (int i = 0; i < GetFairyMaxH(); i++)
	{
		if (fairyH[i]->GetState() == fs_appear || fairyH[i]->GetState() == fs_oblmoving) {
			cu = i;
		}
	}
	CollisionCircle co;
	co.center.x = fairyH[cu]->GetFairy()->sprite->GetPosX();
	co.center.y = fairyH[cu]->GetFairy()->sprite->GetPosY();
	co.radius = 50;
	return co;
}

bool FairyVH_GetActiveV(int id)
{
	return fairyV[id]->GetFairy()->sprite->GetActive();
}

bool FairyVH_GetActiveH(int id)
{
	return fairyH[id]->GetFairy()->sprite->GetActive();
}

void FairyVH_SetFairyDirH(int dir)
{
	for (int i = 0; i < GetFairyMaxH(); i++)
	{
		if (fairyH[i]->GetState() == fs_appear) {
			fairyH[i]->GetState_Appear()->SetDir(dir);
		}
	}
}

int FairyVH_GetTimeOfLine_CountDownV(int id)
{
	return fairyV[id]->GetState_LineBecome()->lineCountDownTime;
}

int FairyVH_GetTimeOfLine_CountDownH(int id)
{
	return fairyH[id]->GetState_LineBecome()->lineCountDownTime;
}

int FairyVH_GetTimeOfLine_DurationV(int id)
{
	return fairyV[id]->GetState_LineBecome()->lineDruationTime;
}

int FairyVH_GetTimeOfLine_DurationH(int id)
{
	return fairyH[id]->GetState_LineBecome()->lineDruationTime;
}

int FairyVH_GetTimeOfFairy_CountDownV(int id)
{
	return fairyV[id]->GetState_Appear()->fairyCountDownTime;
}

int FairyVH_GetTimeOfFairy_CountDownH(int id)
{
	return fairyH[id]->GetState_Appear()->fairyCountDownTime;
}

int FairyVH_GetTimeOfFairy_DurationV(int id)
{
	return fairyV[id]->GetState_Appear()->fairyDruationTime;
}

int FairyVH_GetTimeOfFairy_DurationH(int id)
{
	return fairyH[id]->GetState_Appear()->fairyDruationTime;
}

int FairyVH_GetCoolTimeV(int id)
{
	return fairyV[id]->GetState_Stand()->GetCoolTime();
}

int FairyVH_GetCoolTimeH(int id)
{
	return fairyH[id]->GetState_Stand()->GetCoolTime();
}

int FairyVH_GetCoolTimeMaxV(int id)
{
	return fairyV[id]->GetState_Stand()->GetCoolTimeMax();
}

int FairyVH_GetCoolTimeMaxH(int id)
{
	return fairyH[id]->GetState_Stand()->GetCoolTimeMax();
}

float FairyVH_CoolTimePercentV(int id)
{
	int ct = fairyV[id]->GetState_Stand()->GetCoolTime();
	int ctm = fairyV[id]->GetState_Stand()->GetCoolTimeMax();
	float pe = (float)ct / ctm;
	return pe;
}

float FairyVH_CoolTimePercentH(int id)
{
	int ct = fairyH[id]->GetState_Stand()->GetCoolTime();
	int ctm = fairyH[id]->GetState_Stand()->GetCoolTimeMax();
	float pe = (float)ct / ctm;
	return pe;
}





#include "InputManager.h"

static bool K_move_A = true;
static bool K_move_D = true;
static bool K_attack = true;
static bool K_callFV = true;
static bool K_callFH = true;
static bool K_lineFV = true;
static bool K_lineFH = true;
static bool K_desAll = true;
static bool K_lineDir = true;

static CAMERA_FOUCS cameraFocus = cf_player;
static int fairyMaxCountH = 1;
static int fairyMaxCountV = 1;
static bool InCaves = false;

void SetKey_MoveA(bool b)
{
	K_move_A = b;
}

void SetKey_MoveD(bool b)
{
	K_move_D = b;
}

bool GetKey_MoveA()
{
	return K_move_A;
}

bool GetKey_MoveD()
{
	return K_move_D;
}

void SetKey_CallFairyV(bool b)
{
	K_callFV = b;
}

void SetKey_CallFairyH(bool b)
{
	K_callFH = b;
}

bool GetKey_CallFairyV()
{
	return K_callFV;
}

bool GetKey_CallFairyH()
{
	return K_callFH;
}

void SetKey_LineCreatV(bool b)
{
	K_lineFV = b;
}

void SetKey_LineCreatH(bool b)
{
	K_lineFH = b;
}

bool GetKey_LineCreatV()
{
	return K_lineFV;
}

bool GetKey_LineCreatH()
{
	return K_lineFH;
}

void SetKey_DestroyAll(bool b)
{
	K_desAll = b;
}

bool GetKey_DestroyAll()
{
	return K_desAll;
}

void SetKey_Attack(bool b)
{
	K_attack = b;
}

bool GetKey_Attack()
{
	return K_attack;
}

void SetKey_LineDir(bool b)
{
	K_lineDir = b;
}

bool GetKey_LineDir()
{
	return K_lineDir;
}

void SetCamera_Foucs(CAMERA_FOUCS cf)
{
	if (CAMERA_FOCUS_FAIRY_OFF&&cf == cf_fariy)return;
	cameraFocus = cf;
}

CAMERA_FOUCS GetCamera_Foucs()
{
	return cameraFocus;
}

void SetFairyMaxV(int max)
{
	fairyMaxCountV = max;
}

void SetFairyMaxH(int max)
{
	fairyMaxCountH = max;
}

int GetFairyMaxV()
{
	return fairyMaxCountV;
}

int GetFairyMaxH()
{
	return fairyMaxCountH;
}

void SetInCaves(bool on)
{
	InCaves = on;
}

bool GetInCaves()
{
	return InCaves;
}

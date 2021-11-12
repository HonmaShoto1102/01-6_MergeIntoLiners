#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define GO_HEART_COLLISION_OFF  (true)
#define CAMERA_FOCUS_FAIRY_OFF  (false)
#define SET_START_STAGE  (0)
#define SET_START_SCENE  (1)


//ˆÚ“®“ü—Í
void SetKey_MoveA(bool b);
void SetKey_MoveD(bool b);

bool GetKey_MoveA();
bool GetKey_MoveD();

//—d¸o‚·“ü—Í
void SetKey_CallFairyV(bool b);
void SetKey_CallFairyH(bool b);

bool GetKey_CallFairyV();
bool GetKey_CallFairyH();

//ƒ‰ƒCƒ“‚ª¶¬“ü—Í
void SetKey_LineCreatV(bool b);
void SetKey_LineCreatH(bool b);

bool GetKey_LineCreatV();
bool GetKey_LineCreatH();

//—d¸‚Æƒ‰ƒCƒ“æ‚èÁ‚µ“ü—Í
void SetKey_DestroyAll(bool b);

bool GetKey_DestroyAll();

//UŒ‚A“ü—Í
void SetKey_Attack(bool b);

bool GetKey_Attack();

//—d¸‚ªÎ‚ßƒ‰ƒCƒ“¶¬•ûŒü’²®,player‚ªƒn[ƒgã‚ÌA—d¸‚ªÎ‚ßƒ‰ƒCƒ“¶¬—\’èAUƒ{ƒ^ƒ“‚ª•ûŒü’²®‚Å‚«‚é
void SetKey_LineDir(bool b);
bool GetKey_LineDir();

//{{{{{{{{{{{{{{ƒJƒƒ‰{{{{{{{{{{{{{{{{{{
enum CAMERA_FOUCS
{
	cf_player,     //player‚ªÅ“_
	cf_fariy,      //—d¸‚ªÅ“_
	cf_movingfairy,//Î‚ßƒ‰ƒCƒ“‚ÉˆÚ“®’†‚Ì—d¸
	cf_event1,
};

void SetCamera_Foucs(CAMERA_FOUCS cf);
CAMERA_FOUCS GetCamera_Foucs();

//—d¸ŒÄ‚Ño‚¹‚é”‚ğw’è
void SetFairyMaxV(int max);
void SetFairyMaxH(int max);

//—d¸ŒÄ‚Ño‚¹‚é”‚ğæ“¾
int GetFairyMaxV();
int GetFairyMaxH();


//::::::::::::::::::::::::::::::::::::::‹Šp”ÍˆÍ•ÏX::::::::::::::::::::::::::::::::::::::
void SetInCaves(bool on);
bool GetInCaves();


#endif // !INPUTMANAGER_H


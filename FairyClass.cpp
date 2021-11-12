#include "FairyClass.h"
#include "drawNumber.h"

FairyClass::FairyClass(FAIRYNAMEe nam, const char* filename)
{
	name = nam;
	fairySelf.sprite = new SpriteC(filename);
	if (name == VERTICA) {
		fairySelf.endPoint = new SpriteC("Asset/cursor_vertica.png",13);
	}
	else if(name == HORIZY){
		fairySelf.endPoint = new SpriteC("Asset/cursor_horizy.png",13);
	}
	fairySelf.name = nam;
	fairySelf.fairyID = LINENULL;

	state_Stand = new Fs_Stand(fs_stand, &fairySelf);
	state_Appear = new Fs_Appear(fs_appear, &fairySelf);
	state_LineBecome = new Fs_LineBecame(fs_lineBecome, &fairySelf);
	state_Oblmoving = new Fs_OblMoving(fs_oblmoving, &fairySelf);

	stm.AddState(state_Stand);
	stm.AddState(state_Appear);
	stm.AddState(state_LineBecome);
	stm.AddState(state_Oblmoving);
	callLock = true;
}

void FairyClass::Init()
{
	fairySelf.sprite->Init();
	fairySelf.sprite->SetAnchorPoint(ANCHOR_CENTER);
	fairySelf.sprite->SetScale(0.6f, 0.6f);
	fairySelf.sprite->SetActive(false);
	fairySelf.endPoint->Init();
	fairySelf.endPoint->SetAnchorPoint(ANCHOR_CENTER);
	fairySelf.endPoint->SetScale(0.6f, 0.6f);
	fairySelf.endPoint->SetActive(false);
	
	stm.Init();

}

void FairyClass::Update()
{
	stm.Update();

	//DrawNumber_SetDraw(fairySelf.sprite->GetPosX(), fairySelf.sprite->GetPosY(), fairySelf.fairyID, name, fairySelf.fairyID + 10);
	//DrawNumber_Update();
}

void FairyClass::Final()
{
	delete state_Stand;
	delete state_Appear;
	delete state_LineBecome;
	delete state_Oblmoving;
	delete fairySelf.sprite;
	delete fairySelf.endPoint;
}

#ifndef FAIRYCLASS_H
#define FAIRYCLASS_H
#include "FairyVH.h"
#include "FairyStates.h"
#include "Heart.h"


class FairyClass {
public:
	FairyClass(FAIRYNAMEe nam,const char* filename);
	~FairyClass() { Final(); };

	//void Load();
	void Init();
	void Update();
	void Final();

	FAIRY* GetFairy() { return &fairySelf; }
	FAIRYSTATEe GetState() { return stm.GetNowState(); }
	Fs_Stand* GetState_Stand() { return state_Stand; }
	Fs_Appear* GetState_Appear() { return state_Appear; }
	Fs_LineBecame* GetState_LineBecome() { return state_LineBecome; }
	Fs_OblMoving* GetState_Oblmoving() { return state_Oblmoving; }

	void SetFairyID(int id) { fairySelf.fairyID = id; }
	bool GetCallLock() { return callLock; }
	void SetCallLock(bool b) { callLock = b; }
	stateMachineC<FAIRYSTATEe> GetSTM() { return stm; }

private:
	FAIRYNAMEe name;

	FAIRY fairySelf;
	stateMachineC<FAIRYSTATEe> stm;
	Fs_Stand* state_Stand;
	Fs_Appear* state_Appear;
	Fs_LineBecame* state_LineBecome;
	Fs_OblMoving* state_Oblmoving;

	bool callLock;
};



#endif // !FAIRYCLASS_H


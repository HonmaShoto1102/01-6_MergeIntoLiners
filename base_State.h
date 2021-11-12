#ifndef BASE_STATE_H
#define BASE_STATE_H
//#include <list>
#include <vector>
#include <memory>

template<typename ST>
class stateMachineC;
template<typename ST>
class baseState
{
public:
	virtual ~baseState() { 
		nextStates.clear(); 
	}

 	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Final() = 0;
	ST GetStateName() { return stateName; }
	bool NextStateCheck(ST stName) {
		for (size_t i = 0; i < nextStates.size(); i++)
		{
			if (nextStates[i] == stName) {
				return true;
			}
		}
		return false;
	}
	//virtual void 
	void AddNextState(ST stName) {
		nextStates.push_back(stName);
	}
	void AddNextState(baseState<ST>* sta) {
		nextStates.pop_back(sta->GetStateName());
	}
	//std::list<baseTranslation> translations;
	void SetMachine(stateMachineC<ST>* st) { stateMachine = st; }
protected:
	std::vector<ST> nextStates;
	ST stateName;
	stateMachineC<ST>* stateMachine;
private:
	
};

template<typename ST>
class baseState;
template<typename ST>
class stateMachineC {
public:
	
	stateMachineC() { fristState = NULL; CurrentState = NULL; }
	~stateMachineC() {
		states.clear();
	}
	void Init() {
		CurrentState->Init();
	};
	void Update() {
		CurrentState->Update();
	}
	ST GetNowState() {
		return CurrentState->GetStateName();
	}
	
	void StateTrans(ST stateName) {

		if (CurrentState->NextStateCheck(stateName)) {
			baseState<ST>* temp_state = FindState(stateName);
			if (temp_state != NULL) {
				CurrentState->Final();
				CurrentState = temp_state;
				CurrentState->Init();
			}
		}
	}
	
	void AddState(baseState<ST>* st) {
		if (fristState == NULL) {
			fristState = st;
			CurrentState = st;
			//CurrentState->SetMachine(this);
			//CurrentState->Init();
		}
		st->SetMachine(this);
		states.push_back(st);
	}
	
	baseState<ST>* fristState;
	
	baseState<ST>* CurrentState;
	
protected:
	std::vector<baseState<ST>*> states;
private:
	baseState<ST>* FindState(ST sname) {
		for (size_t i = 0; i < states.size(); i++)
		{
			ST st = states[i]->GetStateName();
			if (st == sname) {
				return states[i];
			}
		}
		return NULL;
	}

};


#endif // !BASE_STATE_H


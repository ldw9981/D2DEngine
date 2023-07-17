#pragma once
#include "Helper.h"
#include "AnimationComponent.h"

class FSMComponent;
class FSMState;
class FSMTransition;
class FSMStateAlias;
class FiniteStateMachine 
{
public:
	FiniteStateMachine(FSMComponent* pOwnerComponent)
		:m_pCurrentState(nullptr), m_pInitialState(nullptr), m_pOwnerComponent(pOwnerComponent)
	{
	
	}
	virtual ~FiniteStateMachine();
protected:
	FSMState* m_pCurrentState;  // 현재 상태
	FSMState* m_pInitialState;	// 초기 상태
	FSMComponent* m_pOwnerComponent;	// FSMComponent

	std::map<std::string, FSMState*> m_pStates;	// 생성된 FSMState들을 저장하는 컨테이너

	std::vector<FSMStateAlias*> m_pStateAlias;	// StateAlias 들을 저장하는 컨테이너
public:
	virtual void Update();
	void ChangeState(std::string stateName);
	void SetInitialState(std::string stateName);
	void AddState(FSMState* pState);
	void AddStateAlias(FSMStateAlias* pStateAlias);

};


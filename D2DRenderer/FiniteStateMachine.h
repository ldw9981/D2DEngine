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
	FSMState* m_pCurrentState;  // ���� ����
	FSMState* m_pInitialState;	// �ʱ� ����
	FSMComponent* m_pOwnerComponent;	// FSMComponent

	std::map<std::string, FSMState*> m_pStates;	// ������ FSMState���� �����ϴ� �����̳�

	std::vector<FSMStateAlias*> m_pStateAlias;	// StateAlias ���� �����ϴ� �����̳�
public:
	virtual void Update();
	void ChangeState(std::string stateName);
	void SetInitialState(std::string stateName);
	void AddState(FSMState* pState);
	void AddStateAlias(FSMStateAlias* pStateAlias);

};


#pragma once
#include "FSMState.h"
#include "FSMTransition.h"

/*
	State간에 공유하는 Transition을 작동시킨다.
*/
class FSMComponent;
class GameObject;
class FSMTransition;
class FiniteStateMachine;
class FSMState;

class FSMStateAlias 
{
public:
	FSMStateAlias(FiniteStateMachine* pOwner)
		:m_pOwner(pOwner)
	{

	}
	virtual ~FSMStateAlias()
	{

	}

	FiniteStateMachine* m_pOwner;
	std::vector<FSMTransition*> m_Transitions;
	std::vector<FSMState*> m_States;

public:
	bool CheckAlias(FSMState* pState)
	{
		for (auto& p : m_States)
		{
			if (p == pState)
				return true;
		}
		return false;
	}
	void BindState(FSMState* pState) { m_States.push_back(pState); }
	bool CheckTransition(std::string& OutNextState)
	{
		for (auto pTransition : m_Transitions)
		{
			if (pTransition->CheckCondition() == true)
			{
				OutNextState = pTransition->m_NextState;
				return true;
			}
		}
		return false;
	}

};

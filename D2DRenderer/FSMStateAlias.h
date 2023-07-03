#pragma once
#include "FSMState.h"

class FSMComponent;
class GameObject;
class FSMTransition;
class FSMInstance;
class FSMState;
class FSMStateAlias :public FSMState
{
public:
	FSMStateAlias(FSMInstance* pOwner, std::wstring Name)
		:FSMState(pOwner,Name)
	{

	}
	virtual ~FSMStateAlias()
	{

	}
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


	virtual void Enter() {};
	virtual void Update() {};
	virtual void Exit() {};

	virtual void EventAnimationEnd(const std::wstring& AnimationName){};
	virtual void EventAnimationNotify(const std::wstring& NotifyName){};
};

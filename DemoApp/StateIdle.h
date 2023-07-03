#pragma once
#include "../D2DRenderer/FSMState.h"

class StateIdle : public FSMState
{
public:

	StateIdle(FSMInstance* pOwner)
		:FSMState(pOwner, L"Idle")
	{

	}
	~StateIdle()
	{

	}

	void Enter() override;
	void Update() override;
	void Exit() override;

	virtual bool CheckTransition(std::wstring& NextState) { return false;}
	virtual void EventAnimationEnd(const std::wstring& AnimationName){}
	virtual void EventAnimationNotify(const std::wstring& NotifyName){};
};


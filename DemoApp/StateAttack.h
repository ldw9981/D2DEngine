#pragma once
#include "../D2DRenderer/FSMState.h"
class StateAttack :
	public FSMState
{
public:
	StateAttack(FiniteStateMachine* pOwner);
	virtual ~StateAttack();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

	virtual bool CheckTransition(std::wstring& NextState) override;
	virtual void EventAnimationEnd(const std::wstring& AnimationName) override;
	virtual void EventAnimationNotify(const std::wstring& NotifyName) override;
};


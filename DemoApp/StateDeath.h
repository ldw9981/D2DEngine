#pragma once
#include "../D2DRenderer/FSMState.h"

class FiniteStateMachine;
class StateDeath : public FSMState
{
public:

	StateDeath(FiniteStateMachine* pOwner);
	~StateDeath();
	void Enter() override;
	void Update() override;
	void Exit() override;

	virtual bool CheckTransition(std::wstring& NextState) override;
	virtual void EventAnimationEnd(const std::wstring& AnimationName) override;
	virtual void EventAnimationNotify(const std::wstring& NotifyName) override;
};


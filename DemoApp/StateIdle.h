#pragma once
#include "../D2DRenderer/FSMState.h"

class FiniteStateMachine;
class StateIdle : public FSMState
{
public:

	StateIdle(FiniteStateMachine* pOwner);
	~StateIdle();

	void Enter() override;
	void Update() override;
	void Exit() override;

	virtual bool CheckTransition(std::string& NextState) override;
};


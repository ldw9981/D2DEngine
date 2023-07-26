#pragma once
#include "../D2DRenderer/FSMState.h"
class StateMove :
    public FSMState
{
public:
	StateMove(FiniteStateMachine* pOwner);
	virtual ~StateMove();

	virtual void Enter() override;
	virtual void Update(float DeltaTime) override;
	virtual void Exit() override;

	virtual bool CheckTransition(std::string& NextState) override;
};


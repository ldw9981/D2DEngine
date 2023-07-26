#pragma once
#include "../D2DRenderer/FSMState.h"

class FiniteStateMachine;
class StateDeath : public FSMState
{
public:

	StateDeath(FiniteStateMachine* pOwner);
	~StateDeath();
	void Enter() override;
	void Update(float DeltaTime) override;
	void Exit() override;

	virtual bool CheckTransition(std::string& NextState) override;
};


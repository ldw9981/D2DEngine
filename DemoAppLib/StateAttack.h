#pragma once
#include "../D2DRenderer/FSMState.h"
class StateAttack :
	public FSMState
{
public:
	StateAttack(FiniteStateMachine* pOwner);
	virtual ~StateAttack();


	float m_BackupSpeed;

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;

	virtual bool CheckTransition(std::string& NextState) override;
};


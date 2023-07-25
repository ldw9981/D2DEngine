#include "pch.h"
#include "StateDeath.h"
#include "../D2DRenderer/FSMState.h"

StateDeath::StateDeath(FiniteStateMachine* pOwner)
	:FSMState(pOwner, "Death")
{

}

StateDeath::~StateDeath()
{
}

void StateDeath::Enter()
{

}

void StateDeath::Update()
{

}

void StateDeath::Exit()
{

}

bool StateDeath::CheckTransition(std::string& NextState)
{
	return false;
}


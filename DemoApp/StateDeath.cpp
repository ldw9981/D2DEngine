#include "framework.h"
#include "StateDeath.h"
#include "../D2DRenderer/FSMState.h"

StateDeath::StateDeath(FiniteStateMachine* pOwner)
	:FSMState(pOwner, L"Death")
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

bool StateDeath::CheckTransition(std::wstring& NextState)
{
	return false;
}

void StateDeath::EventAnimationEnd(const std::wstring& AnimationName)
{

}

void StateDeath::EventAnimationNotify(const std::wstring& NotifyName)
{

}

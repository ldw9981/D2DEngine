#include "framework.h"
#include "StateAttack.h"
#include "../D2DRenderer/FSMState.h"

StateAttack::StateAttack(FiniteStateMachine* pOwner)
	:FSMState(pOwner, L"Attack")
{

}

StateAttack::~StateAttack()
{
}

void StateAttack::Enter()
{

}

void StateAttack::Update()
{

}

void StateAttack::Exit()
{

}

bool StateAttack::CheckTransition(std::wstring& NextState)
{
	return false;
}

void StateAttack::EventAnimationEnd(const std::wstring& AnimationName)
{

}

void StateAttack::EventAnimationNotify(const std::wstring& NotifyName)
{

}

#include "framework.h"
#include "StateMove.h"
#include "../D2DRenderer/FSMState.h"

StateMove::StateMove(FiniteStateMachine* pOwner)
	:FSMState(pOwner,L"Move")
{

}

StateMove::~StateMove()
{
}

void StateMove::Enter()
{

}

void StateMove::Update()
{

}

void StateMove::Exit()
{

}

bool StateMove::CheckTransition(std::wstring& NextState)
{
	return false;
}

void StateMove::EventAnimationEnd(const std::wstring& AnimationName)
{

}

void StateMove::EventAnimationNotify(const std::wstring& NotifyName)
{

}

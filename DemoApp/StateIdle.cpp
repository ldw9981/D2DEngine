#include "framework.h"
#include "StateIdle.h"

StateIdle::StateIdle(FiniteStateMachine* pOwner) 
	:FSMState(pOwner, L"Idle")
{

}

StateIdle::~StateIdle()
{
}

void StateIdle::Enter()
{

}

void StateIdle::Update() 
{

}

void StateIdle::Exit()
{

}
bool StateIdle::CheckTransition(std::wstring& NextState)
{
	return false;
}

void StateIdle::EventAnimationEnd(const std::wstring& AnimationName)
{

}

void StateIdle::EventAnimationNotify(const std::wstring& NotifyName)
{

}
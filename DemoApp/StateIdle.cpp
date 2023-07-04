#include "framework.h"
#include "StateIdle.h"
#include "FSMCharacter.h"

StateIdle::StateIdle(FiniteStateMachine* pOwner) 
	:FSMState(pOwner, L"Idle")
{

}

StateIdle::~StateIdle()
{
}

void StateIdle::Enter()
{
  	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation(L"Idle",false,true);
}

void StateIdle::Update() 
{
	//대기 상태에서는 아무것도 안한다.
}

void StateIdle::Exit()
{

}
bool StateIdle::CheckTransition(std::wstring& NextState)
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	
	if (pFSMCharacter->m_Attack)
	{
		NextState = L"Attack";
		return true;
	}
	else if( pFSMCharacter->m_MoveDirection.x != 0.0f || pFSMCharacter->m_MoveDirection.y != 0.0f)
	{
		NextState = L"Move";
		return true;
	}
	return false;
}

void StateIdle::EventAnimationEnd(const std::wstring& AnimationName)
{
	
}

void StateIdle::EventAnimationNotify(const std::wstring& NotifyName)
{

}
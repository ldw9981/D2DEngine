#include "framework.h"
#include "StateIdle.h"
#include "FSMCharacter.h"

StateIdle::StateIdle(FiniteStateMachine* pOwner) 
	:FSMState(pOwner, "Idle")
{

}

StateIdle::~StateIdle()
{
}

void StateIdle::Enter()
{
  	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Idle", pFSMCharacter->m_Mirror,true);
}

void StateIdle::Update() 
{
	//대기 상태에서는 아무것도 안한다.
}

void StateIdle::Exit()
{

}
bool StateIdle::CheckTransition(std::string& NextState)
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	
	if (pFSMCharacter->m_Attack)
	{
		NextState = "Attack";
		return true;
	}
	else if( pFSMCharacter->m_MoveDirection.x != 0.0f || pFSMCharacter->m_MoveDirection.y != 0.0f)
	{
		NextState = "Move";
		return true;
	}
	return false;
}

#include "framework.h"
#include "StateMove.h"
#include "FSMCharacter.h"


StateMove::StateMove(FiniteStateMachine* pOwner)
	:FSMState(pOwner,L"Move")
{

}

StateMove::~StateMove()
{
}

void StateMove::Enter()
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation(L"Move", false, true);
}

void StateMove::Update()
{

}

void StateMove::Exit()
{

}

bool StateMove::CheckTransition(std::wstring& NextState)
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if (pFSMCharacter->m_Attack)
	{
		NextState = L"Attack";
		return true;
	}
	else if (pFSMCharacter->m_MoveDirection.x == 0.0f && pFSMCharacter->m_MoveDirection.y == 0.0f)
	{
		NextState = L"Idle";
		return true;
	}
	return false;
}

void StateMove::EventAnimationEnd(const std::wstring& AnimationName)
{

}

void StateMove::EventAnimationNotify(const std::wstring& NotifyName)
{

}

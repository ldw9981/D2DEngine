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

	if (pFSMCharacter->m_MoveDirection.x > 0)
	{
		pFSMCharacter->m_Mirror = false;
		
	}
	else if (pFSMCharacter->m_MoveDirection.x < 0)
	{
		pFSMCharacter->m_Mirror = true;
		
	}
	pAnimationComponent->SetAnimation("Move", pFSMCharacter->m_Mirror, true);

}

void StateMove::Update()
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if (pFSMCharacter->m_LastDirection.x != pFSMCharacter->m_MoveDirection.x)
	{
		AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
		if (pFSMCharacter->m_MoveDirection.x > 0)
		{
			pFSMCharacter->m_Mirror = false;

		}
		else if (pFSMCharacter->m_MoveDirection.x < 0)
		{
			pFSMCharacter->m_Mirror = true;
		}
		pAnimationComponent->SetMirror(pFSMCharacter->m_Mirror);
	}
}

void StateMove::Exit()
{
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);	
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

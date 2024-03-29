#include "pch.h"
#include "StateAttack.h"
#include "../D2DRenderer/FSMState.h"
#include "FSMCharacter.h"
#include "../D2DRenderer/MovementComponent.h"

StateAttack::StateAttack(FiniteStateMachine* pOwner)
	:FSMState(pOwner, "Attack")
{

}

StateAttack::~StateAttack()
{
}

void StateAttack::Enter()
{
	// 공격 애니메이션을 시작하고 애니메이션 종료를 기다린다.
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Attack", pFSMCharacter->m_Mirror, false);
	pFSMCharacter->m_AnimationComplete = false;

	// 공격할때는 스피드 0 못움직이게 한다.
	SideMovementComponent* pSideMovementComponent = pFSMCharacter->m_pSideMovementComponent;
	m_BackupSpeed = pSideMovementComponent->GetSpeed();
	pSideMovementComponent->SetSpeed(0);
	
}

void StateAttack::Update(float DeltaTime)
{
	// 공격 중에 뭐 업데이트 할것이 있나?
}

void StateAttack::Exit()
{
	// 다른 상태로 가기전에 복구한다. 
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	pFSMCharacter->m_Attack = false;
	pFSMCharacter->m_AnimationComplete = false;

	SideMovementComponent* pSideMovementComponent = pFSMCharacter->m_pSideMovementComponent;
	pSideMovementComponent->SetSpeed(m_BackupSpeed);
}

bool StateAttack::CheckTransition(std::string& NextState)
{
	// 애니메이션 종료 후 전이된다.
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if(pFSMCharacter->m_Attack && pFSMCharacter->m_AnimationComplete)
	{
		NextState = "Idle";
		return true;
	}
	return false;
}

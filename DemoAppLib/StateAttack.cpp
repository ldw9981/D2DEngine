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
	// ���� �ִϸ��̼��� �����ϰ� �ִϸ��̼� ���Ḧ ��ٸ���.
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	AnimationComponent* pAnimationComponent = pFSMCharacter->m_pAnimationComponent;
	pAnimationComponent->SetAnimation("Attack", pFSMCharacter->m_Mirror, false);
	pFSMCharacter->m_AnimationComplete = false;

	// �����Ҷ��� ���ǵ� 0 �������̰� �Ѵ�.
	SideMovementComponent* pSideMovementComponent = pFSMCharacter->m_pSideMovementComponent;
	m_BackupSpeed = pSideMovementComponent->GetSpeed();
	pSideMovementComponent->SetSpeed(0);
	
}

void StateAttack::Update(float DeltaTime)
{
	// ���� �߿� �� ������Ʈ �Ұ��� �ֳ�?
}

void StateAttack::Exit()
{
	// �ٸ� ���·� �������� �����Ѵ�. 
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	pFSMCharacter->m_Attack = false;
	pFSMCharacter->m_AnimationComplete = false;

	SideMovementComponent* pSideMovementComponent = pFSMCharacter->m_pSideMovementComponent;
	pSideMovementComponent->SetSpeed(m_BackupSpeed);
}

bool StateAttack::CheckTransition(std::string& NextState)
{
	// �ִϸ��̼� ���� �� ���̵ȴ�.
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if(pFSMCharacter->m_Attack && pFSMCharacter->m_AnimationComplete)
	{
		NextState = "Idle";
		return true;
	}
	return false;
}

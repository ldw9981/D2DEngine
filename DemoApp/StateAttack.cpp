#include "framework.h"
#include "StateAttack.h"
#include "../D2DRenderer/FSMState.h"
#include "FSMCharacter.h"
#include "../D2DRenderer/MovementComponent.h"

StateAttack::StateAttack(FiniteStateMachine* pOwner)
	:FSMState(pOwner, L"Attack")
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
	pAnimationComponent->SetAnimation(L"Attack", false, false);
	pFSMCharacter->m_AnimationComplete = false;

	// �����Ҷ��� ���ǵ� 0 �������̰� �Ѵ�.
	MovementComponent* pMoveComponent = pFSMCharacter->m_pMovementComponent;
	m_BackupSpeed = pMoveComponent->GetSpeed();
	pMoveComponent->SetSpeed(0.0f);
	
}

void StateAttack::Update()
{
	// ���� �߿� �� ������Ʈ �Ұ��� �ֳ�?
}

void StateAttack::Exit()
{
	// �ٸ� ���·� �������� �����Ѵ�. 
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	pFSMCharacter->m_Attack = false;
	pFSMCharacter->m_AnimationComplete = false;

	MovementComponent* pMoveComponent = pFSMCharacter->m_pMovementComponent;
	pMoveComponent->SetSpeed(m_BackupSpeed);
}

bool StateAttack::CheckTransition(std::wstring& NextState)
{
	// �ִϸ��̼� ���� �� ���̵ȴ�.
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	if(pFSMCharacter->m_Attack && pFSMCharacter->m_AnimationComplete)
	{
		NextState = L"Idle";
		return true;
	}
	return false;
}

void StateAttack::EventAnimationEnd(const std::wstring& AnimationName)
{
	//�ִϸ��̼��� �����ٰ� �˸���.
	FSMCharacter* pFSMCharacter = static_cast<FSMCharacter*>(m_pOwner);
	pFSMCharacter->m_AnimationComplete = true;
}

void StateAttack::EventAnimationNotify(const std::wstring& NotifyName)
{

}

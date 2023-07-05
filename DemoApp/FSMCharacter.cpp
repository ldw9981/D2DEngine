#include "framework.h"
#include "FSMCharacter.h"

void FSMCharacter::Update()
{
	assert(m_pMovementComponent!=nullptr);
	m_LastDirection = m_MoveDirection;
	m_MoveDirection = m_pMovementComponent->GetDirection();

	FiniteStateMachine::Update();
}
#include "pch.h"
#include "FSMCharacter.h"
#include "../D2DRenderer/Helper.h"

void FSMCharacter::Update(float DeltaTime)
{
	assert(m_pSideMovementComponent !=nullptr);
	m_LastDirection = m_MoveDirection;
	m_MoveDirection = m_pSideMovementComponent->GetDirection();

	

	FiniteStateMachine::Update(DeltaTime);
}

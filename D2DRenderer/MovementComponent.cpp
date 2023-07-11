#include "pch.h"
#include "MovementComponent.h"
#include "SceneComponent.h"
#include "GameApp.h"
#include "Helper.h"


// ���ӵ� ������� ������ �ӵ��� �̵��Ѵ�.
void MovementComponent::Update()
{
	assert(m_pUpdateTarget != nullptr);
	// ���� ��ġ�� �����´�.
	mathHelper::Vector2F Location = m_pUpdateTarget->GetRelativeLocation();
	m_Velocity = m_Direction * m_Speed;		

	// ���ο� ��ġ�� ����Ѵ�.
	Location += m_Velocity * GameApp::m_deltaTime;	

	//���� ���� ��ġ�� �����Ѵ�.
	m_pUpdateTarget->SetRelativeLocation(Location);	
	m_pUpdateTarget->SetVelocity(m_Velocity);
}

void MovementComponent::SetDirection(const mathHelper::Vector2F& Direction)
{
	m_Direction = D2DHelper::NormalizeVector(Direction);	

}


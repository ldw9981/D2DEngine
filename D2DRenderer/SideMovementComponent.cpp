#include "pch.h"
#include "SideMovementComponent.h"
#include "MovementComponent.h"
#include "GameApp.h"


float SideMovementComponent::m_Gravity = 9.80f;

SideMovementComponent::SideMovementComponent(GameObject* pOwner, std::wstring Name)
:MovementComponent(pOwner,Name)
{
	m_GravityGameScale = 100.0f;
	m_GravityAcceleration = m_Gravity * m_GravityGameScale;	// �߷� ���ӵ�  
	m_JumpAcceleration = 500;		//���� ���ӵ�

	m_AccelerationY = 0.0f;
	m_IsJumping = false;
}

SideMovementComponent::~SideMovementComponent()
{
}

void SideMovementComponent::Update()
{
	assert(m_pUpdateTarget != nullptr);
	mathHelper::Vector2F Location = m_pUpdateTarget->GetRelativeLocation();
	// m_Speed�� 1�ʿ� �̵��� �Ÿ��̹Ƿ� �ð���ȭ��(��)�� ���ϸ�  �ð���ȭ��ŭ �󸶳� �̵��ؾ����� ����Ѵ�.
	m_Velocity = mathHelper::Vector2F(m_Direction) * m_Speed * GameApp::m_deltaTime;
	Location += m_Velocity;

	// �߷°��ӵ��� �ð��� �ӵ���ȭ�� �̹Ƿ� �ð���ȭ���� ���ؼ� Y�ӵ��� �����Ѵ�.
	m_VelocityY -= m_GravityAcceleration * GameApp::m_deltaTime;
	
	// Y�ӵ��� Y��ġ�� ����Ѵ�.
	Location.y += m_VelocityY * GameApp::m_deltaTime;

	// ���� �ӵ��� ����Ѵ�.
	m_Velocity.y = m_Velocity.y + m_VelocityY; 


	if (Location.y <= 0.0f)
	{
		m_IsJumping = false;
		m_VelocityY = 0.0f;
		m_GravityAcceleration =0.0f;
	}

	//���� ���� ��ġ�� �����Ѵ�.
	m_pUpdateTarget->SetRelativeLocation(Location.x, Location.y);
}

void SideMovementComponent::SetDirection(const mathHelper::Vector2F& Direction)
{
	m_Direction.x = Direction.x;
	m_Direction.y = 0;

}

void SideMovementComponent::Jump()
{
	if (m_IsJumping == false)
	{
		m_GravityAcceleration = SideMovementComponent::m_Gravity * m_GravityGameScale;
		m_IsJumping = true;
		m_VelocityY = m_JumpAcceleration;
	}
}

#include "pch.h"
#include "SideMovementComponent.h"
#include "MovementComponent.h"
#include "GameApp.h"
#include "Helper.h"

float SideMovementComponent::m_Gravity = 9.80f;

SideMovementComponent::SideMovementComponent(GameObject* pOwner, std::wstring Name)
:MovementComponent(pOwner,Name)
{
	m_GravityScale = 1.0f;
	m_GravityAcceleration = m_Gravity * m_GravityScale;	// �߷� ���ӵ�  
	m_JumpAcceleration = 6;		//���� ���ӵ�
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
	m_Velocity.x = (mathHelper::Vector2F(m_Direction) * m_Speed * GameApp::m_deltaTime).x;	

	// �߷°��ӵ��� �ð��� �ӵ���ȭ�� �̹Ƿ� �ð���ȭ���� ���ؼ� Y�ӵ��� �����Ѵ�.
	m_Velocity.y -= m_GravityAcceleration * GameApp::m_deltaTime;
	Location += m_Velocity;
	
	// �ܺο��� ���� �Ǵ��� �ؾ��ϴµ� �ϴ� 0.0f���� �۰ų� ������ ������ ������ �Ǵ��Ѵ�.
	if (Location.y <= 0.0f)
	{
		m_IsJumping = false;
		m_Velocity.y = 0.0f;
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
		m_GravityAcceleration = SideMovementComponent::m_Gravity * m_GravityScale;
		m_IsJumping = true;
		m_Velocity.y = m_JumpAcceleration;
	}
}

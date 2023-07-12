#include "pch.h"
#include "SideMovementComponent.h"
#include "MovementComponent.h"
#include "GameApp.h"
#include "Helper.h"

float SideMovementComponent::m_Gravity = 9.80f;

SideMovementComponent::SideMovementComponent(GameObject* pOwner, std::wstring Name)
:MovementComponent(pOwner,Name)
{
	m_GravityScale = 100.0f;  // 9.8�� �״�� ����  1�ʿ� 9.8 �ȼ��� �����
	m_GravityScaled = m_Gravity * m_GravityScale;	// �߷� ���ӵ�  
	m_JumpSpeed = 500;		
	m_IsJumping = false;
	m_SpeedY = 0.0f;
	m_MaxSpeedY = 600.0f;
}

SideMovementComponent::~SideMovementComponent()
{
}

void SideMovementComponent::Update()
{
	assert(m_pRootSceneComponent != nullptr);
	mathHelper::Vector2F Location = m_pRootSceneComponent->GetRelativeLocation();

	// x�� �̵� �ӵ�
	m_Velocity.x = (mathHelper::Vector2F(m_Direction) * m_Speed).x;
	
	// y�� �̵� �ӵ�
	m_SpeedY += m_GravityScaled * GameApp::m_deltaTime;	// y�� �̵��ӵ��� �߷¿� ���� ���� ��������.
	m_SpeedY = min(m_MaxSpeedY,m_SpeedY);				// ���ܼӵ��� �����Ѵ�.
	m_Velocity.y = (mathHelper::Vector2F(0.0f, -1.0f) * m_SpeedY).y;  

	//D2DHelper::Log(L"%f,%f\n", m_Velocity.x, m_Velocity.y);
	Location = Location + m_Velocity * GameApp::m_deltaTime;	// �ð���ȭ ��ŭ �̵�
	Location.y = max(0.0f, Location.y);						// �ٴ��� ������ ���ѳ��� ���� 
	// �ܺο��� ���� �Ǵ��� �ؾ��ϴµ� �ϴ� 0.0f���� �۰ų� ������ ������ ������ �Ǵ��Ѵ�.	
	if (Location.y <= 0.0f)
	{
		EndJump();
	}	

	//���� ���� ��ġ�� �����Ѵ�.
	m_pRootSceneComponent->SetRelativeLocation(Location);
	m_pRootSceneComponent->SetVelocity(m_Velocity);
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
		m_GravityScaled = SideMovementComponent::m_Gravity * m_GravityScale;
		m_IsJumping = true;
		m_SpeedY = m_JumpSpeed * -1; // ������ �߷��� �ݴ�
	}
}

void SideMovementComponent::EndJump()
{
	m_IsJumping = false;
	m_SpeedY = 0.0f;
	//m_GravityScaled = 0.0f;	// �߷��� ���°� ������?
}

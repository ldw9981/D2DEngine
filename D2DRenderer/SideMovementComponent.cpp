#include "pch.h"
#include "SideMovementComponent.h"
#include "MovementComponent.h"
#include "GameApp.h"
#include "Helper.h"

float SideMovementComponent::m_Gravity = 9.80f;

SideMovementComponent::SideMovementComponent(GameObject* pOwner, std::wstring Name)
:MovementComponent(pOwner,Name)
{
	m_GravityScale = 100.0f;  // 9.8을 그대로 쓰면  1초에 9.8 픽셀이 적용됨
	m_GravityAcceleration = m_Gravity * m_GravityScale;	// 중력 가속도  
	m_JumpSpeed = 500;		
	m_IsJumping = false;
	m_SpeedY = 0.0f;
	m_MinSpeedY = -600.0f;
}

SideMovementComponent::~SideMovementComponent()
{
}

void SideMovementComponent::Update()
{
	assert(m_pUpdateTarget != nullptr);
	mathHelper::Vector2F Location = m_pUpdateTarget->GetRelativeLocation();

	//                 속도 = 방향 * 힘
	m_Velocity.x = (mathHelper::Vector2F(m_Direction) * m_Speed).x;

	// 중력 가속도를 적용하며 속도를 종단속도로 제한한다.
	
	m_SpeedY -= m_GravityAcceleration * GameApp::m_deltaTime;	
	m_SpeedY = max(m_MinSpeedY,m_SpeedY);
	m_Velocity.y = (mathHelper::Vector2F(0.0f, 1.0f) * m_SpeedY).y;  

	D2DHelper::Log(L"%f,%f\n", m_Velocity.x, m_Velocity.y);

	//1초 기준 속도로 실제 시간을 적용해 위치를 계산한다.
	Location = Location + m_Velocity * GameApp::m_deltaTime;

	// 외부에서 착지 판단을 해야하는데 일단 0.0f보다 작거나 같으면 착지한 것으로 판단한다.	
	if (Location.y <= 0.0f)
	{
		EndJump();
	}	

	//새로 계산된 위치를 적용한다.
	m_pUpdateTarget->SetRelativeLocation(Location);
	m_pUpdateTarget->SetVelocity(m_Velocity);
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
		m_SpeedY = m_JumpSpeed;
	}
}

void SideMovementComponent::EndJump()
{
	m_IsJumping = false;
	m_SpeedY = 0.0f;
	m_GravityAcceleration = 0.0f;
}

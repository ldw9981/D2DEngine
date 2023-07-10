#include "pch.h"
#include "SideMovementComponent.h"
#include "MovementComponent.h"
#include "GameApp.h"


float SideMovementComponent::m_Gravity = 9.80f;

SideMovementComponent::SideMovementComponent(GameObject* pOwner, std::wstring Name)
:MovementComponent(pOwner,Name)
{
	m_GravityGameScale = 100.0f;
	m_GravityAcceleration = m_Gravity * m_GravityGameScale;	// 중력 가속도  
	m_JumpAcceleration = 500;		//점프 가속도

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
	// m_Speed는 1초에 이동할 거리이므로 시간변화량(초)를 곱하면  시간변화만큼 얼마나 이동해야할지 계산한다.
	m_Velocity = mathHelper::Vector2F(m_Direction) * m_Speed * GameApp::m_deltaTime;
	Location += m_Velocity;

	// 중력가속도가 시간당 속도변화량 이므로 시간변화량을 곱해서 Y속도에 적용한다.
	m_VelocityY -= m_GravityAcceleration * GameApp::m_deltaTime;
	
	// Y속도로 Y위치를 계산한다.
	Location.y += m_VelocityY * GameApp::m_deltaTime;

	// 최종 속도를 계산한다.
	m_Velocity.y = m_Velocity.y + m_VelocityY; 


	if (Location.y <= 0.0f)
	{
		m_IsJumping = false;
		m_VelocityY = 0.0f;
		m_GravityAcceleration =0.0f;
	}

	//새로 계산된 위치를 적용한다.
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

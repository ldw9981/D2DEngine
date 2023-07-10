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
	m_GravityAcceleration = m_Gravity * m_GravityScale;	// 중력 가속도  
	m_JumpAcceleration = 6;		//점프 가속도
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
	m_Velocity.x = (mathHelper::Vector2F(m_Direction) * m_Speed * GameApp::m_deltaTime).x;	

	// 중력가속도가 시간당 속도변화량 이므로 시간변화량을 곱해서 Y속도에 적용한다.
	m_Velocity.y -= m_GravityAcceleration * GameApp::m_deltaTime;
	Location += m_Velocity;
	
	// 외부에서 착지 판단을 해야하는데 일단 0.0f보다 작거나 같으면 착지한 것으로 판단한다.
	if (Location.y <= 0.0f)
	{
		m_IsJumping = false;
		m_Velocity.y = 0.0f;
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
		m_GravityAcceleration = SideMovementComponent::m_Gravity * m_GravityScale;
		m_IsJumping = true;
		m_Velocity.y = m_JumpAcceleration;
	}
}

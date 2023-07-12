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
	m_GravityScaled = m_Gravity * m_GravityScale;	// 중력 가속도  
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

	// x축 이동 속도
	m_Velocity.x = (mathHelper::Vector2F(m_Direction) * m_Speed).x;
	
	// y축 이동 속도
	m_SpeedY += m_GravityScaled * GameApp::m_deltaTime;	// y축 이동속도는 중력에 의해 점점 빨라진다.
	m_SpeedY = min(m_MaxSpeedY,m_SpeedY);				// 종단속도로 제한한다.
	m_Velocity.y = (mathHelper::Vector2F(0.0f, -1.0f) * m_SpeedY).y;  

	//D2DHelper::Log(L"%f,%f\n", m_Velocity.x, m_Velocity.y);
	Location = Location + m_Velocity * GameApp::m_deltaTime;	// 시간변화 만큼 이동
	Location.y = max(0.0f, Location.y);						// 바닥이 없을때 무한낙하 방지 
	// 외부에서 착지 판단을 해야하는데 일단 0.0f보다 작거나 같으면 착지한 것으로 판단한다.	
	if (Location.y <= 0.0f)
	{
		EndJump();
	}	

	//새로 계산된 위치를 적용한다.
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
		m_SpeedY = m_JumpSpeed * -1; // 점프는 중력의 반대
	}
}

void SideMovementComponent::EndJump()
{
	m_IsJumping = false;
	m_SpeedY = 0.0f;
	//m_GravityScaled = 0.0f;	// 중력을 끄는게 맞을까?
}

#include "pch.h"
#include "MovementComponent.h"
#include "SceneComponent.h"
#include "GameApp.h"
#include "Helper.h"


// 가속도 개념없이 일정한 속도로 이동한다.
void MovementComponent::Update()
{
	assert(m_pRootSceneComponent != nullptr);
	// 현재 위치를 가져온다.
	mathHelper::Vector2F Location = m_pRootSceneComponent->GetRelativeLocation();
	m_Velocity = m_Direction * m_Speed;		

	// 새로운 위치를 계산한다.
	Location += m_Velocity * GameApp::m_deltaTime;	

	//새로 계산된 위치를 적용한다.
	m_pRootSceneComponent->SetRelativeLocation(Location);	
	m_pRootSceneComponent->SetVelocity(m_Velocity);
}

void MovementComponent::SetDirection(const mathHelper::Vector2F& Direction)
{
	m_Direction = Direction;
	m_Direction.Normalize();
}


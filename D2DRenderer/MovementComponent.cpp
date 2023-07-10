#include "pch.h"
#include "MovementComponent.h"
#include "SceneComponent.h"
#include "GameApp.h"
#include "Helper.h"



void MovementComponent::Update()
{
	assert(m_pUpdateTarget != nullptr);
	mathHelper::Vector2F Location = m_pUpdateTarget->GetRelativeLocation();
	// m_Speed는 1초에 이동할 거리이므로 시간변화량(초)를 곱하면  시간변화만큼 얼마나 이동해야할지 계산한다.
	float Distance = m_Speed * GameApp::m_deltaTime;

	m_Velocity = mathHelper::Vector2F(m_Direction) * Distance;
	Location += m_Velocity;
	
	//새로 계산된 위치를 적용한다.
	m_pUpdateTarget->SetRelativeLocation(Location.x, Location.y);	
}

void MovementComponent::SetDirection(const mathHelper::Vector2F& Direction)
{
	m_Direction = D2DHelper::NormalizeVector(Direction);	

}


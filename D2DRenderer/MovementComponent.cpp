#include "pch.h"
#include "MovementComponent.h"
#include "SceneComponent.h"
#include "GameApp.h"
#include "Helper.h"

void MovementComponent::Update()
{
	assert(m_pUpdateTarget != nullptr);
	D2D1_VECTOR_2F Location = m_pUpdateTarget->GetRelativeLocation();	
	// m_Speed는 1초에 이동할 거리이므로 시간변화량(초)를 곱하면  시간변화만큼 얼마나 이동해야할지 계산한다.
	float Distance = m_Speed * GameApp::m_deltaTime;

	// 방향에 각각 거리를 곱하여 이동한다.
	Location.x = Location.x + m_Direction.x * Distance;
	Location.y = Location.y + m_Direction.y * Distance;	
	
	//새로 계산된 위치를 적용한다.
	m_pUpdateTarget->SetRelativeLocation(Location.x, Location.y);	
}

void MovementComponent::SetDirection(const D2D_VECTOR_2F& Direction)
{
	m_Direction = D2DHelper::NormalizeVector(Direction);	

}


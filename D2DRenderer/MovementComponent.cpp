#include "pch.h"
#include "MovementComponent.h"
#include "SceneComponent.h"
#include "GameApp.h"


bool MovementComponent::Initialize()
{
	assert(m_pRootComponent!=nullptr);
	return true;
}

void MovementComponent::Update()
{
	D2D1_VECTOR_2F Location = m_pRootComponent->GetRelativeLocation();	
	// m_Speed는 1초에 이동할 거리이므로 시간변화량(초)를 곱하면  시간변화만큼 얼마나 이동해야할지 계산한다.
	float Distance = m_Speed * GameApp::m_deltaTime;

	// 방향에 각각 거리를 곱하여 이동한다.
	Location.x = Location.x + m_Direction.x * Distance;
	Location.y = Location.y + m_Direction.y * Distance;	
	
	//새로 계산된 위치를 적용한다.
	m_pRootComponent->SetRelativeLocation(Location.x, Location.y);	
}

void MovementComponent::SetDirection(float x, float y)
{
	// 방향 벡터를 정규화 Normalize 한다.
	float length = std::sqrt(x * x + y * y);

	if (length != 0.0f) {
		m_Direction.x = x /length;
		m_Direction.y = y /length;
	}
	else {
		m_Direction.x = 0.0f;
		m_Direction.y = 0.0f;
	}

}

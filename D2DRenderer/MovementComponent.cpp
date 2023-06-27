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
	float Distance = m_Speed * GameApp::m_deltaTime;
	Location.x = Location.x + m_Direction.x * Distance;
	Location.y = Location.y + m_Direction.y * Distance;	
	m_pRootComponent->SetRelativeLocation(Location.x, Location.y);	
}

void MovementComponent::SetDirection(float x, float y)
{
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

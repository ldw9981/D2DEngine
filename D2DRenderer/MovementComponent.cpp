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
	D2D1_VECTOR_2F Location;
	m_pRootComponent->GetWorldLocation(&Location);



	float Distance = m_Speed * GameApp::m_deltaTime;

	Location.x = Location.x + m_Direction.x * Distance;
	Location.y = Location.y + m_Direction.y * Distance;
	
}

void MovementComponent::SetDirection(float x, float y)
{
	
	//normalize(x, y);

	m_Direction.x = x; m_Direction.y = y;
}

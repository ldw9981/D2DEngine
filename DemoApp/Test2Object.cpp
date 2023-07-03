#include "framework.h"
#include "Test2Object.h"
#include "../D2DRenderer/SceneComponent.h"
#include "../D2DRenderer/BoxComponent.h"
#include "../D2DRenderer/Component.h"
#include "../D2DRenderer/AnimationComponent.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/SphereComponent.h"
#include "../D2DRenderer/TextComponent.h"
#include "../D2DRenderer/MovementComponent.h"
#include "../D2DRenderer/FSMComponent.h"
#include "../D2DRenderer/FSMTransition.h"
#include "../D2DRenderer/FSMInstance.h"
#include "StateIdle.h"
#include "FSMInstanceTest2.h"
/*
	DemoObject Hierachy
	- MovementComponent
	- [Root] AnimationComponent
	- FSMComponent
 */

Test2Object::Test2Object()
{
	m_pMovementComponent = CreateComponent<MovementComponent>();

	m_pAnimationComponent = CreateComponent<AnimationComponent>();
	m_pAnimationComponent->SetAnimationAsset(std::wstring(L"Test"));
	m_pAnimationComponent->SetRelativeLocation(100.0f, 100.0f);
	m_pAnimationComponent->SetAnimation(L"Run", false, true);
	SetRootComponent(m_pAnimationComponent);

	m_pMovementComponent->SetRootComponent(m_pAnimationComponent);
	m_pMovementComponent->SetSpeed(300.0f);
	//m_pMovementComponent->SetDirection(float(rand() % 90) + 1, float(rand() % 90) + 1);
	

	m_pFSMComponent = CreateComponent<FSMComponent>();
	FSMInstance* pFSMInstance = m_pFSMComponent->CreateInstance<FSMInstanceTest2>();
	m_pAnimationComponent->AddListener(pFSMInstance);
}

Test2Object::~Test2Object()
{

}

void Test2Object::Update()
{

	D2D_VECTOR_2F Location, Direction;
	Location = m_pAnimationComponent->GetWorldLocation();
	Direction = m_pMovementComponent->GetDirection();

	
	if ( Location.x  > 1500.0f)
	{
		m_pMovementComponent->SetDirection(-1.0f, Direction.y);
	}
	else if (Location.x < -1500.0f)
	{
		m_pMovementComponent->SetDirection(1.0f, Direction.y);
	}
	if (Location.y > 1500.0f)
	{
		m_pMovementComponent->SetDirection(Direction.x, -1.0f);
	}
	else if (Location.y < -1500.0f)
	{
		m_pMovementComponent->SetDirection(Direction.x, 1.0f);
	}
	

	__super::Update();
}

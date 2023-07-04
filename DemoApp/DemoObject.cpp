#include "framework.h"
#include "DemoObject.h"
#include "../D2DRenderer/SceneComponent.h"
#include "../D2DRenderer/BoxComponent.h"
#include "../D2DRenderer/Component.h"
#include "../D2DRenderer/AnimationComponent.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/SphereComponent.h"
#include "../D2DRenderer/TextComponent.h"
#include "../D2DRenderer/MovementComponent.h"


/*
	DemoObject Hierachy
	- MovementComponent
	- [Root] SceneComponent
		+ [Child] ShpereComponent
		|	+ [Child] BoxComponent
		|		+ [Child] AnimationComponent
		+ [Child] TextComponent
 */

DemoObject::DemoObject()
{
	m_pMovementComponent = CreateComponent<MovementComponent>(L"MovementComponent");

	m_pSceneComponent = CreateComponent<SceneComponent>(L"SceneComponent");
	m_pSceneComponent->Initialize();
	SetRootComponent(m_pSceneComponent);

	m_pMovementComponent->SetUpdateTarget(m_pSceneComponent);
	m_pMovementComponent->SetSpeed(300.0f);
	m_pMovementComponent->SetDirection(float(rand() % 90) + 1, float(rand() % 90) + 1);



	m_pSphereComponent = CreateComponent<SphereComponent>(L"SphereComponent");
	m_pSphereComponent->SetRadius(10.0f);
	m_pSphereComponent->m_Color = D2D1::ColorF(D2D1::ColorF::Yellow);

	m_pSphereComponent->AttachToComponent(m_pSceneComponent);

	m_pTextComponent = CreateComponent<TextComponent>(L"TextComponent");
	m_pTextComponent->SetString(std::wstring(L"Root"));
	m_pTextComponent->Initialize();
	m_pTextComponent->AttachToComponent(m_pSceneComponent);

	m_pBoxComponent = CreateComponent<BoxComponent>(L"BoxComponent");
	m_pBoxComponent->m_Rect = D2D1_RECT_F{ -25.0f,-25.0f,25.0f,25.0f };
	m_pBoxComponent->m_Color = D2D1::ColorF(D2D1::ColorF::Red);
	m_pBoxComponent->SetRelativeLocation(100.0f, 100.0f);
	m_pBoxComponent->Initialize();
	m_pBoxComponent->AttachToComponent(m_pSphereComponent);


	m_pAnimationComponent = CreateComponent<AnimationComponent>(L"AnimationComponent");
	m_pAnimationComponent->SetAnimationAsset(std::wstring(L"Test"));
	m_pAnimationComponent->SetRelativeLocation(100.0f, 100.0f);
	m_pAnimationComponent->Initialize();
	m_pAnimationComponent->AttachToComponent(m_pBoxComponent);
	m_pAnimationComponent->SetAnimation(L"Run", false, true);
}

DemoObject::~DemoObject()
{

}

void DemoObject::Update()
{
	m_pSphereComponent->AddRelativeRotation(30.0f * GameApp::m_deltaTime);
	m_pBoxComponent->AddRelativeRotation(90.0f * GameApp::m_deltaTime);
	
	D2D_VECTOR_2F Location,Direction;
	Location = m_pSceneComponent->GetWorldLocation();
	Direction = m_pMovementComponent->GetDirection();

	/*
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
	*/

	__super::Update();
}

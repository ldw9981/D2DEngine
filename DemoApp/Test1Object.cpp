#include "framework.h"
#include "Test1Object.h"
#include "../D2DRenderer/SceneComponent.h"
#include "../D2DRenderer/BoxComponent.h"
#include "../D2DRenderer/Component.h"
#include "../D2DRenderer/AnimationComponent.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/SphereComponent.h"
#include "../D2DRenderer/TextComponent.h"
#include "../D2DRenderer/MovementComponent.h"

/*
	Test1Object Hierachy
	- MovementComponent
	- [Root] SceneComponent
		+ [Child] ShpereComponent
		|	+ [Child] BoxComponent
		|
		+ [Child] TextComponent
 */

Test1Object::Test1Object()
{
	m_pMovementComponent = CreateComponent<MovementComponent>(L"MovementComponent");

	m_pSceneComponent = CreateComponent<SceneComponent>(L"SceneComponent");
	m_pSceneComponent->Initialize();
	SetRootComponent(m_pSceneComponent);

	m_pMovementComponent->SetUpdateTarget(m_pSceneComponent);
	//m_pMovementComponent->SetSpeed(10.0f);
	//m_pMovementComponent->SetDirection(float(rand() % 90) + 1, float(rand() % 90) + 1);



	m_pSphereComponent = CreateComponent<SphereComponent>(L"SphereComponent");
	m_pSphereComponent->SetRadius(10.0f);
	m_pSphereComponent->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));

	m_pSphereComponent->AttachToComponent(m_pSceneComponent);

	m_pTextComponent = CreateComponent<TextComponent>(L"TextComponent");
	m_pTextComponent->SetString(std::wstring(L"Root"));

	m_pTextComponent->AttachToComponent(m_pSceneComponent);

	m_pBoxComponent = CreateComponent<BoxComponent>(L"BoxComponent");
	m_pBoxComponent->SetExtend(50.0f,50.0f);
	m_pBoxComponent->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
//	m_pBoxComponent->SetRelativeLocation(100.0f, 100.0f);

	m_pBoxComponent->AttachToComponent(m_pSphereComponent);
}

Test1Object::~Test1Object()
{

}

void Test1Object::Update()
{
	//m_pSphereComponent->AddRelativeRotation(30.0f * GameApp::m_deltaTime);
	//m_pBoxComponent->AddRelativeRotation(90.0f * GameApp::m_deltaTime);
	__super::Update();
}

void Test1Object::OnCollide(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void Test1Object::OnAnimationEnd(AnimationComponent* pAnimationComponent, const std::wstring& AnimationName)
{

}

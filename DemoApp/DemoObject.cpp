#include "framework.h"
#include "DemoObject.h"
#include "../D2DRenderer/SceneComponent.h"
#include "../D2DRenderer/BoxComponent.h"
#include "../D2DRenderer/Component.h"
#include "../D2DRenderer/AnimationComponent.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/SphereComponent.h"

DemoObject::DemoObject()
	:m_pBoxComponent(nullptr), m_pAnimationComponent(nullptr), m_pSphereComponent(nullptr)
{

}

DemoObject::~DemoObject()
{

}

bool DemoObject::Initialize()
{
	m_pSphereComponent = CreateComponent<SphereComponent>();
	SetRootComponent(m_pSphereComponent);
	m_pSphereComponent->SetRadius(10.0f);
	m_pSphereComponent->m_Color = D2D1::ColorF(D2D1::ColorF::Yellow);
	m_pSphereComponent->Initialize();

	m_pBoxComponent = m_pSphereComponent->CreateChild<BoxComponent>();
	m_pBoxComponent->m_Rect = D2D1_RECT_F{ -25.0f,-25.0f,25.0f,25.0f };
	m_pBoxComponent->m_Color = D2D1::ColorF(D2D1::ColorF::Red);
	m_pBoxComponent->SetRelativeLocation(100.0f, 0.0f);
	m_pBoxComponent->Initialize();

	m_pAnimationComponent = m_pBoxComponent->CreateChild<AnimationComponent>();
	m_pAnimationComponent->SetAnimationAssetPath(std::wstring(L"Test"));
	m_pAnimationComponent->SetRelativeLocation(100.0f,0.0f);
	m_pAnimationComponent->Initialize();
	
	return true;
}

void DemoObject::Update()
{
	m_pSphereComponent->AddRelativeRotation(15.0f * GameApp::m_deltaTime);
	m_pBoxComponent->AddRelativeRotation(30.0f * GameApp::m_deltaTime);
	m_pAnimationComponent->AddRelativeRotation(60.0f * GameApp::m_deltaTime);
	__super::Update();
}

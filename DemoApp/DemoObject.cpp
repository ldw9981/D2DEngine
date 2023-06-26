#include "framework.h"
#include "DemoObject.h"
#include "../D2DRenderer/SceneComponent.h"
#include "../D2DRenderer/BoxComponent.h"
#include "../D2DRenderer/Component.h"
#include "../D2DRenderer/AnimationComponent.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/SphereComponent.h"
#include "../D2DRenderer/TextComponent.h"

DemoObject::DemoObject()
	:m_pBoxComponent(nullptr), 
	m_pAnimationComponent(nullptr), 
	m_pSphereComponent(nullptr),
	m_pSceneComponent(nullptr),
	m_pTextComponent(nullptr)
{

}

DemoObject::~DemoObject()
{

}

bool DemoObject::Initialize()
{
	m_pSceneComponent = CreateComponent<SceneComponent>();
	m_pSceneComponent->Initialize();
	SetRootComponent(m_pSceneComponent);

	m_pSphereComponent = CreateComponent<SphereComponent>();
	m_pSphereComponent->SetRadius(10.0f);
	m_pSphereComponent->m_Color = D2D1::ColorF(D2D1::ColorF::Yellow);
	m_pSphereComponent->Initialize();
	m_pSphereComponent->AttachToComponent(m_pSceneComponent);

	m_pTextComponent = CreateComponent<TextComponent>();
	m_pTextComponent->SetString(std::wstring(L"Root"));
	m_pTextComponent->Initialize();
	m_pTextComponent->AttachToComponent(m_pSceneComponent);



	m_pBoxComponent = CreateComponent<BoxComponent>();
	m_pBoxComponent->m_Rect = D2D1_RECT_F{ -25.0f,-25.0f,25.0f,25.0f };
	m_pBoxComponent->m_Color = D2D1::ColorF(D2D1::ColorF::Red);
	m_pBoxComponent->SetRelativeLocation(100.0f,100.0f);
	m_pBoxComponent->Initialize();
	m_pBoxComponent->AttachToComponent(m_pSphereComponent);

	
	m_pAnimationComponent = CreateComponent<AnimationComponent>();
	m_pAnimationComponent->SetAnimationAssetPath(std::wstring(L"Test"));
	m_pAnimationComponent->Initialize();
	m_pAnimationComponent->AttachToComponent(m_pBoxComponent);
	
	return true;
}

void DemoObject::Update()
{
	m_pSphereComponent->AddRelativeRotation(30.0f * GameApp::m_deltaTime);
	m_pBoxComponent->AddRelativeRotation(90.0f * GameApp::m_deltaTime);
	
	__super::Update();
}

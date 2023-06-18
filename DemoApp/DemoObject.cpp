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

bool DemoObject::Init()
{
	const D2D_SIZE_U& size = GameApp::m_pInstance->GetClientSize();

	m_pBoxComponent = CreateComponent<BoxComponent>();
	SetRootComponent(m_pBoxComponent);
	m_pBoxComponent->m_Rect = D2D1_RECT_F { -50.0f,-50.0f,50.0f,50.0f};
	m_pBoxComponent->m_Color = D2D1::ColorF(D2D1::ColorF::Red);
	m_pBoxComponent->SetRelativePosition((float)size.width/2, (float)size.height/2);

	m_pSphereComponent = m_pBoxComponent->CreateChild<SphereComponent>();
	m_pSphereComponent->SetRadius(10.0f);
	m_pSphereComponent->m_Color = D2D1::ColorF(D2D1::ColorF::Yellow);
	m_pSphereComponent->SetRelativePosition(150.0f, 0.0f);


	m_pAnimationComponent = m_pSphereComponent->CreateChild<AnimationComponent>();
	m_pAnimationComponent->SetAnimationAssetPath(std::wstring(L"Test"));
	m_pAnimationComponent->SetRelativePosition(30.0f,0.0f);
	m_pAnimationComponent->Init();

	
	return true;
}

void DemoObject::Update()
{


	m_pBoxComponent->AddRelativeRotation(10.0f * GameApp::m_deltaTime);

	m_pSphereComponent->AddRelativeRotation(90.0f * GameApp::m_deltaTime);

	__super::Update();
}

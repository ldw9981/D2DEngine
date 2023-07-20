#include "framework.h"
#include "PlatformObject.h"
#include "../D2DRenderer/SceneComponent.h"
#include "../D2DRenderer/BoxComponent.h"
#include "../D2DRenderer/Component.h"
#include "../D2DRenderer/AnimationComponent.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/SphereComponent.h"
#include "../D2DRenderer/TextComponent.h"
#include "../D2DRenderer/MovementComponent.h"
#include "../D2DRenderer/BitmapComponent.h"

/*
	Test1Object Hierachy
	- MovementComponent
	- [Root] SceneComponent
		+ [Child] ShpereComponent
		|	+ [Child] BoxComponent
		|
		+ [Child] TextComponent
 */

PlatformObject::PlatformObject(World* pOwner)
	:GameObject(pOwner)
{
	m_pBoxComponent = CreateComponent<BoxComponent>("BoxComponent");
	m_pBoxComponent->SetExtend(35.0f, 35.0f);
	m_pBoxComponent->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	m_pBoxComponent->SetCollisionType(CollisionType::Block);
	SetRootComponent(m_pBoxComponent);


	m_pBitmapComponent = CreateComponent<BitmapComponent>("BitmapComponent");
	m_pBitmapComponent->SetBitmap(L"../Resource/Tiles/grassmid.png");
	m_pBitmapComponent->SetRelativeLocation(mathHelper::Vector2F(-35,35));
	m_pBitmapComponent->AttachToComponent(m_pBoxComponent);

}

PlatformObject::~PlatformObject()
{

}

void PlatformObject::Update()
{
	//m_pSphereComponent->AddRelativeRotation(30.0f * GameApp::m_deltaTime);
	//m_pBoxComponent->AddRelativeRotation(90.0f * GameApp::m_deltaTime);
	__super::Update();
}

void PlatformObject::OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void PlatformObject::OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void PlatformObject::OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void PlatformObject::OnAnimationEnd(AnimationComponent* pAnimationComponent, const std::string& AnimationName)
{

}

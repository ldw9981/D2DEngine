#include "framework.h"
#include "FlatformObject.h"
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

FlatformObject::FlatformObject()
{
	m_pBoxComponent = CreateComponent<BoxComponent>(L"BoxComponent");
	m_pBoxComponent->SetExtend(400.0f, 50.0f);
	m_pBoxComponent->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
	m_pBoxComponent->SetCollisionType(CollisionType::Overlap);	
	SetRootComponent(m_pBoxComponent);

	m_pLeftBlock = CreateComponent<BoxComponent>(L"LeftBlock");
	m_pLeftBlock->AttachToComponent(m_pBoxComponent);
	m_pLeftBlock->SetExtend(2.5f, 48.0f);
	m_pLeftBlock->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	m_pLeftBlock->SetCollisionType(CollisionType::Block);
	m_pLeftBlock->SetRelativeLocation(mathHelper::Vector2F(-400.0f,0.0f));

	m_pRightBlock = CreateComponent<BoxComponent>(L"RightBlock");
	m_pRightBlock->AttachToComponent(m_pBoxComponent);
	m_pRightBlock->SetExtend(2.5f, 48.0f);
	m_pRightBlock->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	m_pRightBlock->SetCollisionType(CollisionType::Block);
	m_pRightBlock->SetRelativeLocation(mathHelper::Vector2F(400.0f, 0.0f));

	m_pTextComponent = CreateComponent<TextComponent>(L"TextComponent");
	m_pTextComponent->SetString(std::wstring(L"Root"));
	m_pTextComponent->AttachToComponent(m_pBoxComponent);


}

FlatformObject::~FlatformObject()
{

}

void FlatformObject::Update()
{
	//m_pSphereComponent->AddRelativeRotation(30.0f * GameApp::m_deltaTime);
	//m_pBoxComponent->AddRelativeRotation(90.0f * GameApp::m_deltaTime);
	__super::Update();
}

void FlatformObject::OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void FlatformObject::OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void FlatformObject::OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void FlatformObject::OnAnimationEnd(AnimationComponent* pAnimationComponent, const std::wstring& AnimationName)
{

}

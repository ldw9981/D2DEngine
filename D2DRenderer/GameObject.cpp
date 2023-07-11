#include "pch.h"
#include "GameObject.h"
#include "D2DRenderer.h"
#include "GameApp.h"
#include "SceneComponent.h"
#include "RenderComponent.h"
#include "Component.h"


GameObject::GameObject()
	:m_pRootComponent(nullptr), m_bIsCullObject(true), 
	m_pParentObject(nullptr), m_pOwnerWorld(nullptr)
{

}




void GameObject::SetRootComponent(SceneComponent* pRootComponent)
{
	m_pRootComponent = pRootComponent;
}

SceneComponent* GameObject::GetRootComponent() const
{
	return m_pRootComponent;
}

void GameObject::Update()
{
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Update();
	}
}

void GameObject::Render(ID2D1RenderTarget* pRenderTarget)
{
	for (auto& pComponent : m_OwnedComponents)
	{
		// 보관하고 있는 컴포넌트 인스턴스가 SceneComponent 일때만 Render를 호출한다.
		RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(pComponent);
		if (pRenderComponent)
		{
			pRenderComponent->Render(pRenderTarget);
		}
	}
}

D2D_VECTOR_2F GameObject::GetWorldLocation()
{
	return m_pRootComponent ? m_pRootComponent->GetRelativeLocation() : D2D_VECTOR_2F();
}

void GameObject::SetWorldLocation(const mathHelper::Vector2F& Location)
{
	if (m_pRootComponent)
	{
		m_pRootComponent->SetRelativeLocation(Location);
	}
}

void GameObject::SetParentObject(GameObject* pParentObject)
{
	if (pParentObject == nullptr)
	{
		m_pParentObject = nullptr;
		if (m_pRootComponent)
		{
			m_pRootComponent->SetParentScene(nullptr);
		}
		return;
	}
	
	// 부모설정하고  루트끼리 부모-자식 연결 시킨다. 
	m_pParentObject = pParentObject;
	SceneComponent* pRootComponent = pParentObject->GetRootComponent();
	assert(pRootComponent != nullptr);
	assert(m_pRootComponent != nullptr);
	
	if (m_pRootComponent)
	{
		m_pRootComponent->SetParentScene(pRootComponent);
	}
}

void GameObject::TakeDamage(float Damage, GameObject* pAttacker)
{
	m_OnTakeDamage.InvokeCallbacks(Damage, pAttacker);
}


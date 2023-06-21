#include "pch.h"
#include "GameObject.h"
#include "D2DRenderer.h"
#include "GameApp.h"
#include "SceneComponent.h"
#include "Component.h"


GameObject::GameObject()
:m_pRootComponent(nullptr)
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
	for (auto& pComponent : m_OwnedComponent)
	{
		pComponent->Update();
	}
}

void GameObject::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (m_pRootComponent)
	{
		m_pRootComponent->Render(pRenderTarget);
	}
}

D2D_VECTOR_2F GameObject::GetLocation()
{
	return m_pRootComponent ? m_pRootComponent->GetRelativeLocation() : D2D_VECTOR_2F();
}

void GameObject::SetLocation(float x, float y)
{
	if (m_pRootComponent)
	{
		m_pRootComponent->SetRelativeLocation(x, y);
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

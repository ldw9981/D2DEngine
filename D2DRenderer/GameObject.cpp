#include "pch.h"
#include "GameObject.h"
#include "D2DRenderer.h"
#include "GameApp.h"
#include "SceneComponent.h"
#include "RenderComponent.h"
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
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Update();
	}
}

void GameObject::Render(ID2D1RenderTarget* pRenderTarget)
{
	for (auto& pComponent : m_OwnedComponents)
	{
		// �����ϰ� �ִ� ������Ʈ �ν��Ͻ��� SceneComponent �϶��� Render�� ȣ���Ѵ�.
		RenderComponent* pRenderComponent = dynamic_cast<RenderComponent*>(pComponent);
		if (pRenderComponent)
		{
			pRenderComponent->Render(pRenderTarget);
		}
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
	
	// �θ����ϰ�  ��Ʈ���� �θ�-�ڽ� ���� ��Ų��. 
	m_pParentObject = pParentObject;
	SceneComponent* pRootComponent = pParentObject->GetRootComponent();
	assert(pRootComponent != nullptr);
	assert(m_pRootComponent != nullptr);
	
	if (m_pRootComponent)
	{
		m_pRootComponent->SetParentScene(pRootComponent);
	}
}



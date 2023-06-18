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

GameObject::~GameObject()
{
	for (auto& pComponent : m_OwnedComponent)
	{
		delete pComponent;
	}
	m_OwnedComponent.clear();
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

#include "pch.h"
#include "GameObject.h"
#include "GameApp.h"

GameObject::GameObject()
:m_pRootComponent(nullptr)
{

}

GameObject::~GameObject()
{
	if (m_pRootComponent)
	{
		delete m_pRootComponent;
		m_pRootComponent = nullptr;
	}
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
	if (m_pRootComponent)
	{
		m_pRootComponent->Update();
	}
}

void GameObject::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (m_pRootComponent)
	{
		m_pRootComponent->Render(pRenderTarget);
	}
}

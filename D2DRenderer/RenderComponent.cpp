#include "pch.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent()
:m_bVisible(true),m_iZOrder(0)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Update()
{
	__super::Update();
}

void RenderComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

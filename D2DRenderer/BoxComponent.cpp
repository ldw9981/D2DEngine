#include "pch.h"
#include "BoxComponent.h"
#include "D2DRenderer.h"

BoxComponent::BoxComponent()
:m_Rect({0})
{

}


BoxComponent::~BoxComponent()
{

}

void BoxComponent::Update()
{
	__super::Update();
}

void BoxComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	ID2D1SolidColorBrush* pBrush = D2DRenderer::m_Instance->GetBrush();
	pBrush->SetColor(m_Color);	
	pRenderTarget->SetTransform(m_WorldTransform);
	pRenderTarget->DrawRectangle(m_Rect,pBrush);	
}

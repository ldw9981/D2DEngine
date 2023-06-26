#include "pch.h"
#include "BoxComponent.h"
#include "D2DRenderer.h"
#include "RendererHelper.h"

BoxComponent::BoxComponent()
:m_Rect({0})
{

}


BoxComponent::~BoxComponent()
{

}


void BoxComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	ID2D1SolidColorBrush* pBrush = D2DRenderer::m_Instance->GetBrush();
	pBrush->SetColor(m_Color);	
	
	D2D1_MATRIX_3X2_F Transform =  m_WorldTransform * D2DRenderer::m_CameraTransformInv;
	

	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawRectangle(m_Rect,pBrush);	

	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

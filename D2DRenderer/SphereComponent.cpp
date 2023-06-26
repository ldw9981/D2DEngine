#include "pch.h"
#include "SphereComponent.h"
#include "D2DRenderer.h"
#include "RendererHelper.h"

SphereComponent::SphereComponent()
	: m_Radius(5.0f)
	, m_Color(D2D1::ColorF(D2D1::ColorF::Red))
{
}

SphereComponent::~SphereComponent()
{
}

void SphereComponent::Update()
{
	__super::Update();
}

void SphereComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	ID2D1SolidColorBrush* pBrush = D2DRenderer::m_Instance->GetBrush();
	pBrush->SetColor(m_Color);

	D2D1_MATRIX_3X2_F Transform = m_WorldTransform * D2DRenderer::m_CameraTransformInv;
	

	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(0, 0), m_Radius, m_Radius), pBrush);
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

#include "pch.h"
#include "SphereComponent.h"
#include "D2DRenderer.h"
#include "Helper.h"
#include "GameObject.h"

SphereComponent::SphereComponent(GameObject* pOwner, const std::wstring& Name)
	: RenderComponent(m_pOwner,Name), m_Radius(5.0f)
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

	// ����->ī�޶�->��ũ�� ��ǥ��� ��ȯ�Ѵ�. 
	// m_ScreenTransform �� ScaleY -1 �̹Ƿ� �Ųٷ� �׷�����. 
	// m_RenderTransform���� ����ó�� ��ȯ�� ScaleY -1�� �����ش�.
	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;
	

	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(0, 0), m_Radius, m_Radius), pBrush);
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

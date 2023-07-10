#include "pch.h"
#include "SphereComponent.h"
#include "D2DRenderer.h"
#include "Helper.h"
#include "GameObject.h"


SphereComponent::SphereComponent(GameObject* pOwner, const std::wstring& Name)
	: ColliderComponent(m_pOwner,Name), m_Radius(5.0f)
{
}

SphereComponent::~SphereComponent()
{
}


void SphereComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	ID2D1SolidColorBrush* pBrush = D2DRenderer::m_Instance->GetBrush();
	pBrush->SetColor(GetColor());

	// 월드->카메라->스크린 좌표계로 변환한다. 
	// m_ScreenTransform 의 ScaleY -1 이므로 거꾸로 그려진다. 
	// m_RenderTransform에서 제일처음 변환에 ScaleY -1을 곱해준다.
	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;
	

	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(0, 0), m_Radius, m_Radius), pBrush);
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

bool SphereComponent::IsCollide(ColliderComponent* pOtherComponent)
{
	return false;
}

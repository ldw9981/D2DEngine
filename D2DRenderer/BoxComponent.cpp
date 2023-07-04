#include "pch.h"
#include "BoxComponent.h"
#include "D2DRenderer.h"
#include "Helper.h"

BoxComponent::BoxComponent(GameObject* pOwner, const std::wstring& Name)
	:RenderComponent(pOwner, Name),m_Rect({0})
{
	m_Color= D2D1::ColorF(D2D1::ColorF::White);
}


BoxComponent::~BoxComponent()
{

}


void BoxComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	ID2D1SolidColorBrush* pBrush = D2DRenderer::m_Instance->GetBrush();
	pBrush->SetColor(m_Color);	
	
	// 월드->카메라->스크린 좌표계로 변환한다. Screen 의 y스케일이 -1 이므로 거꾸로 그려진다. 제일처음 변환에 -1을 곱해준다.
	D2D1_MATRIX_3X2_F Transform = Matrix3x2F::Scale(1.0f, -1.0f) * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;
	

	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawRectangle(m_Rect,pBrush);	

	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

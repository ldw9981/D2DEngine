#include "pch.h"
#include "BitmapComponent.h"
#include "D2DRenderer.h"


void BitmapComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	DrawDebugWorldTransform(pRenderTarget);

	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;

	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawBitmap(m_pBitmap);
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

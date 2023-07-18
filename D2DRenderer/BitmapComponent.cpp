#include "pch.h"
#include "BitmapComponent.h"
#include "D2DRenderer.h"


void BitmapComponent::SetBitmap(std::wstring val)
{
	ID2D1Bitmap* result = nullptr;
	if (!D2DRenderer::m_Instance->CreateSharedD2DBitmapFromFile(val,&result))
		return;	
	
	if (m_pBitmap!=nullptr)
	{
		D2DRenderer::m_Instance->ReleaseSharedD2DBitmap(m_pBitmap);
	}
	m_FilePath = val;
	m_pBitmap = result;	
}

void BitmapComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	DrawDebugWorldTransform(pRenderTarget);

	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;

	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawBitmap(m_pBitmap);
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

void BitmapComponent::SerializeOut(nlohmann::ordered_json& object)
{
	RenderComponent::SerializeOut(object);
	object["m_FilePath"] = m_FilePath;
}
 
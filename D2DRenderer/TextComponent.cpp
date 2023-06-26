#include "pch.h"
#include "TextComponent.h"
#include "D2DRenderer.h"
#include "RendererHelper.h"

TextComponent::TextComponent()
	:m_String(L"Text"), m_Color(D2D1::ColorF(D2D1::ColorF::White)),m_Rect(D2D1::RectF(0,0,100,100))
{

}

TextComponent::~TextComponent()
{
}

bool TextComponent::Initialize()
{
	return false;
}


void TextComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	D2D1_MATRIX_3X2_F Transform = m_WorldTransform * D2DRenderer::m_CameraTransformInv;
	ModifyMatrixtForBottomUpScreenSpace(pRenderTarget, Transform);

	pRenderTarget->SetTransform(Transform);
	D2DRenderer::m_Instance->DrawText(pRenderTarget, m_String, m_Rect, m_Color);
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

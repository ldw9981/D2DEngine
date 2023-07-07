#include "pch.h"
#include "TextComponent.h"
#include "D2DRenderer.h"
#include "Helper.h"
#include "GameObject.h"

TextComponent::TextComponent(GameObject* pOwner, const std::wstring& Name)
	:RenderComponent(pOwner,Name),m_String(L"Text"), m_Color(D2D1::ColorF(D2D1::ColorF::White)),m_Rect(D2D1::RectF(0,0,100,100))
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
	// 월드->카메라->스크린 좌표계로 변환한다. 
	// m_ScreenTransform 의 ScaleY -1 이므로 거꾸로 그려진다. 
	// m_RenderTransform에서 제일처음 변환에 ScaleY -1을 곱해준다.
	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;
	
	pRenderTarget->SetTransform(Transform);
	D2DRenderer::m_Instance->DrawText(pRenderTarget, m_String, m_Rect, m_Color);  //시간이 엄청 오래 걸립니다.
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

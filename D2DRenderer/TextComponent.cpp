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
	// ����->ī�޶�->��ũ�� ��ǥ��� ��ȯ�Ѵ�. 
	// m_ScreenTransform �� ScaleY -1 �̹Ƿ� �Ųٷ� �׷�����. 
	// m_RenderTransform���� ����ó�� ��ȯ�� ScaleY -1�� �����ش�.
	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform * D2DRenderer::m_ScreenTransform;
	
	pRenderTarget->SetTransform(Transform);
	D2DRenderer::m_Instance->DrawText(pRenderTarget, m_String, m_Rect, m_Color);  //�ð��� ��û ���� �ɸ��ϴ�.
	D2DRenderer::m_Instance->DrawCrossLine(pRenderTarget);
}

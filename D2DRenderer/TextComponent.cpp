#include "pch.h"
#include "TextComponent.h"
#include "D2DRenderer.h"
#include "Helper.h"
#include "GameObject.h"

TextComponent::TextComponent(GameObject* pOwner, const std::string& Name)
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

void TextComponent::SerializeOut(nlohmann::ordered_json& object)
{
	RenderComponent::SerializeOut(object);
	object["m_String"] = D2DHelper::WStringToString(m_String);
	object["m_Color"] = { m_Color.r,m_Color.g,m_Color.b,m_Color.a };
	object["m_Rect"] = { m_Rect.left,m_Rect.top,m_Rect.right,m_Rect.bottom};
}

void TextComponent::SerializeIn(nlohmann::ordered_json& object)
{
	RenderComponent::SerializeIn(object);
	m_String = D2DHelper::StringToWString(object["m_String"]);
	m_Color = D2D1::ColorF(object["m_Color"][0], object["m_Color"][1], object["m_Color"][2], object["m_Color"][3]);
	m_Rect = D2D1::RectF(object["m_Rect"][0], object["m_Rect"][1], object["m_Rect"][2], object["m_Rect"][3]);
}
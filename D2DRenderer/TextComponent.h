#pragma once
#include "RenderComponent.h"
/*
	�ؽ�Ʈ�� �׸��� ������Ʈ
	
*/
class TextComponent :
    public RenderComponent
{
public:
	TextComponent(GameObject* pOwner, const std::wstring& Name);
	virtual ~TextComponent() override;

protected:
	std::wstring m_String;

	D2D1_RECT_F m_Rect;
	D2D1_COLOR_F m_Color;
public:
	virtual bool Initialize() override;

	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	const std::wstring& GetString() const { return m_String; }
	void SetString(const std::wstring& val) { m_String = val; }

};


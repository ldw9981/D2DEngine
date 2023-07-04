#pragma once
#include "RenderComponent.h"

/*
	Rect �ڽ��� �׸��� ������Ʈ
*/
class BoxComponent :
    public RenderComponent
{
public:
	BoxComponent(GameObject* pOwner, const std::wstring& Name);
	virtual ~BoxComponent();

	
	D2D1_RECT_F m_Rect;
	D2D1_COLOR_F m_Color;

	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
};


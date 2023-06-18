#pragma once
#include "RenderComponent.h"


class BoxComponent :
    public RenderComponent
{
public:
	BoxComponent();
	virtual ~BoxComponent();

	
	D2D1_RECT_F m_Rect;
	D2D1_COLOR_F m_Color;

	virtual void Update() override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
};


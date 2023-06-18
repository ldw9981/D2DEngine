#pragma once
#include "SceneComponent.h"

class RenderComponent: public SceneComponent
{
public:
	RenderComponent();
	virtual ~RenderComponent();
protected:
	int m_iZOrder;
	bool m_bVisible;
public:
	void SetZOrder(int zOrder) {  m_iZOrder = zOrder; }
	void SetVisible(bool visible) { m_bVisible = visible; }

	virtual void Update() override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
};


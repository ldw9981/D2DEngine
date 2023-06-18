#pragma once
#include "RenderComponent.h"
class SphereComponent :
    public RenderComponent
{
public:
    SphereComponent();
	~SphereComponent();
public:
	D2D1_COLOR_F m_Color;
	float m_Radius;

public:
	void SetRadius(float radius) { m_Radius = radius; }
	float GetRadius() { return m_Radius; }


	virtual void Update() override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

};


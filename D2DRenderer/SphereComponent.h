#pragma once
#include "RenderComponent.h"
/*
	Sphere를 그리는 컴포넌트

*/
class SphereComponent :
    public RenderComponent
{
public:
	SphereComponent(GameObject* pOwner,const std::wstring& Name);
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


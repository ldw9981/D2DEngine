#pragma once
#include "ColliderComponent.h"
/*
	Sphere를 그리는 컴포넌트

*/
class SphereComponent :
    public ColliderComponent
{
public:
	SphereComponent(GameObject* pOwner,const std::wstring& Name);
	~SphereComponent();
public:
	float m_Radius;

public:
	void SetRadius(float radius);
	float GetRadius() { return m_Radius; }

	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	virtual bool IsCollide(ColliderComponent* pOtherComponent) override;

};


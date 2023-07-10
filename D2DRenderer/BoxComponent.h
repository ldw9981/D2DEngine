#pragma once
#include "ColliderComponent.h"
#include "AABB.h"
/*
	Rect 박스를 그리는 컴포넌트
*/
class BoxComponent :
    public ColliderComponent
{
public:
	BoxComponent(GameObject* pOwner, const std::wstring& Name);
	virtual ~BoxComponent();

protected:
	D2D1_RECT_F m_Rect;
	AABB m_Collider;
public:
	void SetExtend(float x, float y);
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	virtual void Update() override;
	virtual bool IsCollide(ColliderComponent* pOtherComponent) override;

};


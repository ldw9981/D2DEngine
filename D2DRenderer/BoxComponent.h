#pragma once
#include "ColliderComponent.h"
#include "AABB.h"
/*
	Rect �ڽ��� �׸��� ������Ʈ
*/
class BoxComponent :
	public ColliderComponent
{
public:
	BoxComponent(GameObject* pOwner, const std::string& Name);
	virtual ~BoxComponent();

protected:
	D2D1_RECT_F m_Rect;
	AABB m_Collider;
public:
	const AABB& GetCollider() { return m_Collider;  }
	void SetExtend(float x, float y);
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	virtual void Update() override;
	virtual bool IsCollide(ColliderComponent* pOtherComponent) override;

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object) {};
};


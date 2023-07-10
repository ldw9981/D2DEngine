#pragma once
#include "RenderComponent.h"

class ColliderComponent;
class IColliderNotify
{
public:
	virtual void OnCollide(ColliderComponent* pOwnedComponent,ColliderComponent* pOtherComponent) = 0;
};

class ColliderComponent :
    public RenderComponent
{
public:
	ColliderComponent(GameObject* pOwner, const std::wstring& Name);
	virtual ~ColliderComponent();

protected:
	bool		m_NoCollision;
	D2D1_COLOR_F m_Color;
	std::list<IColliderNotify*> m_Observers;
public:
	bool GetNoCollision() const { return m_NoCollision; }
	void SetNoCollision(bool val) { m_NoCollision = val; }
	D2D1_COLOR_F GetColor() const { return m_Color; }
	void SetColor(D2D1_COLOR_F val) { m_Color = val; }

	// Sphere,Box, Capsule 에서 각자 구현해야한다.
	virtual bool IsCollide(ColliderComponent* pOtherComponent)=0;

};


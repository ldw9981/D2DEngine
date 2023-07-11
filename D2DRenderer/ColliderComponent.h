#pragma once
#include "RenderComponent.h"
#include <set>

enum class ColliderType
{
	None,
	Sphere,
	Box,
	Capsule,
};

enum class CollisionType
{
	NoCollision,
	Block,
	Overlap
};

class ColliderComponent;
class IColliderNotify
{
public:
	virtual void OnBlock(ColliderComponent* pOwnedComponent,ColliderComponent* pOtherComponent) = 0;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) = 0;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) = 0;
};

class ColliderComponent :
    public RenderComponent
{
public:
	ColliderComponent(GameObject* pOwner, const std::wstring& Name);
	virtual ~ColliderComponent();

protected:
	CollisionType m_CollisionType;
	ColliderType m_ColliderType;
	bool	m_IsCollide;
	bool	m_IsCollidePrev;
	bool	m_NoCollision;
	D2D1_COLOR_F m_Color;

	std::set<ColliderComponent*> m_CollideStateCurr;
	std::set<ColliderComponent*> m_CollideStatePrev;
public:

	CollisionType GetCollisionType() { return m_CollisionType; }
	void SetCollisionType(CollisionType Type) { m_CollisionType = Type; }
	
	D2D1_COLOR_F GetColor() const { return m_Color; }
	void SetColor(D2D1_COLOR_F val) { m_Color = val; }
	void SetIsCollide(bool IsCollide) { m_IsCollide = IsCollide; }
	bool GetIsCollide() { return m_IsCollide; }
	void ClearCollideStateCurr() { m_CollideStateCurr.clear(); }
	void ClearCollideStatePrev() { m_CollideStatePrev.clear(); }
	void BackupCollideState() {	m_CollideStatePrev = m_CollideStateCurr; }
	void InsertCollideState(ColliderComponent* pColliderComponent) { m_CollideStateCurr.insert(pColliderComponent); }

	bool IsEmptyCollideStateCurr() { return m_CollideStateCurr.empty(); }

	void ProcessOverlap();
	void ProcessBlock(ColliderComponent* pOtherComponent);
	ColliderType GetColliderType() { return m_ColliderType; }

	// Sphere,Box, Capsule 에서 각자 구현해야한다.
	virtual bool IsCollide(ColliderComponent* pOtherComponent)=0;
};


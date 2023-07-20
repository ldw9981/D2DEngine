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

/*
	�߻� Ŭ����
*/
class ColliderComponent :
    public RenderComponent
{
public:
	ColliderComponent(GameObject* pOwner, const std::string& Name);
	virtual ~ColliderComponent();

protected:
	CollisionType m_CollisionType;		// �ø��� Ÿ�� (���ø���,��, ������)
	ColliderType m_ColliderType;		// �ö��̴� Ÿ�� (��,�ڽ�,ĸ��)
	D2D1_COLOR_F m_Color;				// �׸���� ����

	std::set<ColliderComponent*> m_CollideStateCurr;    // ���� �浹 ����
	std::set<ColliderComponent*> m_CollideStatePrev;	// ���� �浹 ����
public:

	CollisionType GetCollisionType() { return m_CollisionType; }
	void SetCollisionType(CollisionType Type) { m_CollisionType = Type; }
	ColliderType GetColliderShape() { return m_ColliderType; }

	D2D1_COLOR_F GetColor() const { return m_Color; }
	void SetColor(D2D1_COLOR_F val) { m_Color = val; }
	void ClearAndBackupCollideState();
	
	bool IsEmptyCollideStateCurr() { return m_CollideStateCurr.empty(); }

	void InsertCollideState(ColliderComponent* pColliderComponent) { m_CollideStateCurr.insert(pColliderComponent); }
	void ProcessOverlap();
	void ProcessBlock(ColliderComponent* pOtherComponent);


	// Sphere,Box, Capsule ���� ���� �����ؾ��Ѵ�.
	virtual bool IsCollide(ColliderComponent* pOtherComponent)=0;

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);
};


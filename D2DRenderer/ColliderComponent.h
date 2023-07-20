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
	추상 클래스
*/
class ColliderComponent :
    public RenderComponent
{
public:
	ColliderComponent(GameObject* pOwner, const std::string& Name);
	virtual ~ColliderComponent();

protected:
	CollisionType m_CollisionType;		// 컬리전 타입 (노컬리전,블럭, 오버랩)
	ColliderType m_ColliderType;		// 컬라이더 타입 (구,박스,캡슐)
	D2D1_COLOR_F m_Color;				// 그리기용 색상

	std::set<ColliderComponent*> m_CollideStateCurr;    // 현재 충돌 상태
	std::set<ColliderComponent*> m_CollideStatePrev;	// 이전 충돌 상태
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


	// Sphere,Box, Capsule 에서 각자 구현해야한다.
	virtual bool IsCollide(ColliderComponent* pOtherComponent)=0;

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);
};


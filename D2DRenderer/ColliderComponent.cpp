#include "pch.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "GameApp.h"

ColliderComponent::ColliderComponent(GameObject* pOwner, const std::string& Name)
	: RenderComponent(pOwner,Name),m_Color(D2D1::ColorF(D2D1::ColorF::White))
{
	m_ColliderType = ColliderType::None;
	m_CollisionType = CollisionType::Overlap;
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::ClearAndBackupCollideState()
{
	m_CollideStatePrev = m_CollideStateCurr;
	m_CollideStateCurr.clear();
}

void ColliderComponent::ProcessOverlap()
{
	// 현재는 충돌 이지만 이전 상태에 업으면 Begin
	for (auto& pColliderComponent : m_CollideStateCurr)
	{
		if (m_CollideStatePrev.find(pColliderComponent) == m_CollideStatePrev.end())
		{	//게임 오브젝트에 알린다.
			GetOwner()->OnBeginOverlap(this,pColliderComponent);	
		}
	}
	// 이전에는 충돌 상태지만 현재 없으면 End
	for (auto& pColliderComponent : m_CollideStatePrev)
	{
		if (m_CollideStateCurr.find(pColliderComponent) == m_CollideStateCurr.end())
		{	//게임 오브젝트에 알린다.
			GetOwner()->OnEndOverlap(this, pColliderComponent);
		}
	}
}

void ColliderComponent::ProcessBlock(ColliderComponent* pOtherComponent)
{
	GetOwner()->OnBlock(this, pOtherComponent);
}

void ColliderComponent::SerializeOut(nlohmann::ordered_json& object)
{
	RenderComponent::SerializeOut(object);
	object["m_Color"] = { m_Color.r , m_Color.g , m_Color.b, m_Color.a };
	object["m_ColliderType"] = m_ColliderType;
	object["m_CollisionType"] = m_CollisionType; 
}

void ColliderComponent::SerializeIn(nlohmann::ordered_json& object)
{
	RenderComponent::SerializeIn(object);
	m_Color.r = object["m_Color"][0];
	m_Color.g = object["m_Color"][1];
	m_Color.b = object["m_Color"][2];
	m_Color.a = object["m_Color"][3];
	m_ColliderType = object["m_ColliderType"];
	m_CollisionType = object["m_CollisionType"];
}


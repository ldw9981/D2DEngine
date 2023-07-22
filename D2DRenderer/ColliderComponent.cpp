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
	// ����� �浹 ������ ���� ���¿� ������ Begin
	for (auto& pColliderComponent : m_CollideStateCurr)
	{
		if (m_CollideStatePrev.find(pColliderComponent) == m_CollideStatePrev.end())
		{	//���� ������Ʈ�� �˸���.
			GetOwner()->OnBeginOverlap(this,pColliderComponent);	
		}
	}
	// �������� �浹 �������� ���� ������ End
	for (auto& pColliderComponent : m_CollideStatePrev)
	{
		if (m_CollideStateCurr.find(pColliderComponent) == m_CollideStateCurr.end())
		{	//���� ������Ʈ�� �˸���.
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
	__super::SerializeOut(object);
}

void ColliderComponent::SerializeIn(nlohmann::ordered_json& object)
{
	__super::SerializeIn(object);


	if (object.find("m_Color") != object.end())
	{
		m_Color.r = object["m_Color"][0];
		m_Color.g = object["m_Color"][1];
		m_Color.b = object["m_Color"][2];
		m_Color.a = object["m_Color"][3];
	}

	if (object.find("m_ColliderType") != object.end())
	{
		m_ColliderType = object["m_ColliderType"];
	}

	if (object.find("m_CollisionType") != object.end())
	{
		m_CollisionType = object["m_CollisionType"];
	}
}


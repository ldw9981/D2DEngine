#include "pch.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "GameApp.h"

ColliderComponent::ColliderComponent(GameObject* pOwner, const std::wstring& Name)
	: RenderComponent(pOwner,Name),m_Color(D2D1::ColorF(D2D1::ColorF::White))
{
	m_NoCollision = false;
	m_ColliderType = ColliderType::None;
	m_CollisionType = CollisionType::Overlap;
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::ProcessOverlap()
{
	// ����� �浹 ������ ���� ���¿� ������ Begin
	for (auto& pColliderComponent : m_CollideStateCurr)
	{
		if (m_CollideStatePrev.find(pColliderComponent) == m_CollideStatePrev.end())
		{
			GetOwner()->OnBeginOverlap(this,pColliderComponent);	
		}
	}

	// �������� �浹 �������� ���� ������ End
	for (auto& pColliderComponent : m_CollideStatePrev)
	{
		if (m_CollideStateCurr.find(pColliderComponent) == m_CollideStateCurr.end())
		{
			GetOwner()->OnEndOverlap(this, pColliderComponent);
		}
	}
}

void ColliderComponent::ProcessBlock(ColliderComponent* pOtherComponent)
{
	GetOwner()->OnBlock(this, pOtherComponent);
}


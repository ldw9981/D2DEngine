#include "pch.h"
#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(GameObject* pOwner, const std::wstring& Name)
	: RenderComponent(pOwner,Name),m_Color(D2D1::ColorF(D2D1::ColorF::White))
{
	m_NoCollision = false;
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::CheckBeginEnd()
{
	// 현재는 충돌 이지만 이전 상태에 업으면 Begin


	// 이전에는 충돌 상태지만 현재 없으면 End
}


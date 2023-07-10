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

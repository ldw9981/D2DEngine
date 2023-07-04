#include "pch.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent(GameObject* pOwner, const std::wstring& Name)
	:SceneComponent(pOwner, Name),m_bVisible(true),m_iZOrder(0)
{
	
}


RenderComponent::~RenderComponent()
{
}



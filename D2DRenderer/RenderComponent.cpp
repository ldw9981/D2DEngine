#include "pch.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent(GameObject* pOwner, const std::string& Name)
	:SceneComponent(pOwner, Name),m_bVisible(true),m_iZOrder(0)
{
	// Screen 변환에서 왼쪽,하단이 0,0에서 위로 출력하므로 상하 반대로 출력한다.
	// 그러므로 최초 반대 방향으로 뒤집기 위한 행렬 Scale.y = -1.0f 을 적용한다.
	m_RenderTransform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f, D2D1::Point2F(0, 0));
}


RenderComponent::~RenderComponent()
{
}



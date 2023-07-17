#include "pch.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent(GameObject* pOwner, const std::string& Name)
	:SceneComponent(pOwner, Name),m_bVisible(true),m_iZOrder(0)
{
	// Screen ��ȯ���� ����,�ϴ��� 0,0���� ���� ����ϹǷ� ���� �ݴ�� ����Ѵ�.
	// �׷��Ƿ� ���� �ݴ� �������� ������ ���� ��� Scale.y = -1.0f �� �����Ѵ�.
	m_RenderTransform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f, D2D1::Point2F(0, 0));
}


RenderComponent::~RenderComponent()
{
}



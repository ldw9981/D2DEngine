#include "pch.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent(GameObject* pOwner, const std::string& Name)
	:SceneComponent(pOwner, Name),m_Visible(true),m_ZOrder(0)
{
	// Screen ��ȯ���� ����,�ϴ��� 0,0���� ���� ����ϹǷ� ���� �ݴ�� ����Ѵ�.
	// �׷��Ƿ� ���� �ݴ� �������� ������ ���� ��� Scale.y = -1.0f �� �����Ѵ�.
	m_RenderTransform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f, D2D1::Point2F(0, 0));
}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::SerializeOut(nlohmann::ordered_json& object)
{
	__super::SerializeOut(object);
}

void RenderComponent::SerializeIn(nlohmann::ordered_json& object)
{
	__super::SerializeIn(object);

	if (object.find("m_ZOrder") != object.end())
	{
		m_ZOrder = object["m_ZOrder"];
	}

	if (object.find("m_Visible") != object.end())
	{
		m_Visible = object["m_Visible"];
	}

}


#pragma once

#include "SceneComponent.h"

/*
	ī�޶�� ���ӿ� ���� ī�޶��� ��ġ ������Ʈ����� �ٸ��� �����Ƿ� 
	��� ��Ȱ���Ҽ� �ֵ��� ������Ʈ�� �������.
*/
class CameraComponent : public SceneComponent
{
public:
	CameraComponent(GameObject* pOwner, const std::string& Name);
	virtual ~CameraComponent();

public:
	int		m_CameraID;
	void SetCameraID(int id) { m_CameraID = id;  }
	int	GetCameraID() { return m_CameraID;  }
	virtual void Update(float DeltaTime) override;
	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);
};


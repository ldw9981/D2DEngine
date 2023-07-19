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
	virtual void Update() override;
	virtual void SerializeOut(nlohmann::ordered_json& object);;
	virtual void SerializeIn(nlohmann::ordered_json& object);;
};


#pragma once

#include "SceneComponent.h"

/*
	ī�޶�� ���ӿ� ���� ī�޶��� ��ġ ������Ʈ����� �ٸ��� �����Ƿ� 
	��� ��Ȱ���Ҽ� �ֵ��� ������Ʈ�� �������.
*/
class CameraComponent : public SceneComponent
{
public:
	CameraComponent(GameObject* pOwner, const std::wstring& Name);
	virtual ~CameraComponent();

public:
	virtual void Update() override;
};


#pragma once

#include "SceneComponent.h"

/*
	ī�޶�� ���ӿ� ���� ī�޶��� ��ġ ������Ʈ����� �ٸ��� �����Ƿ� 
	��� ��Ȱ���Ҽ� �ֵ��� ������Ʈ�� �������.
*/
class CameraComponent : public SceneComponent
{
public:
	CameraComponent();
	virtual ~CameraComponent();

public:
	virtual void Update() override;
};


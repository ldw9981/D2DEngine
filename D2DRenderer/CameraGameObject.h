#pragma once
#include "GameObject.h"

/*
	�׽�Ʈ�� �⺻ ī�޶� ������Ʈ
	���ο� ī�޶� ������Ʈ�� �����Ѵ�.
*/
class CameraComponent;
class CameraGameObject : public GameObject
{
public:
	CameraGameObject();
	virtual ~CameraGameObject();

	CameraComponent* m_pCameraComponent;
public :

	CameraComponent* GetCameraComponent() { return m_pCameraComponent; }
};

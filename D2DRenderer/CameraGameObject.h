#pragma once
#include "GameObject.h"

/*
	테스트용 기본 카메라 오브젝트
	내부에 카메라 컴포넌트를 생성한다.
*/
class CameraComponent;
class CameraGameObject : public GameObject
{
public:
	CameraGameObject();
	virtual ~CameraGameObject();

	CameraComponent* m_pCameraComponent;
public :
	virtual bool Initialize() override;

	CameraComponent* GetCameraComponent() { return m_pCameraComponent; }
};


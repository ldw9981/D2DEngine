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

	CameraComponent* GetCameraComponent() { return m_pCameraComponent; }
	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pAnimationComponent, const std::wstring& AnimationName) override;
};


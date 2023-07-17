#pragma once
#include "GameObject.h"

/*
	�׽�Ʈ�� �⺻ ī�޶� ������Ʈ
	���ο� ī�޶� ������Ʈ�� �����Ѵ�.
*/
class CameraComponent;
class Camera : public GameObject
{
public:
	Camera();
	virtual ~Camera();

	CameraComponent* m_pCameraComponent;
public :

	CameraComponent* GetCameraComponent() { return m_pCameraComponent; }
	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pAnimationComponent, const std::wstring& AnimationName) override;
};

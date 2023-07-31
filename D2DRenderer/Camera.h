#pragma once
#include "GameObject.h"
#include "InputComponent.h"

/*
	테스트용 기본 카메라 오브젝트
	내부에 카메라 컴포넌트를 생성한다.
*/
class MovementComponent;
class CameraComponent;
class InputComponent;
class Camera : public GameObject, public IInputNotify 
{
public:
	Camera();
	virtual ~Camera();

	CameraComponent* m_pCameraComponent;
	MovementComponent* m_pMovementComponent;
	InputComponent* m_pInputComponent;

	D2D_VECTOR_2F m_KeyDirection;

public:
	int  GetCameraID();
	void SetCameraID(int id);
	CameraComponent* GetCameraComponent() { return m_pCameraComponent; }
	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pAnimationComponent, const std::string& AnimationName) override;

	virtual void OnKeyDown(SHORT Key) override;
	virtual void OnKeyUp(SHORT Key) override;
	virtual void OnKeyPressed(SHORT Key) override;
	virtual void Update(float DeltaTime) override;
};


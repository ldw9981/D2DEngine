#include "pch.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "World.h"

Camera::Camera()
{
	m_pCameraComponent = CreateComponent<CameraComponent>("CameraComponent");
	SetRootComponent(m_pCameraComponent);
	// ����Ϸ��� ���ӿ��� ���� ȣ���ؾ� �Ѵ�
	//GetOwnerWorld()->SetCamera(m_pCameraComponent);
	m_IsCullObject = false;
}

Camera::~Camera()
{
}

void Camera::OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void Camera::OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void Camera::OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void Camera::OnAnimationEnd(AnimationComponent* pAnimationComponent, const std::string& AnimationName)
{

}


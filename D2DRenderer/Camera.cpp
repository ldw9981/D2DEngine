#include "pch.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "World.h"

Camera::Camera(World* pOwnerWorld)
	:GameObject(pOwnerWorld)
{
	m_pCameraComponent = CreateComponent<CameraComponent>("CameraComponent");
	SetRootComponent(m_pCameraComponent);

	m_IsCullObject = false;

	// CameraID를 등록한다.
	GetOwnerWorld()->AddCamera(m_pCameraComponent);
}

Camera::~Camera()
{
	// CameraID를 삭제한다.
	GetOwnerWorld()->DelCamera(m_pCameraComponent);
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


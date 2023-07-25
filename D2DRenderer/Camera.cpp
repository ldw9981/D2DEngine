#include "pch.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "World.h"
#include "Factory.h"

REGISTER_GAMEOBJECT(Camera)

Camera::Camera()
{
	m_pCameraComponent = CreateComponent<CameraComponent>("CameraComponent");
	SetRootComponent(m_pCameraComponent);
	m_IsCullObject = false;
}

Camera::~Camera()
{
	m_pOwnerWorld->DelCamera(m_pCameraComponent);
}

void Camera::SetCameraID(int id)
{
	m_pCameraComponent->SetCameraID(id);
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

void Camera::SerializeIn(nlohmann::ordered_json& object)
{
	GameObject::SerializeIn(object);

	m_pOwnerWorld->AddCamera(m_pCameraComponent);
}


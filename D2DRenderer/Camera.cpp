#include "pch.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "MovementComponent.h"
#include "InputComponent.h"
#include "World.h"
#include "Factory.h"

REGISTER_GAMEOBJECT(Camera)

Camera::Camera()
{
	m_pInputComponent = CreateComponent<InputComponent>("InputComponent");
	m_pInputComponent->SetInputListener(this);
	m_pInputComponent->RegisterKey('W');
	m_pInputComponent->RegisterKey('S');
	m_pInputComponent->RegisterKey('A');
	m_pInputComponent->RegisterKey('D');
	m_pInputComponent->SetEnabled(true);

	m_pMovementComponent = CreateComponent<MovementComponent>("MovementComponent");
	m_pMovementComponent->SetSpeed(100);

	m_pCameraComponent = CreateComponent<CameraComponent>("CameraComponent");
	SetRootComponent(m_pCameraComponent);
		
	m_pMovementComponent->SetRootSceneComponent(m_pCameraComponent);
	m_IsCullObject = false;
}

Camera::~Camera()
{

}

int Camera::GetCameraID()
{
	return m_pCameraComponent->GetCameraID();
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

void Camera::OnKeyDown(SHORT Key)
{

}

void Camera::OnKeyUp(SHORT Key)
{

}

void Camera::OnKeyPressed(SHORT Key)
{
	if (Key == 'A')
		m_KeyDirection.x = -1.0f;
	else if (Key == 'D')
		m_KeyDirection.x = 1.0f;

	if (Key == 'W')
		m_KeyDirection.y = 1.0f;
	else if (Key == 'S')
		m_KeyDirection.y = -1.0f;

	if (Key == 'A' || Key == 'D' || Key == 'W' || Key == 'S')
		m_pMovementComponent->SetDirection(m_KeyDirection);
}

void Camera::Update(float DeltaTime)
{
	// 방향은 매프레임 초기화 하고 키 입력이 있는 상태에서만 방향을 설정한다.
	m_KeyDirection = { 0,0 };
	m_pMovementComponent->SetDirection(m_KeyDirection);

	__super::Update(DeltaTime);
}
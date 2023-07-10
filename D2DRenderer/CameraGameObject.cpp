#include "pch.h"
#include "CameraGameObject.h"
#include "CameraComponent.h"
#include "World.h"

CameraGameObject::CameraGameObject()
{
	m_pCameraComponent = CreateComponent<CameraComponent>(L"CameraComponent");
	SetRootComponent(m_pCameraComponent);
	// ����Ϸ��� ���ӿ��� ���� ȣ���ؾ� �Ѵ�
	//GetOwnerWorld()->SetCamera(m_pCameraComponent);
	m_bIsCullObject = false;
}

CameraGameObject::~CameraGameObject()
{
}

void CameraGameObject::OnCollide(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void CameraGameObject::OnAnimationEnd(AnimationComponent* pAnimationComponent, const std::wstring& AnimationName)
{

}


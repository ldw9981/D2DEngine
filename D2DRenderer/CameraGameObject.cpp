#include "pch.h"
#include "CameraGameObject.h"
#include "CameraComponent.h"
#include "World.h"

CameraGameObject::CameraGameObject()
{

}

CameraGameObject::~CameraGameObject()
{
}

bool CameraGameObject::Initialize()
{ 
    m_pCameraComponent = CreateComponent<CameraComponent>();
    SetRootComponent(m_pCameraComponent);
    // ����Ϸ��� ���ӿ��� ���� ȣ���ؾ� �Ѵ�
    //GetOwnerWorld()->SetCamera(m_pCameraComponent);
    m_pCameraComponent->Initialize();
    return true;
}

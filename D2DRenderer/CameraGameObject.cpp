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
    // 사용하려는 게임에서 직접 호출해야 한다
    //GetOwnerWorld()->SetCamera(m_pCameraComponent);
    m_bIsCullObject = false;
    m_pCameraComponent->Initialize();
    return true;
}

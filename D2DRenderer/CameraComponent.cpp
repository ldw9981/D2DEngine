#include "pch.h"
#include "CameraComponent.h"
#include "Helper.h"
#include "GameApp.h"


CameraComponent::CameraComponent(GameObject* pOwner, const std::wstring& Name)
	: SceneComponent(pOwner, Name)
{
	m_BoundingBox.m_Extend.x = GameApp::m_pInstance->GetClientSize().width / 2.f;
	m_BoundingBox.m_Extend.y = GameApp::m_pInstance->GetClientSize().height / 2.f;
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::Update()
{
	__super::Update();	
	// 카메라의 위치가 0,0 이면 바운딩 박스의 센터위치는 화면 크기의 절반씩 더한 위치이다
	m_BoundingBox.m_Center.x = GetWorldLocation().x + m_BoundingBox.m_Extend.x;
	m_BoundingBox.m_Center.y = GetWorldLocation().y + m_BoundingBox.m_Extend.y;
}


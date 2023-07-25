#include "pch.h"
#include "CameraComponent.h"
#include "Helper.h"
#include "GameApp.h"
#include "World.h"


CameraComponent::CameraComponent(GameObject* pOwner, const std::string& Name)
	: SceneComponent(pOwner, Name)
{
	m_BoundingBox.m_Extend.x = GameApp::m_pInstance->GetClientSize().width / 2.f;
	m_BoundingBox.m_Extend.y = GameApp::m_pInstance->GetClientSize().height / 2.f;
	m_CameraID = -1;

	// CameraID를 등록한다.
	//GetOwnerWorld()->AddCamera(m_pCameraComponent);
}

CameraComponent::~CameraComponent()
{
	// CameraID를 삭제한다.
	//GetOwnerWorld()->DelCamera(m_pCameraComponent);
}

void CameraComponent::Update()
{
	__super::Update();	
	// 카메라의 위치가 0,0 이면 바운딩 박스의 센터위치는 화면 크기의 절반씩 더한 위치이다
	m_BoundingBox.m_Center.x = GetWorldLocation().x + m_BoundingBox.m_Extend.x;
	m_BoundingBox.m_Center.y = GetWorldLocation().y + m_BoundingBox.m_Extend.y;
}

void CameraComponent::SerializeOut(nlohmann::ordered_json& object)
{
	__super::SerializeOut(object);
	object["m_CameraID"] = m_CameraID;
}

void CameraComponent::SerializeIn(nlohmann::ordered_json& object)
{
	__super::SerializeIn(object);
	m_CameraID = object["m_CameraID"].get<int>();
}


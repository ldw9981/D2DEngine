#include "pch.h"
#include "CameraComponent.h"
#include "Helper.h"
#include "GameApp.h"
#include "World.h"
#include "../D2DRenderer/D2DRenderer.h"

CameraComponent::CameraComponent(GameObject* pOwner, const std::string& Name)
	: SceneComponent(pOwner, Name)
{
	
	m_BoundingBox.m_Extend.x = D2DRenderer::m_Instance->GetClientSize().width / 2.f;
	m_BoundingBox.m_Extend.y = D2DRenderer::m_Instance->GetClientSize().height / 2.f;
	m_CameraID = -1;

	// CameraID�� ����Ѵ�.
	//GetOwnerWorld()->AddCamera(m_pCameraComponent);
}

CameraComponent::~CameraComponent()
{
	// CameraID�� �����Ѵ�.
	//GetOwnerWorld()->DelCamera(m_pCameraComponent);
}

void CameraComponent::Update(float DeltaTime)
{
	__super::Update(DeltaTime);	
	// ī�޶��� ��ġ�� 0,0 �̸� �ٿ�� �ڽ��� ������ġ�� ȭ�� ũ���� ���ݾ� ���� ��ġ�̴�
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


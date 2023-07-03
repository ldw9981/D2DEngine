#include "pch.h"
#include "CameraComponent.h"
#include "Helper.h"
#include "GameApp.h"


CameraComponent::CameraComponent()
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
	// ī�޶��� ��ġ�� 0,0 �̸� �ٿ�� �ڽ��� ������ġ�� ȭ�� ũ���� ���ݾ� ���� ��ġ�̴�
	m_BoundingBox.m_Center.x = GetWorldLocation().x + m_BoundingBox.m_Extend.x;
	m_BoundingBox.m_Center.y = GetWorldLocation().y + m_BoundingBox.m_Extend.y;
}


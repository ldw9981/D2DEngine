#include "pch.h"
#include "MovementComponent.h"
#include "SceneComponent.h"
#include "GameApp.h"
#include "Helper.h"



void MovementComponent::Update()
{
	assert(m_pUpdateTarget != nullptr);
	mathHelper::Vector2F Location = m_pUpdateTarget->GetRelativeLocation();
	// m_Speed�� 1�ʿ� �̵��� �Ÿ��̹Ƿ� �ð���ȭ��(��)�� ���ϸ�  �ð���ȭ��ŭ �󸶳� �̵��ؾ����� ����Ѵ�.
	float Distance = m_Speed * GameApp::m_deltaTime;

	m_Velocity = mathHelper::Vector2F(m_Direction) * Distance;
	Location += m_Velocity;
	
	//���� ���� ��ġ�� �����Ѵ�.
	m_pUpdateTarget->SetRelativeLocation(Location.x, Location.y);	
}

void MovementComponent::SetDirection(const mathHelper::Vector2F& Direction)
{
	m_Direction = D2DHelper::NormalizeVector(Direction);	

}


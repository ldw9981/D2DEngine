#include "pch.h"
#include "MovementComponent.h"
#include "SceneComponent.h"
#include "GameApp.h"
#include "Helper.h"

void MovementComponent::Update()
{
	assert(m_pUpdateTarget != nullptr);
	D2D1_VECTOR_2F Location = m_pUpdateTarget->GetRelativeLocation();	
	// m_Speed�� 1�ʿ� �̵��� �Ÿ��̹Ƿ� �ð���ȭ��(��)�� ���ϸ�  �ð���ȭ��ŭ �󸶳� �̵��ؾ����� ����Ѵ�.
	float Distance = m_Speed * GameApp::m_deltaTime;

	// ���⿡ ���� �Ÿ��� ���Ͽ� �̵��Ѵ�.
	Location.x = Location.x + m_Direction.x * Distance;
	Location.y = Location.y + m_Direction.y * Distance;	
	
	//���� ���� ��ġ�� �����Ѵ�.
	m_pUpdateTarget->SetRelativeLocation(Location.x, Location.y);	
}

void MovementComponent::SetDirection(const D2D_VECTOR_2F& Direction)
{
	m_Direction = D2DHelper::NormalizeVector(Direction);	

}


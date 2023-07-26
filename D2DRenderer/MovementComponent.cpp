#include "pch.h"
#include "MovementComponent.h"
#include "SceneComponent.h"
#include "GameApp.h"
#include "Helper.h"


// ���ӵ� ������� ������ �ӵ��� �̵��Ѵ�.
void MovementComponent::Update(float DeltaTime)
{
	assert(m_pRootSceneComponent != nullptr);
	// ���� ��ġ�� �����´�.
	mathHelper::Vector2F Location = m_pRootSceneComponent->GetRelativeLocation();
	m_Velocity = m_Direction * m_Speed;		

	// ���ο� ��ġ�� ����Ѵ�.
	Location += m_Velocity * DeltaTime;	

	//���� ���� ��ġ�� �����Ѵ�.
	m_pRootSceneComponent->SetRelativeLocation(Location);	
	m_pRootSceneComponent->SetVelocity(m_Velocity);
}

void MovementComponent::SetDirection(const mathHelper::Vector2F& Direction)
{
	m_Direction = Direction;
	m_Direction.Normalize();
}

void MovementComponent::SerializeOut(nlohmann::ordered_json& object)
{
	Component::SerializeOut(object);
	object["m_Direction"] = { m_Direction.x , m_Direction.y };
	object["m_Speed"] = m_Speed;
}

void MovementComponent::SerializeIn(nlohmann::ordered_json& object)
{
	Component::SerializeIn(object);
	m_Direction.x = object["m_Direction"][0];
	m_Direction.y = object["m_Direction"][1];
	m_Speed = object["m_Speed"];
}


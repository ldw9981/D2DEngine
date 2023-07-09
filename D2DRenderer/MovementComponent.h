#pragma once
#include "Component.h"
#include "SimpleMathHelper.h"

class SceneComponent;
class GameObject;
class MovementComponent :
    public Component
{
public:
	MovementComponent(GameObject* pOwner, std::wstring Name)
		:Component(pOwner, Name)
	{
		m_Speed=0.0f; 
		m_Direction.x = 0; m_Direction.y = 0.0f;
	};
	~MovementComponent() 
	{  
	}
protected:
	float			m_Speed;		// 1�ʴ� �̵��� �ӷ�
	mathHelper::Vector2F	m_Direction;	// ���� ���ֺ���
	mathHelper::Vector2F	m_Velocity;		// �ӵ� ����
	SceneComponent* m_pUpdateTarget; // ��ġ�� ������ ������Ʈ
public:
	virtual void Update() override;	

	void SetUpdateTarget(SceneComponent* val) { m_pUpdateTarget = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	float GetSpeed() { return m_Speed; };
	void SetDirection(const mathHelper::Vector2F& Direction );
	const mathHelper::Vector2F& GetDirection() { return m_Direction; };
};


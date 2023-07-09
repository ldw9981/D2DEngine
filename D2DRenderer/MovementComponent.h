#pragma once
#include "Component.h"

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
	D2D_VECTOR_2F	m_Direction;	// ���� ���ֺ���
	D2D_VECTOR_2F	m_Velocity;		// �ӵ� ����
	SceneComponent* m_pUpdateTarget; // ��ġ�� ������ ������Ʈ
public:
	virtual void Update() override;	

	void SetUpdateTarget(SceneComponent* val) { m_pUpdateTarget = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	float GetSpeed() { return m_Speed; };
	void SetDirection(const D2D_VECTOR_2F& Direction );
	const D2D_VECTOR_2F& GetDirection() { return m_Direction; };
};


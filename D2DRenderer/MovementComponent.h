#pragma once
#include "Component.h"

class SceneComponent;
class MovementComponent :
    public Component
{
public:
	MovementComponent() { m_Speed=0.0f; };
	~MovementComponent() { m_Direction.x = 0; m_Direction.y=0.0f; }
protected:
	float			m_Speed;		// 1�ʴ� �̵��� �ӷ�
	D2D_VECTOR_2F	m_Direction;	// ���� ���ֺ���
	SceneComponent* m_pUpdateTarget; // ��ġ�� ������ ������Ʈ
public:
	virtual void Update() override;

	void SetUpdateTarget(SceneComponent* val) { m_pUpdateTarget = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	void SetDirection(float x, float y);
	const D2D_VECTOR_2F& GetDirection() { return m_Direction; };
};


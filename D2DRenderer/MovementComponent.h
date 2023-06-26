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
	float			m_Speed;		// 속력
	D2D_VECTOR_2F	m_Direction;	// 방향
	SceneComponent* m_pRootComponent; //

	virtual void Update() override;

	void SetSpeed(float speed) { m_Speed =speed; };
	void SetDirection(float x, float y) { m_Direction.x = x; m_Direction.y = y; }
};


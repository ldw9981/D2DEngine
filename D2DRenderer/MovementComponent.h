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
	float			m_Speed;		// 1초당 이동할 속력
	D2D_VECTOR_2F	m_Direction;	// 방향 유닛벡터
	SceneComponent* m_pRootComponent; // 위치를 변경할 컴포넌트
public:
	virtual void Update() override;

	void SetRootComponent(SceneComponent* val) { m_pRootComponent = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	void SetDirection(float x, float y);
	const D2D_VECTOR_2F& GetDirection() { return m_Direction; };
};


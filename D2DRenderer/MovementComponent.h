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
	float			m_Speed;		// ¼Ó·Â
	D2D_VECTOR_2F	m_Direction;	// ¹æÇâ À¯´Öº¤ÅÍ
	SceneComponent* m_pRootComponent; //
public:
	virtual bool Initialize() override;
	virtual void Update() override;

	void SetRootComponent(SceneComponent* val) { m_pRootComponent = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	void SetDirection(float x, float y);
};


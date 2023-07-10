#pragma once
#include "MovementComponent.h"

class GameObject;
class SideMovementComponent :
    public MovementComponent
{
public:
	SideMovementComponent(GameObject* pOwner,std::wstring Name);
	~SideMovementComponent();

	static float m_Gravity;		// 중력 가속도
protected:
	//mathHelper::Vector2F m_VelocityY;

	float m_VelocityY;
	float m_AccelerationY;			// 가속도
	float m_SpeedY;
	bool  m_IsJumping;				// 점프중인지
	float m_GravityAcceleration;	// 중력 가속도	
	float m_JumpAcceleration;		//점프 가속도

	float m_GravityGameScale;
public:
	virtual void Update() override;
	virtual void SetDirection(const mathHelper::Vector2F& Direction);

	void Jump();
};


#pragma once
#include "MovementComponent.h"

class GameObject;
class SideMovementComponent :
    public MovementComponent
{
public:
	SideMovementComponent(GameObject* pOwner,std::wstring Name);
	~SideMovementComponent();

	static float m_Gravity;		// �߷� ���ӵ�
protected:
	//mathHelper::Vector2F m_VelocityY;

	float m_VelocityY;
	float m_AccelerationY;			// ���ӵ�
	float m_SpeedY;
	bool  m_IsJumping;				// ����������
	float m_GravityAcceleration;	// �߷� ���ӵ�	
	float m_JumpAcceleration;		//���� ���ӵ�

	float m_GravityGameScale;
public:
	virtual void Update() override;
	virtual void SetDirection(const mathHelper::Vector2F& Direction);

	void Jump();
};


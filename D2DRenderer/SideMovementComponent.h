#pragma once
#include "MovementComponent.h"

class GameObject;
/*
	�̵������� X�����θ� �̵��Ѵ�.
	Y���� �߷°� �����θ� �̵��Ѵ�.
*/
class SideMovementComponent :
    public MovementComponent
{
public:
	SideMovementComponent(GameObject* pOwner,std::wstring Name);
	~SideMovementComponent();
	static float m_Gravity;		// �߷� ���ӵ�
protected:
	bool  m_IsJumping;				// ����������
	float m_GravityAcceleration;	// �߷� ���ӵ�	
	float m_JumpSpeed;				// ������ �ӷ�
	float m_GravityScale;			// �߷� ���ӵ� ������  ������Ʈ�� ���� �߷��� �ٸ��� ������ �� �ִ�.
	float m_SpeedY;		            // Y�� �ӷ� 
	float m_MinSpeedY;				// �߷��� ���� �ӵ�
public:
	virtual void Update() override;
	virtual void SetDirection(const mathHelper::Vector2F& Direction);
	void SetGravityScale(float val) { m_GravityScale = val; }
	void StartJump();
	void EndJump();
};


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
	float m_JumpAcceleration;		//���� ���ӵ�
	float m_GravityScale;			// �߷� ���ӵ� ������  ������Ʈ�� ���� �߷��� �ٸ��� ������ �� �ִ�.
public:
	virtual void Update() override;
	virtual void SetDirection(const mathHelper::Vector2F& Direction);
	void SetGravityScale(float val) { m_GravityScale = val; }
	void Jump();
};


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
	SideMovementComponent(GameObject* pOwner,std::string Name);
	~SideMovementComponent();
	static float m_Gravity;		// �߷� ���ӵ�
protected:
	bool  m_IsJumping;				// ����������
	float m_GravityScaled;			// �����ϵ� �߷�
	float m_JumpSpeed;				// ������ �ӷ�
	float m_GravityScale;			// �߷� ���ӵ� ������  ������Ʈ�� ���� �߷��� �ٸ��� ������ �� �ִ�.
	float m_SpeedY;		            // Y�� �ӷ� 
	float m_MaxSpeedY;				// �߷��� ���� �ӵ�
public:
	virtual void Update() override;
	virtual void SetDirection(const mathHelper::Vector2F& Direction);
	void SetGravityScale(float val) { m_GravityScale = val; }
	void ResetGravity() { m_GravityScaled = m_Gravity * m_GravityScale; }
	void Jump();
	void EndJump();

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);
};


#pragma once
#include "MovementComponent.h"

class GameObject;
/*
	이동방향은 X축으로만 이동한다.
	Y축은 중력과 점프로만 이동한다.
*/
class SideMovementComponent :
    public MovementComponent
{
public:
	SideMovementComponent(GameObject* pOwner,std::string Name);
	~SideMovementComponent();
	static float m_Gravity;		// 중력 가속도
protected:
	bool  m_IsJumping;				// 점프중인지
	float m_GravityScaled;			// 스케일된 중력
	float m_JumpSpeed;				// 점프의 속력
	float m_GravityScale;			// 중력 가속도 스케일  오브젝트에 따라서 중력을 다르게 적용할 수 있다.
	float m_SpeedY;		            // Y축 속력 
	float m_MaxSpeedY;				// 중력의 종단 속도
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


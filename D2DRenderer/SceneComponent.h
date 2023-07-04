#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include "AABB.h"

/*
	회전, 위치, 크기를 가지는 컴포넌트
	WorldTransform 을 계산하는것이 최종 목적이다. 
	참조하는 부모 컴포넌트가 있으면 부모 컴포넌트의 WorldTransform을 참조하여 계산한다.
*/
class GameObject;
class SceneComponent : public Component
{
public:
	SceneComponent(GameObject* pOwner, std::wstring Name);
	virtual ~SceneComponent() {};


protected:
	SceneComponent*		m_pParentScene;		// 부모 Scene 컴포넌트
	std::vector<SceneComponent*> m_Children; // 단지 참조만 한다. update,render호출안함

	D2D1_VECTOR_2F		m_RelativeScale;	// 상대 크기
	float				m_RelativeRotation; // 상대 회전
	D2D1_VECTOR_2F		m_RelativeLocation; // 상대 위치
	D2D1_MATRIX_3X2_F	m_RelativeTransform; // 상대 복합 변환

	D2D1_MATRIX_3X2_F	m_WorldTransform;    // 부모까지 반영된 최종 변환

	AABB				m_BoundingBox;		// AABB  
public:
	virtual bool Initialize();
	
	virtual void Update() override;
	// RelativeTransform과 	m_WorldTransform을 계산한다.
	void UpdateTrasnform();
	void SetRelativeScale(float x, float y);
	void AddRelativeScale(float x, float y);
	const D2D1_VECTOR_2F& GetRelativeScale() { return m_RelativeScale; }

	void SetRelativeRotation(float Rotation);
	void AddRelativeRotation(float Rotation);
	float GetRelativeRotation() { return m_RelativeRotation; }

	void SetRelativeLocation(float x, float y);
	void AddRelativeLocation(float x, float y);
	const D2D1_VECTOR_2F& GetRelativeLocation() { return m_RelativeLocation; }

	void SetParentScene(SceneComponent* pParent) { m_pParentScene = pParent; }

	const D2D1_MATRIX_3X2_F& GetWorldTransform() { return m_WorldTransform; }
	const AABB& GetBoundingBox() { return m_BoundingBox; }
	void SetBoundingBoxExtend(float x, float y) { m_BoundingBox.m_Extend = { x,y }; }
	void AttachToComponent(SceneComponent* pParent);


	// 월드 위치를 WorldTransform에서 가져온다.
	D2D1_VECTOR_2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = m_WorldTransform._31;
		out.y = m_WorldTransform._32;
		return out;
	}
	// SetWorldLocation은 
	// 부모가 있을경우 부모 기준으로 RelativeLocation을 변경하고 WorldTransform을 설정해야한다.
	// 부모가 없을경우 RelativeLocation을 설정하고 WorldTransform을 설정한다.
};


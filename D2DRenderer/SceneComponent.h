#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"

/*
	회전, 위치, 크기를 가지는 컴포넌트
	WorldTransform 을 계산하는것이 최종 목적이다. 
	참조하는 부모 컴포넌트가 있으면 부모 컴포넌트의 WorldTransform을 참조하여 계산한다.
*/
class SceneComponent : public Component
{
public:
	SceneComponent();
	virtual ~SceneComponent() {};


protected:
	SceneComponent*		m_pParentScene;		// 부모 Scene 컴포넌트
	std::vector<SceneComponent*> m_Children; // 단지 참조만 한다. update,render호출안함

	D2D1_VECTOR_2F		m_RelativeScale;	// 상대 크기
	float				m_RelativeRotation; // 상대 회전
	D2D1_VECTOR_2F		m_RelativeLocation; // 상대 위치
	D2D1_MATRIX_3X2_F	m_RelativeTransform; // 상대 복합 변환

	D2D1_MATRIX_3X2_F	m_WorldTransform;    // 부모까지 반영된 최종 변환

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

	const D2D_MATRIX_3X2_F& GetWorldTransform() { return m_WorldTransform; }


	void AttachToComponent(SceneComponent* pParent);

	void GetWorldLocation(D2D1_VECTOR_2F* out)
	{
		out->x = m_WorldTransform._31;
		out->y = m_WorldTransform._32;
	}
};


#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"

/*
	ȸ��, ��ġ, ũ�⸦ ������ ������Ʈ
	WorldTransform �� ����ϴ°��� ���� �����̴�. 
	�����ϴ� �θ� ������Ʈ�� ������ �θ� ������Ʈ�� WorldTransform�� �����Ͽ� ����Ѵ�.
*/
class SceneComponent : public Component
{
public:
	SceneComponent();
	virtual ~SceneComponent() {};

protected:
	SceneComponent*		m_pParentScene;
	std::vector<SceneComponent*> m_Children;

	D2D1_VECTOR_2F		m_RelativeScale;
	float				m_RelativeRotation;
	D2D1_VECTOR_2F		m_RelativeLocation;
	D2D1_MATRIX_3X2_F	m_RelativeTransform;

	D2D1_MATRIX_3X2_F	m_WorldTransform;
public:
	virtual bool Initialize();
	virtual void Update() override;
	

		
	void UpdateTrasnform();
	void SetRelativeScale(float x, float y);
	void AddRelativeScale(float x, float y);
	D2D1_VECTOR_2F GetRelativeScale() { return m_RelativeScale; }

	void SetRelativeRotation(float Rotation);
	void AddRelativeRotation(float Rotation);
	float GetRelativeRotation() { return m_RelativeRotation; }

	void SetRelativeLocation(float x, float y);
	void AddRelativeLocation(float x, float y);
	D2D1_VECTOR_2F GetRelativeLocation() { return m_RelativeLocation; }

	void SetParentScene(SceneComponent* pParent) { m_pParentScene = pParent; }

	const D2D_MATRIX_3X2_F& GetWorldTransform() { return m_WorldTransform; }


	void AttachToComponent(SceneComponent* pParent);
};


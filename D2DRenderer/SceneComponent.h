#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include "AABB.h"

/*
	ȸ��, ��ġ, ũ�⸦ ������ ������Ʈ
	WorldTransform �� ����ϴ°��� ���� �����̴�. 
	�����ϴ� �θ� ������Ʈ�� ������ �θ� ������Ʈ�� WorldTransform�� �����Ͽ� ����Ѵ�.
*/
class GameObject;
class SceneComponent : public Component
{
public:
	SceneComponent(GameObject* pOwner, std::wstring Name);
	virtual ~SceneComponent() {};


protected:
	SceneComponent*		m_pParentScene;		// �θ� Scene ������Ʈ
	std::vector<SceneComponent*> m_Children; // ���� ������ �Ѵ�. update,renderȣ�����

	D2D1_VECTOR_2F		m_RelativeScale;	// ��� ũ��
	float				m_RelativeRotation; // ��� ȸ��
	D2D1_VECTOR_2F		m_RelativeLocation; // ��� ��ġ
	D2D1_MATRIX_3X2_F	m_RelativeTransform; // ��� ���� ��ȯ

	D2D1_MATRIX_3X2_F	m_WorldTransform;    // �θ���� �ݿ��� ���� ��ȯ

	AABB				m_BoundingBox;		// AABB  
public:
	virtual bool Initialize();
	
	virtual void Update() override;
	// RelativeTransform�� 	m_WorldTransform�� ����Ѵ�.
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


	// ���� ��ġ�� WorldTransform���� �����´�.
	D2D1_VECTOR_2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = m_WorldTransform._31;
		out.y = m_WorldTransform._32;
		return out;
	}
	// SetWorldLocation�� 
	// �θ� ������� �θ� �������� RelativeLocation�� �����ϰ� WorldTransform�� �����ؾ��Ѵ�.
	// �θ� ������� RelativeLocation�� �����ϰ� WorldTransform�� �����Ѵ�.
};


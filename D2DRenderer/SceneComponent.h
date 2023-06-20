#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"

class SceneComponent : public Component
{
public:
	SceneComponent();
	virtual ~SceneComponent();

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
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

	template<typename T>
	T* CreateChild()
	{
		bool bIsBase = std::is_base_of<SceneComponent, T>::value;		
		T* pChild = new T();		
		pChild->SetParentScene(this);
		m_Children.push_back(pChild);
		return pChild;
	}
		
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
};


#pragma once
#include <vector>
#include "Object.h"

class SceneComponent : public Object
{
public:
	SceneComponent();
	virtual ~SceneComponent();

protected:
	SceneComponent*		m_pParent;

	std::vector<SceneComponent*> m_Children;
	D2D1_VECTOR_2F		m_RelativeScale;
	float				m_RelativeRotation;
	D2D1_VECTOR_2F		m_RelativeLocation;
	D2D1_MATRIX_3X2_F	m_RelativeTransform;
	D2D1_MATRIX_3X2_F	m_WorldTransform;
public:
	virtual bool Init();
	virtual void Update();
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

	template<typename T>
	T* CreateChild()
	{
		T* pChild = new T();		
		pChild->SetParent(this);
		m_Children.push_back(pChild);
		return pChild;
	}
		
	void SetScale(float x, float y) { m_RelativeScale = { x,y }; }
	void SetRotation(float Rotation) { m_RelativeRotation = Rotation; }
	void SetPosition(float x, float y) { m_RelativeLocation = { x,y }; }
	void SetParent(SceneComponent* pParent) { m_pParent = pParent; }

	const D2D1_MATRIX_3X2_F& GetWorldTransform() { return m_WorldTransform; }

	D2D1_VECTOR_2F ExtractScaleFromTransform(const D2D1_MATRIX_3X2_F& Transform);
};


#pragma once

#include "Component.h"

class Transform : public Component
{
public:
	Transform()
	:m_RelativePositionX(0)
	{
	}
	virtual ~Transform() {}

protected:
	Transform* m_pParent;
	int m_RelativePositionX;
	int m_RelativeTransform;
	int m_WorldTransform;
public:
	Transform* GetParent() const { return m_pParent; }
	void SetParent(Transform* val) { m_pParent = val; }
	const int& GetWorldTransform()
	{
		return m_WorldTransform;
	}
	virtual void Update(float DeltaTime);

};

/*
class BitmapComponent : public Transform
	'
{'

wstring m_FilePath;
ID2D_Bitmap* m_pBitmap;

Render(IRenderTarget* pRendertaret)
{
	SetTransform
		pRendertaret->DrawBitmap()
}
}
*/
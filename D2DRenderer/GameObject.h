#pragma once
#include "SceneComponent.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

protected:
	SceneComponent* m_pRootComponent;
		
public:
	void SetRootComponent(SceneComponent* pRootComponent);
	SceneComponent* GetRootComponent() const;

	virtual void Update();
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
};


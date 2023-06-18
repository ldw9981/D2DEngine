#pragma once

#include "../D2DRenderer/GameObject.h"

/*
	DemoObject Hierachy
		- BoxComponent
			- SphereComponent
				- AnimationComponent
				
 */
class BoxComponent;
class AnimationComponent;
class SphereComponent;
class DemoObject :
    public GameObject
{
public:
	DemoObject();
	virtual ~DemoObject();
	BoxComponent* m_pBoxComponent;

	SphereComponent* m_pSphereComponent;
	AnimationComponent* m_pAnimationComponent;
public:
	virtual bool Init() override;
	virtual void Update() override;
};


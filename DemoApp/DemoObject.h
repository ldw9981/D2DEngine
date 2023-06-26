#pragma once

#include "../D2DRenderer/GameObject.h"

/*
	DemoObject Hierachy

	- [Root] SphereComponent
		- BoxComponent
			- AnimationComponent
				
 */
class BoxComponent;
class AnimationComponent;
class SphereComponent;
class TextComponent;
class SceneComponent;
class DemoObject :
    public GameObject
{
public:
	DemoObject();
	virtual ~DemoObject();
	BoxComponent* m_pBoxComponent;

	SphereComponent* m_pSphereComponent;
	AnimationComponent* m_pAnimationComponent;
	TextComponent* m_pTextComponent;
	SceneComponent* m_pSceneComponent;
public:
	virtual bool Initialize() override;
	virtual void Update() override;
};


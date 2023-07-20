#pragma once

#include "../D2DRenderer/GameObject.h"


class BoxComponent;
class AnimationComponent;
class SphereComponent;
class TextComponent;
class SceneComponent;
class MovementComponent;
class World;
class DemoObject :
    public GameObject
{
public:
	DemoObject(World* pOwner);
	virtual ~DemoObject();
	BoxComponent* m_pBoxComponent;

	SphereComponent* m_pSphereComponent;
	AnimationComponent* m_pAnimationComponent;
	TextComponent* m_pTextComponent;
	SceneComponent* m_pSceneComponent;
	MovementComponent* m_pMovementComponent;
public:

	virtual void Update() override;
};


#pragma once

#include "../D2DRenderer/GameObject.h"


class BoxComponent;
class AnimationComponent;
class SphereComponent;
class TextComponent;
class SceneComponent;
class MovementComponent;
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
	MovementComponent* m_pMovementComponent;
public:
	virtual bool Initialize() override;	// 컴포넌트를 생성하고 부모자식 연결한다.
	virtual void Update() override;
};


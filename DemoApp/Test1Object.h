#pragma once
#include "../D2DRenderer/GameObject.h"


class BoxComponent;
class AnimationComponent;
class SphereComponent;
class TextComponent;
class SceneComponent;
class MovementComponent;

/*

	Hierarchy 테스트용 오브젝트
*/
class Test1Object :
	public GameObject
{
public:
	Test1Object();
	virtual ~Test1Object();
	BoxComponent* m_pBoxComponent;

	SphereComponent* m_pSphereComponent;
	TextComponent* m_pTextComponent;
	SceneComponent* m_pSceneComponent;
	MovementComponent* m_pMovementComponent;
public:

	virtual void Update() override;

	virtual void OnCollide(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pOwnedComponent, const std::wstring& AnimationName) override;
};


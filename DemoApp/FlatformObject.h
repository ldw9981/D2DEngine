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
class FlatformObject :
	public GameObject
{
public:
	FlatformObject();
	virtual ~FlatformObject();
	BoxComponent* m_pBoxComponent;
	BoxComponent* m_pLeftBlock;
	BoxComponent* m_pRightBlock;

	SphereComponent* m_pSphereComponent;
	TextComponent* m_pTextComponent;
	SceneComponent* m_pSceneComponent;
	MovementComponent* m_pMovementComponent;
public:

	virtual void Update() override;

	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pOwnedComponent, const std::wstring& AnimationName) override;
};


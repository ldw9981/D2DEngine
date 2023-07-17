#pragma once
#include "../D2DRenderer/GameObject.h"


class BoxComponent;
class AnimationComponent;
class SphereComponent;
class TextComponent;
class SceneComponent;
class MovementComponent;
class BitmapComponent;
/*

	Hierarchy 테스트용 오브젝트
*/
class PlatformObject :
	public GameObject
{
public:
	PlatformObject();
	virtual ~PlatformObject();
	BoxComponent* m_pBoxComponent;
	
	SceneComponent* m_pSceneComponent;
	MovementComponent* m_pMovementComponent;
	BitmapComponent* m_pBitmapComponent;
public:

	virtual void Update() override;

	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pOwnedComponent, const std::wstring& AnimationName) override;
};


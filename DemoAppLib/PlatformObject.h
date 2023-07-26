#pragma once
#include "../D2DRenderer/GameObject.h"


class BoxComponent;
class AnimationComponent;
class SphereComponent;
class TextComponent;
class SceneComponent;
class MovementComponent;
class BitmapComponent;
class World;
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
	BitmapComponent* m_pBitmapComponent;
public:

	virtual void Update(float DeltaTime) override;

	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pOwnedComponent, const std::string& AnimationName) override;
};


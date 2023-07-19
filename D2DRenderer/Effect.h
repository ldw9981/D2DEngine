#pragma once
#include "GameObject.h"
class Effect :
    public GameObject
{
public:

	Effect();
	virtual ~Effect();

	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pAnimationComponent, const std::string& AnimationName) override;

	static GameObject* Create()
	{
		return new Effect;
	}
};


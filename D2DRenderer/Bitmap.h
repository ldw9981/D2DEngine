#pragma once
#include "GameObject.h"
class Bitmap :
    public GameObject
{
public:
	Bitmap();
	~Bitmap();

	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pOwnedComponent, const std::string& AnimationName) override;

	
	static GameObject* Create()
	{
		return new Bitmap;
	}
};


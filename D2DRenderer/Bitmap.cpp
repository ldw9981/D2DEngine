#include "pch.h"
#include "Bitmap.h"

Bitmap::Bitmap(World* pOwnerWorld)
	:GameObject(pOwnerWorld)
{
}

Bitmap::~Bitmap()
{
}

void Bitmap::OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{
}

void Bitmap::OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{
}

void Bitmap::OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{
}

void Bitmap::OnAnimationEnd(AnimationComponent* pOwnedComponent, const std::string& AnimationName)
{
}

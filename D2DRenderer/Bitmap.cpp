#include "pch.h"
#include "Bitmap.h"
#include "Factory.h"


REGISTER_GAMEOBJECT(Bitmap)

Bitmap::Bitmap()
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

#include "pch.h"
#include "Bitmap.h"
#include "BitmapComponent.h"
#include "Factory.h"


REGISTER_GAMEOBJECT(Bitmap)

Bitmap::Bitmap()
{
	BitmapComponent* pBitmapComponent = CreateComponent<BitmapComponent>("BitmapComponent");
	SetRootComponent(pBitmapComponent);
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

void Bitmap::OnBeginPlay()
{

}

void Bitmap::OnEndPlay()
{

}

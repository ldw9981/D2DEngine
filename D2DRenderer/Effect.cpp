#include "pch.h"
#include "Effect.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{
}

void Effect::OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{
}

void Effect::OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{
}

void Effect::OnAnimationEnd(AnimationComponent* pAnimationComponent, const std::string& AnimationName)
{
}

#include "pch.h"
#include "Effect.h"
#include "Factory.h"
#include "World.h"

REGISTER_GAMEOBJECT(Effect)

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

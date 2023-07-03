#pragma once

#include "../D2DRenderer/GameObject.h"



class AnimationComponent;
class MovementComponent;
class FSMComponent;

class Test2Object :
	public GameObject
{
public:
	Test2Object();
	virtual ~Test2Object();

	FSMComponent* m_pFSMComponent;
	AnimationComponent* m_pAnimationComponent;
	MovementComponent* m_pMovementComponent;
public:

	virtual void Update() override;
};


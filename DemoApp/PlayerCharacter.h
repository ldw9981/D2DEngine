#pragma once

#include "../D2DRenderer/GameObject.h"



class AnimationComponent;
class MovementComponent;
class FSMComponent;
class FSMCharacter;
class TextComponent;
class PlayerCharacter :
	public GameObject
{
public:
	PlayerCharacter();
	virtual ~PlayerCharacter();

	FSMComponent* m_pFSMComponent;
	AnimationComponent* m_pAnimationComponent;
	MovementComponent* m_pMovementComponent;
	FSMCharacter* m_pFSMCharacter;
	TextComponent* m_pTextComponent;
public:

	virtual void Update() override;
};


#pragma once

#include "../D2DRenderer/GameObject.h"



class AnimationComponent;
class SideMovementComponent;
class FSMComponent;
class FSMCharacter;
class TextComponent;
class CameraComponent;
class PlayerCharacter :
	public GameObject
{
public:
	PlayerCharacter();
	virtual ~PlayerCharacter();

	FSMComponent* m_pFSMComponent;
	AnimationComponent* m_pAnimationComponent;
	SideMovementComponent* m_pSideMovementComponent;
	FSMCharacter* m_pFSMCharacter;
	TextComponent* m_pTextComponent;
	CameraComponent* m_pCameraComponent;
public:

	virtual void Update() override;
};


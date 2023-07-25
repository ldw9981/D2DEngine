#pragma once

#include "../D2DRenderer/GameObject.h"


extern int Test;

class AnimationComponent;
class SideMovementComponent;
class FSMComponent;
class FSMCharacter;
class TextComponent;
class CameraComponent;
class BoxComponent;
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
	BoxComponent* m_pFootBox;
	BoxComponent* m_pBodyBox;
public:

	virtual void Update() override;

	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pOwnedComponent, const std::string& AnimationName) override;


	virtual void SerializeIn(nlohmann::ordered_json& object);
};


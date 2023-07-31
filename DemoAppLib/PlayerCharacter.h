#pragma once

#include "../D2DRenderer/GameObject.h"
#include "../D2DRenderer/InputComponent.h"

class AnimationComponent;
class SideMovementComponent;
class FSMComponent;
class FSMCharacter;
class TextComponent;
class CameraComponent;
class BoxComponent;
class InputComponent;
class PlayerCharacter :
	public GameObject,public IInputNotify 
{
public:
	PlayerCharacter();
	virtual ~PlayerCharacter();

	InputComponent* m_pInputComponent;
	FSMComponent* m_pFSMComponent;
	AnimationComponent* m_pAnimationComponent;
	SideMovementComponent* m_pSideMovementComponent;
	FSMCharacter* m_pFSMCharacter;
	TextComponent* m_pTextComponent;
	CameraComponent* m_pCameraComponent;
	BoxComponent* m_pFootBox;
	BoxComponent* m_pBodyBox;
	D2D_VECTOR_2F m_KeyDirection;
public:

	virtual void Update(float DeltaTime) override;

	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) override;
	virtual void OnAnimationEnd(AnimationComponent* pOwnedComponent, const std::string& AnimationName) override;


	virtual void SerializeIn(nlohmann::ordered_json& object);

	virtual void OnKeyDown(SHORT Key) override;
	virtual void OnKeyUp(SHORT Key) override;
	virtual void OnKeyPressed(SHORT Key) override;
};


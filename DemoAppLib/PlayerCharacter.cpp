#include "pch.h"
#include "PlayerCharacter.h"
#include "../D2DRenderer/SceneComponent.h"
#include "../D2DRenderer/BoxComponent.h"
#include "../D2DRenderer/Component.h"
#include "../D2DRenderer/AnimationComponent.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/SphereComponent.h"
#include "../D2DRenderer/TextComponent.h"
#include "../D2DRenderer/SideMovementComponent.h"
#include "../D2DRenderer/TextComponent.h"
#include "../D2DRenderer/FSMComponent.h"
#include "../D2DRenderer/FSMTransition.h"
#include "../D2DRenderer/FiniteStateMachine.h"
#include "../D2DRenderer/CameraComponent.h"
#include "../D2DRenderer/BoxComponent.h"
#include "../D2DRenderer/Factory.h"
#include "../D2DRenderer/D2DRenderer.h"
#include "../D2DRenderer/TimeSystem.h"
#include "../D2DRenderer/InputComponent.h"
#include "StateIdle.h"
#include "FSMCharacter.h"


REGISTER_GAMEOBJECT(PlayerCharacter)

PlayerCharacter::PlayerCharacter()
{
	m_KeyDirection = {0,0};	

	// 그냥 Component 
	m_pInputComponent = CreateComponent<InputComponent>("InputComponent");
	m_pInputComponent->SetEnabled(true);
	m_pInputComponent->SetInputListener(this);
	m_pInputComponent->RegisterKey(VK_CONTROL);
	m_pInputComponent->RegisterKey(VK_SPACE);
	m_pInputComponent->RegisterKey(VK_LEFT);
	m_pInputComponent->RegisterKey(VK_RIGHT);

	m_pSideMovementComponent = CreateComponent<SideMovementComponent>("SideMovementComponent");
	m_pSideMovementComponent->SetSpeed(200);

	m_pFootBox = CreateComponent<BoxComponent>("FootBox");
	m_pFootBox->SetExtend(20.0f,4.0f);
	SetRootComponent(m_pFootBox);

	// 위치를 변경할 컴포넌트를 설정한다.
	m_pSideMovementComponent->SetRootSceneComponent(m_pFootBox);

	m_pBodyBox = CreateComponent<BoxComponent>("BodyBox");
	m_pBodyBox->SetRelativeLocation(mathHelper::Vector2F(0, 50));
	m_pBodyBox->SetExtend(25.0f, 50.0f);
	m_pBodyBox->AttachToComponent(m_pFootBox);

	// SceneComponent만 RootComponent로 설정 가능
	m_pAnimationComponent = CreateComponent<AnimationComponent>("AnimationComponent");
	m_pAnimationComponent->SetAnimationAsset(std::wstring(L"../Resource/Ken.AnimAsset"));	
	m_pAnimationComponent->SetRelativeLocation(mathHelper::Vector2F(0,-4));
	m_pAnimationComponent->AttachToComponent(m_pFootBox);	

	m_pFSMComponent = CreateComponent<FSMComponent>("FSMComponent");
	m_pFSMCharacter = m_pFSMComponent->CreateFiniteStateMachine<FSMCharacter>();

	m_pTextComponent = CreateComponent<TextComponent>("TextComponent");
	m_pTextComponent->SetRelativeLocation(mathHelper::Vector2F (-100,100));
	m_pTextComponent->SetString(L"이동:화살표 , 공격:컨트롤 , 점프: 스페이스");
	m_pTextComponent->AttachToComponent(m_pAnimationComponent);

	m_pCameraComponent = CreateComponent<CameraComponent>("CameraComponent");	
	m_pCameraComponent->AttachToComponent(m_pAnimationComponent);

	m_pCameraComponent->SetCameraID(1);
}

PlayerCharacter::~PlayerCharacter()
{
	GetOwnerWorld()->DelCamera(m_pCameraComponent);
}

void PlayerCharacter::Update(float DeltaTime)
{
	// 방향은 매프레임 초기화 하고 키 입력이 있는 상태에서만 방향을 설정한다.
	m_KeyDirection = { 0,0 };
	m_pSideMovementComponent->SetDirection(m_KeyDirection);

	// 카메라의 상대 위치는 한번만 설정해도 되지만 MFC에디터에서는 화면 크기가 바뀔수 있어 일단 매번 설정한다.
	// Todo: 이벤트 기반으로 바꾸자
	D2D_VECTOR_2F Location = m_pAnimationComponent->GetWorldLocation();
	// 상대위치가 0이면 왼쪽 하단 기준으로 나온다.
	// 플레이어 이므로 캐릭터가 가운데 나오게한다.
	D2D_SIZE_U size = D2DRenderer::m_Instance->GetClientSize();
	m_pCameraComponent->SetRelativeLocation(mathHelper::Vector2F((float)size.width /2 * -1.0f, -100.0f));	

	__super::Update(DeltaTime);
}

void PlayerCharacter::OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{
	if (pOwnedComponent == m_pFootBox)
	{
		mathHelper::Vector2F Location = m_pRootComponent->GetWorldLocation();
		Location = Location - m_pRootComponent->GetVelocity() * GameTimer::m_Instance->DeltaTime();
		Location.x = m_pRootComponent->GetRelativeLocation().x;
		m_pRootComponent->SetRelativeLocation(Location);

		m_pSideMovementComponent->EndJump();
		
	}
	else if (pOwnedComponent == m_pBodyBox)
	{
		mathHelper::Vector2F Location = m_pRootComponent->GetWorldLocation();
		Location = Location - m_pRootComponent->GetVelocity() * GameTimer::m_Instance->DeltaTime();
		Location.y = m_pRootComponent->GetRelativeLocation().y;
		m_pRootComponent->SetRelativeLocation(Location);
	}

}

void PlayerCharacter::OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{

}

void PlayerCharacter::OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{


}

void PlayerCharacter::OnAnimationEnd(AnimationComponent* pOwnedComponent, const std::string& AnimationName)
{
	m_pFSMCharacter->m_AnimationComplete = true;
}

void PlayerCharacter::SerializeIn(nlohmann::ordered_json& object)
{
	__super::SerializeIn(object);
	GetOwnerWorld()->AddCamera(m_pCameraComponent);
}

void PlayerCharacter::OnKeyDown(SHORT Key)
{
	if (Key == VK_CONTROL)
	{
		m_pFSMCharacter->m_Attack = true;
	}
	if (Key == VK_SPACE)
	{
		m_pSideMovementComponent->Jump();
	}
}

void PlayerCharacter::OnKeyUp(SHORT Key)
{

}

void PlayerCharacter::OnKeyPressed(SHORT Key)
{
	if (Key == VK_LEFT)
		m_KeyDirection.x = -1.0f;		
	else if ( Key == VK_RIGHT)
		m_KeyDirection.x = 1.0f;

	if (Key == VK_LEFT || Key == VK_RIGHT )
		m_pSideMovementComponent->SetDirection(m_KeyDirection);
}

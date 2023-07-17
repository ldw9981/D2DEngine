#include "framework.h"
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
#include "StateIdle.h"
#include "FSMCharacter.h"
/*
	DemoObject Hierachy
	- SideMovementComponent
	- [Root] AnimationComponent
	- FSMComponent
 */

PlayerCharacter::PlayerCharacter()
{
	// 그냥 Component 
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
	// 상대위치가 0이면 왼쪽 하단 기준으로 나온다.
	// 플레이어 이므로 캐릭터가 가운데 나오게한다.
	D2D_SIZE_U size = GameApp::m_pInstance->GetClientSize();
	size.height = size.height / 2;
	size.width = size.width / 2;
	m_pCameraComponent->SetRelativeLocation(mathHelper::Vector2F((float)size.width * -1.0f , -100.0f));

}

PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::Update()
{

	D2D_VECTOR_2F Location, Direction {0};
	Location = m_pAnimationComponent->GetWorldLocation();
	
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
	{
		m_pFSMCharacter->m_Attack = true;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) 	{ //왼쪽
		Direction.x = -1.0f;	
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽
		Direction.x = 1.0f;		
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { //위
		Direction.y = 1.0f;		
	} 
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래
		Direction.y = -1.0f;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_pSideMovementComponent->Jump();
	}

	m_pSideMovementComponent->SetDirection(Direction);
	
	
	

	__super::Update();
}

void PlayerCharacter::OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent)
{
	if (pOwnedComponent == m_pFootBox)
	{
		mathHelper::Vector2F Location = m_pRootComponent->GetWorldLocation();
		Location = Location - m_pRootComponent->GetVelocity() * GameApp::m_deltaTime;
		Location.x = m_pRootComponent->GetRelativeLocation().x;
		m_pRootComponent->SetRelativeLocation(Location);

		m_pSideMovementComponent->EndJump();
		
	}
	else if (pOwnedComponent == m_pBodyBox)
	{
		mathHelper::Vector2F Location = m_pRootComponent->GetWorldLocation();
		Location = Location - m_pRootComponent->GetVelocity() * GameApp::m_deltaTime;
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

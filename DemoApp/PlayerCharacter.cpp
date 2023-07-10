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
	m_pSideMovementComponent = CreateComponent<SideMovementComponent>(L"SideMovementComponent");

	// SceneComponent만 RootComponent로 설정 가능
	m_pAnimationComponent = CreateComponent<AnimationComponent>(L"AnimationComponent");
	m_pAnimationComponent->SetAnimationAsset(std::wstring(L"Ken"));	
	//m_pAnimationComponent->SetAnimation(L"Attack", false, true);
	SetRootComponent(m_pAnimationComponent);

	// 위치를 변경할 컴포넌트를 설정한다.
	m_pSideMovementComponent->SetUpdateTarget(m_pAnimationComponent);	
	m_pSideMovementComponent->SetSpeed(300);

	m_pFSMComponent = CreateComponent<FSMComponent>(L"FSMComponent");
	m_pFSMCharacter = m_pFSMComponent->CreateFiniteStateMachine<FSMCharacter>();
	// 애니메이션 이벤트를 처리할 인스턴스 등록
	m_pAnimationComponent->AddListener(m_pFSMCharacter);


	m_pTextComponent = CreateComponent<TextComponent>(L"TextComponent");
	m_pTextComponent->SetRelativeLocation(-100,0);
	m_pTextComponent->SetString(L"이동:화살표 , 공격:스페이스");
	m_pTextComponent->AttachToComponent(m_pAnimationComponent);

	m_pCameraComponent = CreateComponent<CameraComponent>(L"CameraComponent");
	m_pCameraComponent->AttachToComponent(m_pAnimationComponent);
	// 상대위치가 0이면 왼쪽 하단 기준으로 나온다.
	// 플레이어 이므로 캐릭터가 가운데 나오게한다.
	D2D_SIZE_U size = GameApp::m_pInstance->GetClientSize();
	size.height = size.height / 2;
	size.width = size.width / 2;
	m_pCameraComponent->SetRelativeLocation((float)size.width * -1.0f,(float)size.height *-1.0f);

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
		OutputDebugString(L"위");
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

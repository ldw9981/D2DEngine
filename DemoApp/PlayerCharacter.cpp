#include "framework.h"
#include "PlayerCharacter.h"
#include "../D2DRenderer/SceneComponent.h"
#include "../D2DRenderer/BoxComponent.h"
#include "../D2DRenderer/Component.h"
#include "../D2DRenderer/AnimationComponent.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/SphereComponent.h"
#include "../D2DRenderer/TextComponent.h"
#include "../D2DRenderer/MovementComponent.h"
#include "../D2DRenderer/FSMComponent.h"
#include "../D2DRenderer/FSMTransition.h"
#include "../D2DRenderer/FiniteStateMachine.h"
#include "StateIdle.h"
#include "FSMCharacter.h"
/*
	DemoObject Hierachy
	- MovementComponent
	- [Root] AnimationComponent
	- FSMComponent
 */

PlayerCharacter::PlayerCharacter()
{
	// �׳� Component 
	m_pMovementComponent = CreateComponent<MovementComponent>();

	// SceneComponent�� RootComponent�� ���� ����
	m_pAnimationComponent = CreateComponent<AnimationComponent>();
	m_pAnimationComponent->SetAnimationAsset(std::wstring(L"Test"));	
	m_pAnimationComponent->SetAnimation(L"Run", false, true);
	SetRootComponent(m_pAnimationComponent);

	// ��ġ�� ������ ������Ʈ�� �����Ѵ�.
	m_pMovementComponent->SetUpdateTarget(m_pAnimationComponent);
	m_pMovementComponent->SetSpeed(300.0f);
	m_pMovementComponent->SetDirection(0,0);

	m_pFSMComponent = CreateComponent<FSMComponent>();
	FiniteStateMachine* pFiniteStateMachine = m_pFSMComponent->CreateFiniteStateMachine<FSMCharacter>();
	// �ִϸ��̼� �̺�Ʈ�� ó���� �ν��Ͻ� ���
	m_pAnimationComponent->AddListener(pFiniteStateMachine);
}

PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::Update()
{

	D2D_VECTOR_2F Location, Direction {0};
	Location = m_pAnimationComponent->GetWorldLocation();
	
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) 	{ //����
		Direction.x = -1.0f;	
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //������
		Direction.x = 1.0f;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { //��
		Direction.y = 1.0f;
	} 
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //�Ʒ�
		Direction.y = -1.0f;
	}

	m_pMovementComponent->SetDirection(Direction.x, Direction.y);
	

	__super::Update();
}

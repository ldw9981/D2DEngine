#pragma once
#include "../D2DRenderer/FiniteStateMachine.h"
#include "../D2DRenderer/FSMState.h"
#include "../D2DRenderer/FSMTransition.h"
#include "StateIdle.h"
#include "StateAttack.h"
#include "StateMove.h"
#include "StateDeath.h"
#include "TransitionDeath.h"

#include "../D2DRenderer/FSMStateAlias.h"
#include "../D2DRenderer/FSMComponent.h"
#include "../D2DRenderer/MovementComponent.h"
#include "../D2DRenderer/GameObject.h"

class AnimationComponent;
class MovementComponent;
/*
	�� FSM�� PlayerCharacter�� �и��� ���� ������ �۵��ǹǷ�
	NPC���Ե� ����Ҽ��ִ�.
*/
class FSMCharacter :
    public FiniteStateMachine
{
public:
	FSMCharacter(FSMComponent* pOwner)
	: FiniteStateMachine(pOwner),
		m_StateIdle(this),
		m_StateMove(this),
		m_StateAttack(this),
		m_StateDeath(this),
		m_TransitionToDeath(this),
		m_StateAliasDeath(this)
	{
		AddState(&m_StateMove);
		AddState(&m_StateAttack);
		AddState(&m_StateIdle);
		AddState(&m_StateDeath);

		AddStateAlias(&m_StateAliasDeath);

		m_StateAliasDeath.BindState(&m_StateMove);
		m_StateAliasDeath.BindState(&m_StateAttack);
		m_StateAliasDeath.BindState(&m_StateIdle);

		SetInitialState(L"Idle");

		GameObject* pGameObject = pOwner->GetOwner();
		m_pAnimationComponent =  (AnimationComponent*)pGameObject->GetComponent(L"AnimationComponent");
		m_pMovementComponent = (MovementComponent*)pGameObject->GetComponent(L"MovementComponent");
		
		m_Attack=false;
		m_AnimationComplete=false;
	}
	virtual ~FSMCharacter()
	{
	
	}

	StateMove m_StateMove;
	StateAttack m_StateAttack;
	StateDeath m_StateDeath;
	StateIdle m_StateIdle;
	TransitionDeath m_TransitionToDeath;

	// Death���·� ���� ���� Transition�� ó���Ѵ�.
	FSMStateAlias m_StateAliasDeath;	


	AnimationComponent* m_pAnimationComponent;
	MovementComponent* m_pMovementComponent;

	D2D1_VECTOR_2F m_MoveDirection;
	D2D1_VECTOR_2F m_LastDirection;
	bool			m_Attack;
	bool			m_AnimationComplete;
	bool			m_Mirror;

	virtual void Update() override;
};


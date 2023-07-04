#pragma once

/*
	FSM에서 공유할 전이 조건을 다루는 클래스
	
*/
class FiniteStateMachine;
class GameObject;
class FSMTransition
{
public:
	FSMTransition(FiniteStateMachine* pOwner)
		:m_pOwner(pOwner)
	{

	}

	virtual ~FSMTransition()
	{

	}
	
public:	
	std::wstring m_NextState;
	virtual bool CheckCondition() = 0;
	FiniteStateMachine* m_pOwner;
public:
	void SetOwner(FiniteStateMachine* pOwner) { m_pOwner = pOwner; }
};


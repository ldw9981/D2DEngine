#pragma once

/*
	FSM에서 전이를 다루는 클래스
	이 클래스를 사용해도 되지만 State의 CheckTransition에 전이 내용을 직접 작성해도된다.
	공통으로 작성할 전이 내용이 많아 진다면 자식 Transition 클래스 작성을 고려해본다. 
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
	std::string m_NextState;			// 변화할 상태이름
	virtual bool CheckCondition() = 0;	// 조건 내용
	FiniteStateMachine* m_pOwner;
public:
	void SetOwner(FiniteStateMachine* pOwner) { m_pOwner = pOwner; }
};


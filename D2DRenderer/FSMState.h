#pragma once

/*
	State Class
	전이는 Transition Class를 사용해도되고
	CheckTransition 함수를 재정의(override) 해서 사용해도됨
*/
class FSMComponent;
class GameObject;
class FSMTransition;
class FiniteStateMachine;
class FSMState
{
public:
	FSMState(FiniteStateMachine* pOwner,std::wstring Name)
		:m_pOwner(pOwner)
		,m_Name(Name)
	{

	}
	virtual ~FSMState()
	{

	}
	std::wstring m_Name;
	FiniteStateMachine* m_pOwner;

	std::vector<FSMTransition*> m_Transitions;
public:	
	void SetOwner(FiniteStateMachine* pOwner) { m_pOwner = pOwner; }

	//체크할 Transition 인터스턴스를 등록한다.
	void AddTransition(FSMTransition* pTransition) { m_Transitions.push_back(pTransition); }

	virtual bool CheckTransition(std::wstring& OutNextState);
	const std::wstring& GetName() { return m_Name; }

	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

	virtual void EventAnimationEnd(const std::wstring& AnimationName) = 0;
	virtual void EventAnimationNotify(const std::wstring& NotifyName) = 0;
};


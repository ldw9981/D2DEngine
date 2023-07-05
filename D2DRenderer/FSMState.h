#pragma once

/*
	State Class
	���̴� Transition Class�� ����ص��ǰ�
	CheckTransition �Լ��� ������(override) �ؼ� ����ص���
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

	//üũ�� Transition ���ͽ��Ͻ��� ����Ѵ�.
	void AddTransition(FSMTransition* pTransition) { m_Transitions.push_back(pTransition); }

	virtual bool CheckTransition(std::wstring& OutNextState);
	const std::wstring& GetName() { return m_Name; }

	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

	virtual void EventAnimationEnd(const std::wstring& AnimationName) = 0;
	virtual void EventAnimationNotify(const std::wstring& NotifyName) = 0;
};


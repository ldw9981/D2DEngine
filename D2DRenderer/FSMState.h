#pragma once
class FSMComponent;
class GameObject;
class FSMTransition;
class FSMInstance;
class FSMState
{
public:
	FSMState(FSMInstance* pOwner,std::wstring Name)
		:m_pOwner(pOwner)
		,m_Name(Name)
	{

	}
	virtual ~FSMState()
	{

	}
	std::wstring m_Name;
	FSMInstance* m_pOwner;
	GameObject* m_pGameObject;

	std::vector<FSMTransition*> m_Transitions;
public:	
	void SetOwner(FSMInstance* pOwner) { m_pOwner = pOwner; }
	void SetGameObject(GameObject* pGameObject) { m_pGameObject = pGameObject; }
	void AddTransition(FSMTransition* pTransition) { m_Transitions.push_back(pTransition); }

	virtual bool CheckTransition(std::wstring& NextState);
	const std::wstring& GetName() { return m_Name; }

	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

	virtual void EventAnimationEnd(const std::wstring& AnimationName) = 0;
	virtual void EventAnimationNotify(const std::wstring& NotifyName) = 0;
};


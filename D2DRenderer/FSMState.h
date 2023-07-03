#pragma once
class FSMComponent;
class GameObject;
class FSMState
{
public:
	FSMState(wstring StateName)
	{
		m_StateName = StateName;
	}
	virtual ~FSMState()
	{

	}

	wstring m_StateName;
	FSMComponent* m_pOwner;
	GameObject* m_pGameObject;
public:	
	void SetOwner(FSMComponent* pOwner) { m_pOwner = pOwner; }
	void SetGameObject(GameObject* pGameObject) { m_pGameObject = pGameObject; }
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual bool CheckTransition(wstring& OutNewStateName) = 0;
	virtual void Exit() = 0;
};


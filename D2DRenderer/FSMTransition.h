#pragma once

/*
	FSM에서 공유할 전이 조건을 다루는 클래스
	
*/
class FSMInstance;
class GameObject;
class FSMTransition
{
public:
	FSMTransition(FSMInstance* pOwner)
		:m_pOwner(pOwner)
	{

	}

	virtual ~FSMTransition()
	{

	}
	
public:	
	std::wstring m_NextState;
	virtual bool CheckCondition() = 0;
	FSMInstance* m_pOwner;
public:
	void SetOwner(FSMInstance* pOwner) { m_pOwner = pOwner; }
};


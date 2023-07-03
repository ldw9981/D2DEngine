#pragma once

/*
	FSM���� ������ ���� ������ �ٷ�� Ŭ����
	
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


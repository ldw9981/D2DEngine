#pragma once

/*
	FSM���� ������ ���� ������ �ٷ�� Ŭ����
	
*/
class FSMSharedTransition
{
public:
	FSMSharedTransition();
	~FSMSharedTransition();
	
public:

	wstring m_NextState;

	bool CheckTransition(wstring& OutStateName);
};


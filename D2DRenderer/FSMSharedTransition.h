#pragma once

/*
	FSM에서 공유할 전이 조건을 다루는 클래스
	
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


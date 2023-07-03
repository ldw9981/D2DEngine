#include "pch.h"
#include "FSMComponent.h"
#include "FSMState.h"
#include "Helper.h"

FSMComponent::~FSMComponent()
{
	for (auto iter : m_pStates)
	{
		delete iter.second;
	}
	m_pStates.clear();
}

void FSMComponent::Update()
{
	if (m_pCurrentState)
	{
		// Update Action
		// 현재 실행중인 State의 Update를 실행시켜 매프레임 실행할 내용을 처리하게 한다.
		m_pCurrentState->Update();		


		// Transition Check수행하여 조건에 만족할경우 넘겨받은 nextState로 변경한다.
		wstring nextStateName;
		bool bTransite = m_pCurrentState->CheckTransition(nextStateName);
		if (bTransite)
		{
			ChangeState(nextStateName);
		}
	}
	else
	{
		// 초기 상태로 바꾼다.
		assert(m_pInitialState!=nullptr);
		ChangeState(m_pInitialState->m_StateName);
	}
}

void FSMComponent::ChangeState(wstring stateName)
{
	if (m_pCurrentState)
	{
		// Exit Action 
		// State가 변경될때 이전 State가 종료 처리할 내용을 실행한다.
		m_pCurrentState->Exit();	
	}

	auto it = m_pStates.find(stateName);
	if (it != m_pStates.end())
	{
		m_pCurrentState = it->second;

		// Enter Action
		// State가 변경될때 새로운 State가 시작 처리할 내용을 실행한다.
		m_pCurrentState->Enter();	
	}
	else
	{
		LOG_WARNING(L"No state with name: %s ",stateName.c_str());
	}
}

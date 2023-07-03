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
		// ���� �������� State�� Update�� ������� �������� ������ ������ ó���ϰ� �Ѵ�.
		m_pCurrentState->Update();		


		// Transition Check�����Ͽ� ���ǿ� �����Ұ�� �Ѱܹ��� nextState�� �����Ѵ�.
		wstring nextStateName;
		bool bTransite = m_pCurrentState->CheckTransition(nextStateName);
		if (bTransite)
		{
			ChangeState(nextStateName);
		}
	}
	else
	{
		// �ʱ� ���·� �ٲ۴�.
		assert(m_pInitialState!=nullptr);
		ChangeState(m_pInitialState->m_StateName);
	}
}

void FSMComponent::ChangeState(wstring stateName)
{
	if (m_pCurrentState)
	{
		// Exit Action 
		// State�� ����ɶ� ���� State�� ���� ó���� ������ �����Ѵ�.
		m_pCurrentState->Exit();	
	}

	auto it = m_pStates.find(stateName);
	if (it != m_pStates.end())
	{
		m_pCurrentState = it->second;

		// Enter Action
		// State�� ����ɶ� ���ο� State�� ���� ó���� ������ �����Ѵ�.
		m_pCurrentState->Enter();	
	}
	else
	{
		LOG_WARNING(L"No state with name: %s ",stateName.c_str());
	}
}

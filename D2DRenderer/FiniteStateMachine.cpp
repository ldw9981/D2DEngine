#include "pch.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMStateAlias.h"
#include "Helper.h"

FiniteStateMachine::~FiniteStateMachine()
{

}

void FiniteStateMachine::Update()
{
	if (m_pCurrentState == nullptr)
	{
		// �ʱ� ���·� �ٲ۴�.
		assert(m_pInitialState != nullptr);
		ChangeState(m_pInitialState->GetName());
		return;
	}

	// Update Action
	// ���� �������� State�� Update�� ������� �������� ������ ������ ó���ϰ� �Ѵ�.
	m_pCurrentState->Update();

	// Transition Check�����Ͽ� ���ǿ� �����Ұ�� �Ѱܹ��� nextState�� �����Ѵ�.
	wstring nextStateName;
	if (m_pCurrentState->CheckTransition(nextStateName))
	{
		ChangeState(nextStateName);
		return;
	}
	
	// ���� Transition Check
	for (auto pStateAlias : m_pStateAlias)
	{
		// ���� State�� Alias�� ���ԵǾ� �ִ��� Ȯ���Ѵ�.
		if(!pStateAlias->CheckAlias(m_pCurrentState))
			continue;

		// Alias�� ���ԵǾ� ���� ��� Transition�� Ȯ���Ѵ�.
		if (pStateAlias->CheckTransition(nextStateName))
		{
			ChangeState(nextStateName);
			break;
		}
	}
}

void FiniteStateMachine::ChangeState(wstring stateName)
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
		LOG_WARNING(L"No state with name: %s ", stateName.c_str());
	}
}

void FiniteStateMachine::SetInitialState(std::wstring stateName)
{
	auto it = m_pStates.find(stateName);
	if (it != m_pStates.end())
	{
		m_pInitialState = it->second;
	}
	else
	{
		LOG_WARNING(L"No state with name: %s ", stateName.c_str());
	}
}

void FiniteStateMachine::AddState(FSMState* pState)
{
	m_pStates.insert(make_pair(pState->GetName(), pState));
}


void FiniteStateMachine::AddStateAlias(FSMStateAlias* pStateAlias)
{
	m_pStateAlias.push_back(pStateAlias);
}

void FiniteStateMachine::OnAnimationEnd(const std::wstring& AnimationName)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->EventAnimationEnd(AnimationName);
	}
}

void FiniteStateMachine::OnAnimationNotify(const std::wstring& NotifyName)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->EventAnimationNotify(NotifyName);
	}
}

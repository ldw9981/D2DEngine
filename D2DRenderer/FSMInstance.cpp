#include "pch.h"
#include "FSMInstance.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMStateAlias.h"
#include "Helper.h"

FSMInstance::~FSMInstance()
{

}

void FSMInstance::Update()
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
	
	// StateAlias Check
	for (auto pStateAlias : m_pStateAlias)
	{
		if(!pStateAlias->CheckAlias(pStateAlias))
			continue;

		if (pStateAlias->CheckTransition(nextStateName))
		{
			ChangeState(nextStateName);
			break;
		}
	}
}

void FSMInstance::ChangeState(wstring stateName)
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

void FSMInstance::AddState(FSMState* pState)
{
	m_pStates.insert(make_pair(pState->GetName(), pState));
}


void FSMInstance::AddStateAlias(FSMStateAlias* pStateAlias)
{
	m_pStateAlias.push_back(pStateAlias);
}

void FSMInstance::OnAnimationEnd(const std::wstring& AnimationName)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->EventAnimationEnd(AnimationName);
	}
}

void FSMInstance::OnAnimationNotify(const std::wstring& NotifyName)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->EventAnimationNotify(NotifyName);
	}
}

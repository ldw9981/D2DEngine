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
		// 초기 상태로 바꾼다.
		assert(m_pInitialState != nullptr);
		ChangeState(m_pInitialState->GetName());
		return;
	}

	// Update Action
	// 현재 실행중인 State의 Update를 실행시켜 매프레임 실행할 내용을 처리하게 한다.
	m_pCurrentState->Update();

	// Transition Check수행하여 조건에 만족할경우 넘겨받은 nextState로 변경한다.
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

#include "pch.h"
#include "FSMState.h"
#include "FSMTransition.h"

bool FSMState::CheckTransition(std::wstring& NextState)
{
	for (auto pTransition : m_Transitions)
	{
		if (pTransition->CheckCondition() == true)
		{
			NextState = pTransition->m_NextState;
			return true;
		}
	}
	return false;
}

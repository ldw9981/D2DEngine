#include "pch.h"
#include "FSMState.h"
#include "FSMTransition.h"

bool FSMState::CheckTransition(std::string& OutNextState)
{
	for (auto pTransition : m_Transitions)
	{
		if (pTransition->CheckCondition() == true)
		{
			OutNextState = pTransition->m_NextState;
			return true;
		}
	}
	return false;
}

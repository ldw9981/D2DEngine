#include "pch.h"
#include "InputComponent.h"
#include "InputManager.h"

InputComponent::InputComponent(GameObject* pOwner, const std::string& Name)
:Component(pOwner,Name),m_pInputNotify(nullptr), m_bIsEnabled(false)
{
	
}

InputComponent::~InputComponent()
{
	
}

void InputComponent::RegisterKey(SHORT Key)
{
	m_Keys.push_back(Key);
	m_KeysPrev.push_back(0);
	m_KeysCurr.push_back(0);
}

void InputComponent::Update(float DeltaTime)
{
	if(!m_bIsEnabled || !m_pInputNotify)
		return;

	for (size_t i=0;i < m_Keys.size();i++)
	{		
		m_KeysCurr[i] = GetAsyncKeyState(m_Keys[i]);

		// detect key down and key up
		if (m_KeysCurr[i] != m_KeysPrev[i])
		{
			if (m_KeysPrev[i] == 0 && m_KeysCurr[i] != 0)
			{
				m_pInputNotify->OnKeyDown(m_Keys[i]);
			}
			else if (m_KeysPrev[i] != 0 && m_KeysCurr[i] == 0)
			{
				m_pInputNotify->OnKeyUp(m_Keys[i]);
			}			
		}

		// detect key pressed (key down and hold)
		if ( m_KeysCurr[i] & 0x8000)
		{
			m_pInputNotify->OnKeyPressed(m_Keys[i]);
		}
		m_KeysPrev[i] = m_KeysCurr[i];
	}	
}

void InputComponent::SerializeOut(nlohmann::ordered_json& object)
{
	__super::SerializeOut(object);

}

void InputComponent::SerializeIn(nlohmann::ordered_json& object)
{
	__super::SerializeIn(object);
}

void InputComponent::OnBeginPlay()
{
	InputManager::GetInstance()->RegisterInputComponent(this);
}

void InputComponent::OnEndPlay()
{
	InputManager::GetInstance()->UnregisterInputComponent(this);
}

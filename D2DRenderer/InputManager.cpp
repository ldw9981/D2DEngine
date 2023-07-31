#include "pch.h"
#include "InputManager.h"
#include "InputComponent.h"
#include "GameObject.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
}

void InputManager::RegisterInputComponent(InputComponent* pInputComponent)
{
	m_InputComponents.push_back(pInputComponent);
}

void InputManager::UnregisterInputComponent(InputComponent* pInputComponent)
{
	m_InputComponents.remove(pInputComponent);
}




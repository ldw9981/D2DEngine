#pragma once
#include "Singleton.h"

class InputComponent;
class InputManager :
	public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();

protected:
	std::list<InputComponent*> m_InputComponents;

public:
	void RegisterInputComponent(InputComponent* pInputComponent);
	void UnregisterInputComponent(InputComponent* pInputComponent);
};


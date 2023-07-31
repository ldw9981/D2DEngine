#pragma once
#include "Component.h"

class IInputNotify
{
public:
	virtual void OnKeyDown(SHORT Key) = 0;
	virtual void OnKeyUp(SHORT Key) = 0;
	virtual void OnKeyPressed(SHORT Key) = 0;
};
class GameObject;
class InputComponent :
    public Component
{
public:
	InputComponent(GameObject* pOwner, const std::string& Name);
	~InputComponent();

	void SetEnabled(bool val) { m_bIsEnabled = val; }
	void SetInputListener(IInputNotify* pNotify) { m_pInputNotify = pNotify; }
protected:
	bool m_bIsEnabled;
	std::vector<SHORT> m_Keys;
	std::vector<SHORT> m_KeysCurr;
	std::vector<SHORT> m_KeysPrev;

	IInputNotify* m_pInputNotify;
public:
	void RegisterKey(SHORT Key);
	void Update(float DeltaTime) override;

	virtual void SerializeOut(nlohmann::ordered_json& object);
	virtual void SerializeIn(nlohmann::ordered_json& object);
	virtual void OnBeginPlay();
	virtual void OnEndPlay();
};


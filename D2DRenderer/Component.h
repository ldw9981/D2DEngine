#pragma once
#include "Object.h"
/*
	���� ������Ʈ�� ����� ������Ʈ ������ �и��ϱ� ���� �߻� Ŭ����
	���ӿ�����Ʈ�� ������Ʈ�� �������� �̷������.
	������Ʈ�� ������ GameObject�� CreateComponent<T> �� ���� �̷������.

	���ݴ����� Object�� ������ �����Ƿ� Object�� ��ӹ��� �ʴ´�.
*/
class GameObject;
class Component //: public Object
{
public:
	Component(GameObject* pOwner,const std::wstring& Name) : m_pOwner(pOwner),m_Name(Name)
	{
	}
	virtual ~Component() {};

protected:
	GameObject* m_pOwner;
	std::wstring m_Name;
public:
	const std::wstring& GetName() const { return m_Name; }
	virtual void Update() = 0;
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
	GameObject* GetOwner() { return m_pOwner; }
};


#pragma once
#include "Object.h"
/*
	���� ������Ʈ�� ����� ������Ʈ ������ �и��ϱ� ���� �߻� Ŭ����
	���ӿ�����Ʈ�� ������Ʈ�� �������� �̷������.
	������Ʈ�� ������ GameObject�� CreateComponent<T> �� ���� �̷������.

	���ݴ����� Object�� ������ �����Ƿ� Object�� ��ӹ��� �ʴ´�.
*/
class GameObject;
class Component 
{
public:
	Component() : m_pOwner(nullptr)
	{
	}
	virtual ~Component() {};

protected:
	GameObject* m_pOwner;
public:
	virtual void Update() = 0;
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
};


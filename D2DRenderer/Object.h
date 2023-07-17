#pragma once
/*
	������Ʈ�� ��� ���� ����� �����ϴ� �߻� Ŭ����
	���� Save/Load�� �ϴ� Serialize�� ������ ����
	�ڽ� Ŭ������ Serialize�� �����ؾ� �Ѵ�.
*/
#include <nlohmann/json.hpp>

class Object
{
public:
	Object()
	{

	};
	virtual ~Object()
	{

	};

	virtual void SerializeOut(nlohmann::ordered_json& object) {} ;
	virtual void SerializeIn(nlohmann::ordered_json& object) {};
};


#pragma once
/*
	������Ʈ�� ��� ���� ����� �����ϴ� �߻� Ŭ����
	���� Save/Load�� �ϴ� Serialize�� ������ ����
	�ڽ� Ŭ������ Serialize�� �����ؾ� �Ѵ�.
*/
class Object
{
public:
	Object()
	{

	};
	virtual ~Object()
	{

	};

	virtual void Serialize(std::ofstream& ofstream)=0;	
	virtual void Serialize(std::ifstream& ofstream)=0;
};


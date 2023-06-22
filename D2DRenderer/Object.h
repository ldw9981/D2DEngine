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

	virtual bool Initialize()=0; //�ʱ�ȭ�� ������Ʈ�� ��밡������Ȯ���Ѵ�.
	virtual void Update()=0;	//������Ʈ�� ���¸� ������Ʈ�Ѵ�.
};


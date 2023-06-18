#pragma once
class Object
{
public:
	Object()
	{

	};
	virtual ~Object()
	{

	};

	virtual bool Init()=0;
	virtual void Update()=0;
};


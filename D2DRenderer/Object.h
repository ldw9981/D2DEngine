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

	virtual bool Initialize()=0;
	virtual void Update()=0;
};


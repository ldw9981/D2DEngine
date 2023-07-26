#pragma once

class GameObject 
{
public:
	GameObject() {};
	~GameObject() {};



	virtual void Render()=0;
	virtual void Update(float DeltaTime)=0;
};


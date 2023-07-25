#pragma once
#include "GameObject.h"
#include "AnimationRender.h"
#include "Movement.h"
#include "BoxRender.h"
#include "Component.h"


class PlayerCharacter :
    public GameObject,public AnimationRender,public Movement
{
public:
	PlayerCharacter()
	{
		SetOwner(this);
		m_BoxRenderer.SetOwner(this);
		m_BoxRenderer.SetParent(this);
	}
	~PlayerCharacter()
	{

	}

	BoxRender m_BoxRenderer;

	virtual void Render() override;
	virtual void Update() override;
};



/*

class Galaxy :
	public GameObject, public Bitmapcomponent , 
{
	Galaxy()
	{
		SetOwner(this);
		m_Earth.SetParent(this);
		m_Moon.SetParent(&m_Earth);
	}
	Bitmapcomponent m_Earth;
	Bitmapcomponent m_Moon;

	virtual void Render() override;
	virtual void Update() override;
};

*/
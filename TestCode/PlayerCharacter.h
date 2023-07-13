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


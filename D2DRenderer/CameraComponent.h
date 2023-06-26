#pragma once

#include "SceneComponent.h"



class CameraComponent : public SceneComponent
{
public:
	CameraComponent() {}
	virtual ~CameraComponent() {}

	D2D1_RECT_F m_ViewPort;
public:
	virtual void Update() override;
	virtual bool Initialize() override;
};


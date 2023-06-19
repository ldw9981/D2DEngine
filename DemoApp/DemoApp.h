#pragma once

#include "resource.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/AnimationInstance.h"
#include "../D2DRenderer/AnimationAsset.h"
#include "../D2DRenderer/AnimationComponent.h"
#include "../D2DRenderer/SceneComponent.h"

class AnimationAsset;
class DemoObject;
class DemoApp: public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);
	virtual ~DemoApp();

	// override는 부모의 가상함수를 재정의 한다고 명확히 명시하여 새로 가상함수를 만드는 실수를 방지한다. 
	virtual bool Initialize() override;

	AnimationAsset* m_pAnimationAsset;
	DemoObject* m_pDemoObject;
};

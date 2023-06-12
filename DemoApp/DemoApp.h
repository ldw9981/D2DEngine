#pragma once

#include "resource.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/AnimationInstance.h"
#include "TestClass.h"
#include "../D2DRenderer/AnimationAsset.h"

class AnimationAsset;
class DemoApp: public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);
	virtual ~DemoApp();

	ID2D1Bitmap* m_pD2DBitmap1 = nullptr;
	ID2D1Bitmap* m_pD2DBitmap2 = nullptr;
	AnimationAsset* m_pAnimationAsset;

	AnimationAsset* m_pAnimAssetMidNight;

	AnimationInstance m_AnimationInstance1;
	AnimationInstance m_AnimationInstance2;

	AnimationInstance m_Background;

	TestClass1 A;	// TestClass1::~TestClass1()는 DemoApp::~DemoApp 호출 뒤에 호출된다. 
	TestClass2 B;	// 생성자 역순으로 밑에 있는 파괴자가 먼저 호출된다. 

	// override는 부모의 가상함수를 재정의 한다고 명확히 명시하여 새로 가상함수를 만드는 실수를 방지한다. 
	virtual bool Initialize() override;	
	virtual void Render() override;
	virtual void Update() override;
};

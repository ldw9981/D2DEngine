#pragma once

#include "resource.h"
#include "../D2DRenderer/GameApp.h"

#include "../D2DRenderer/Animation.h"
#include "../D2DRenderer/TestClass.h"

class AnimationInfo;
class DemoApp: public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);
	virtual ~DemoApp();

	ID2D1Bitmap* m_pD2DBitmap1 = nullptr;
	ID2D1Bitmap* m_pD2DBitmap2 = nullptr;
	AnimationInfo* m_pAnimationInfo;
	AnimationInstance* m_pAnimationInstance;

	TestClass A;	// 멤버변수 클래스의 파괴자는 소유자 클래스의 파괴자 보다 나중에 호출된다. 

	virtual bool Initialize();
	virtual void Finalize();
	virtual void Render();
	virtual void Update();
};

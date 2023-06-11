#pragma once

#include "resource.h"
#include "../D2DRenderer/GameApp.h"

#include "../D2DRenderer/Animation.h"
#include "../D2DRenderer/TestClass.h"

class AnimationAsset;
class DemoApp: public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);
	virtual ~DemoApp();

	ID2D1Bitmap* m_pD2DBitmap1 = nullptr;
	ID2D1Bitmap* m_pD2DBitmap2 = nullptr;
	AnimationAsset* m_pAnimationAsset;
	AnimationInstance m_AnimationInstance;

	TestClass1 A;	// ������� Ŭ������ �ı��ڴ� ������ Ŭ������ �ı��� ���� ���߿� ȣ��ȴ�. 
	TestClass2 B;	// �ؿ� �ִ� �ı��ڰ� ���� ȣ��ȴ�. 

	virtual bool Initialize();
	virtual void Render();
	virtual void Update();
};

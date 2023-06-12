#pragma once

#include "resource.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/AnimationInstance.h"
#include "TestClass.h"

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

	TestClass1 A;	// TestClass1::~TestClass1()�� DemoApp::~DemoApp ȣ�� �ڿ� ȣ��ȴ�. 
	TestClass2 B;	// ������ �������� �ؿ� �ִ� �ı��ڰ� ���� ȣ��ȴ�. 

	// override�� �θ��� �����Լ��� ������ �Ѵٰ� ��Ȯ�� ����Ͽ� ���� �����Լ��� ����� �Ǽ��� �����Ѵ�. 
	virtual bool Initialize() override;	
	virtual void Render() override;
	virtual void Update() override;
};

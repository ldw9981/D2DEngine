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

	// override�� �θ��� �����Լ��� ������ �Ѵٰ� ��Ȯ�� ����Ͽ� ���� �����Լ��� ����� �Ǽ��� �����Ѵ�. 
	virtual bool Initialize() override;

	ID2D1Bitmap* m_pD2DBitmap1 = nullptr;
	ID2D1Bitmap* m_pD2DBitmap2 = nullptr;
	AnimationAsset* m_pAnimationAsset;


	DemoObject* m_pDemoObject;
};

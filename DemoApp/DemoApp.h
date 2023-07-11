#pragma once

#include "resource.h"
#include "../D2DRenderer/GameApp.h"
#include "../D2DRenderer/AnimationAsset.h"
#include "../D2DRenderer/AnimationComponent.h"
#include "../D2DRenderer/SceneComponent.h"

#define MAX_DEMO_OBJECT 1

class AnimationAsset;
class DemoObject;
class CameraGameObject;
class FlatformObject;
class DemoApp: public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);
	virtual ~DemoApp();

	// override�� �θ��� �����Լ��� ������ �Ѵٰ� ��Ȯ�� ����Ͽ� ���� �����Լ��� ����� �Ǽ��� �����Ѵ�. 
	virtual bool Initialize(UINT Width,UINT Height) override;

	AnimationAsset* m_pAnimationAsset;
	FlatformObject* m_pTest1Object[MAX_DEMO_OBJECT];
	//CameraGameObject* m_pCameraGameObject;
};

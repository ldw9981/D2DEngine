#pragma once

#include <map>
#include <string>
#include "TestClass.h"

class AnimationAsset;
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static ID2D1HwndRenderTarget* m_pRenderTarget;
	static D2DRenderer* m_Instance;
public:
	ID2D1Factory* m_pD2DFactory;		// D2D ��ü �������̽� ������ ����	
	IWICImagingFactory* m_pWICFactory;	// D2D��Ʈ�� ������ ���� �̹��� ó�� �������̽�
	IDWriteFactory* m_pDWriteFactory;	// TextFormat������ ���� ���丮
	IDWriteTextFormat* m_pDWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format

	std::map<std::wstring,ID2D1Bitmap*>		m_BitmapResourceContainer;
	std::map<std::wstring, AnimationAsset*>	m_AnimationInfoResources;
public:
	HRESULT Initialize();

	void EndDraw();

	HRESULT CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** ppID2D1Bitmap);

	AnimationAsset* CreateAnimationInfo(std::wstring key);
};


#pragma once

#include <map>
#include <string>

class AnimationAsset;
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static ID2D1HwndRenderTarget* m_pRenderTarget;
	static D2DRenderer* m_Instance;
public:
	ID2D1Factory* m_pD2DFactory;		// D2D 개체 인터페이스 포인터 변수	
	IWICImagingFactory* m_pWICFactory;	// D2D비트맵 생성을 위한 이미지 처리 인터페이스
	IDWriteFactory* m_pDWriteFactory;	// TextFormat생성을 위한 팩토리
	IDWriteTextFormat* m_pDWriteTextFormat; // 기본 텍스트 출력을 위한 Format

	std::map<std::wstring,ID2D1Bitmap*>		m_SharingBitmaps;
	std::map<ID2D1Bitmap*,std::wstring>		m_SharingBitmapKeys;

	std::map<std::wstring, AnimationAsset*>	m_SharingAnimationAssets;
	std::map<AnimationAsset*,std::wstring>	m_SharingAnimationAssetKeys;
public:
	HRESULT Initialize();

	void EndDraw();

	// 공유하는 비트맵 생성
	HRESULT CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	AnimationAsset* CreateAnimationAsset(std::wstring key);

	// 릴리즈를 대신 호출하면서 카운터가 0이되면 공유중인 목록에서 제거한다.
	void ReleaseD2DBitmapFromFile(ID2D1Bitmap* pBitmap);
	void ReleaseAnimationAsset(AnimationAsset* pAnimationAsset);

};


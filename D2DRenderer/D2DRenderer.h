#pragma once

#include <map>
#include <string>
#include <list>

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
	ID2D1SolidColorBrush* m_pBrush;	// 렌더타겟이 생성하는 리소스 역시 장치의존
	IDXGIFactory4* m_pDXGIFactory;		// DXGI팩토리
	IDXGIAdapter3* m_pDXGIAdapter;



	std::list<std::pair<std::wstring, ID2D1Bitmap*>> m_SharingBitmaps;
	std::list<std::pair<std::wstring, AnimationAsset*>> m_SharingAnimationAssets;
public:
	HRESULT Initialize();

	void DrawRectangle(ID2D1RenderTarget* pRenderTarget,D2D1_RECT_F rect, D2D1_COLOR_F color);
	void EndDraw();


	// 공유하는 비트맵 생성
	HRESULT CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	// 파일이름으로 읽어와야하지만 그냥 비어있는 인스턴스 리턴한다.
	AnimationAsset* CreateAnimationAsset(std::wstring strFilePath);

	// 릴리즈를 대신 호출하면서 카운터가 0이되면 공유중인 목록에서 제거한다.
	void ReleaseD2DBitmapFromFile(ID2D1Bitmap* pBitmap);
	void ReleaseAnimationAsset(AnimationAsset* pAnimationAsset);
	ID2D1SolidColorBrush* GetBrush() const { return m_pBrush; }

	size_t GetUsedVRAM();
private:

};


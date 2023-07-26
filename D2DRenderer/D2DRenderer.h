#pragma once

#define NOIMAGE L"../Resource/NoImage.png"
/*
	Direct2D의 기본 기능을 래핑한 클래스
	기본 렌더 타겟을 생성한다.
	간단한 리소스관리자 로서 공유하는 비트맵과 
	공유하는 애니메이션 어셋을 생성하는 기능을 제공한다.
*/
class AnimationAsset;
class RenderComponent;
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static ID2D1HwndRenderTarget* m_pRenderTarget;
	static D2DRenderer* m_Instance;
	static D2D1_MATRIX_3X2_F m_CameraTransform;		// 카메라의 좌표계로 변환하는 행렬
	static D2D1_MATRIX_3X2_F m_ScreenTransform;		// 왼쪽 하단이 0,0인 화면의 좌표계로 변환하는 행렬   
private:
	ID2D1Factory* m_pD2DFactory;		// D2D 개체 인터페이스 포인터 변수	
	IWICImagingFactory* m_pWICFactory;	// D2D비트맵 생성을 위한 이미지 처리 인터페이스
	IDWriteFactory* m_pDWriteFactory;	// TextFormat생성을 위한 팩토리
	IDWriteTextFormat* m_pDWriteTextFormat; // 기본 텍스트 출력을 위한 Format
	ID2D1SolidColorBrush* m_pBrush;	// 렌더타겟이 생성하는 리소스 역시 장치의존
	IDXGIFactory4* m_pDXGIFactory;		// DXGI팩토리
	IDXGIAdapter3* m_pDXGIAdapter;		// 비디오카드 정보에 접근 가능한 인터페이스
	HWND m_hWnd;

	std::list<std::pair<std::wstring, ID2D1Bitmap*>> m_SharingBitmaps;
	std::list<std::pair<std::wstring, AnimationAsset*>> m_SharingAnimationAssets;	
public:
	HRESULT Initialize(HWND hWnd);

	void DrawRectangle(ID2D1RenderTarget* pRenderTarget,D2D1_RECT_F rect, D2D1_COLOR_F color);
	void DrawCrossLine(ID2D1RenderTarget* pRenderTarget,D2D1_VECTOR_2F point = {0.0f,0.0f}, D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::LightGreen));
	void DrawEllipse(ID2D1RenderTarget* pRenderTarget,D2D1_ELLIPSE ellipse, D2D1_COLOR_F color);
	void DrawText(ID2D1RenderTarget* pRenderTarget,const std::wstring& string,D2D1_RECT_F rect, D2D1_COLOR_F color);



	// 카메라의 월드 변환을 넣어 역행렬을 계산하여 저장한다.
	void SetCameraTransform(const D2D1_MATRIX_3X2_F& worldTrasnform);
	// 공유하는 비트맵 생성
	bool CreateSharedD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	// 파일이름으로 읽어와야하지만 그냥 비어있는 인스턴스 리턴한다.
	AnimationAsset* CreateSharedAnimationAsset(std::wstring strFilePath);

	// 릴리즈를 대신 호출하면서 카운터가 0이되면 공유중인 목록에서 제거한다.
	void ReleaseSharedD2DBitmap(ID2D1Bitmap* pBitmap);
	void ReleaseSharedAnimationAsset(AnimationAsset* pAnimationAsset);
	ID2D1SolidColorBrush* GetBrush() const { return m_pBrush; }

	size_t GetUsedVRAM();
	D2D_SIZE_U GetClientSize();

	static void UpdateScreenTransform(D2D_SIZE_U ScreenSize);
};


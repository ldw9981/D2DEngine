#pragma once


class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static ID2D1HwndRenderTarget* m_pRenderTarget;
public:
	//  D2D 개체 인터페이스 포인터 변수
	ID2D1Factory* m_pD2DFactory = nullptr;
	// D2D1비트맵 생성을 위한 이미지 처리 인터페이스
	IWICImagingFactory* m_pWICFactory = nullptr;
public:
	HRESULT Initialize();

	void EndDraw();

	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	void Finalize();
};


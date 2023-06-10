#pragma once

using namespace std;

#include <map>

class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static ID2D1HwndRenderTarget* m_pRenderTarget;
public:
	
	ID2D1Factory* m_pD2DFactory;		// D2D 개체 인터페이스 포인터 변수	
	IWICImagingFactory* m_pWICFactory;	// D2D비트맵 생성을 위한 이미지 처리 인터페이스
	IDWriteFactory* m_pDWriteFactory;	// TextFormat생성을 위한 팩토리
	IDWriteTextFormat* m_pDWriteTextFormat; // 기본 텍스트 출력을 위한 Format

	std::map<std::wstring,ID2D1Bitmap*> m_BitmapContainer;
public:
	HRESULT Initialize();

	void EndDraw();

	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	void Finalize();
};


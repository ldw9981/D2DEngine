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
	
	ID2D1Factory* m_pD2DFactory;		// D2D ��ü �������̽� ������ ����	
	IWICImagingFactory* m_pWICFactory;	// D2D��Ʈ�� ������ ���� �̹��� ó�� �������̽�
	IDWriteFactory* m_pDWriteFactory;	// TextFormat������ ���� ���丮
	IDWriteTextFormat* m_pDWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format

	std::map<std::wstring,ID2D1Bitmap*> m_BitmapContainer;
public:
	HRESULT Initialize();

	void EndDraw();

	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	void Finalize();
};


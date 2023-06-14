#pragma once
#include "D2DRenderer.h"

class D2DBitmap 
{
public:
	D2DBitmap()
	{
		
	}
	D2DBitmap(const D2DBitmap& other)
	{		
		m_pID2D1Bitmap = other.m_pID2D1Bitmap;	
		other.m_pID2D1Bitmap->AddRef();
	}
	virtual ~D2DBitmap()
	{
		D2DRenderer::m_Instance->ReleaseD2DBitmapFromFile(m_pID2D1Bitmap);
	}

	ID2D1Bitmap* m_pID2D1Bitmap = nullptr;

public:
	bool IsValid()
	{
		return m_pID2D1Bitmap!=nullptr;
	}
};

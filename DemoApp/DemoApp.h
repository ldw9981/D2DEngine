#pragma once

#include "resource.h"
#include "../D2DRenderer/GameApp.h"


class DemoApp: public GameApp
{
public:
	DemoApp(HINSTANCE hInstance);

	ID2D1Bitmap* m_pD2DBitmap1 = nullptr;
	ID2D1Bitmap* m_pD2DBitmap2 = nullptr;

	virtual bool Initialize();
	virtual void Finalize();
	virtual void Render();
};

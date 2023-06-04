#pragma once

#include "resource.h"
#include "../D2DEngine/GameApp.h"

class DemoApp: public GameApp
{
public:
	DemoApp(HINSTANCE hInstance,int nCmdShow);

	HWND mem;
};

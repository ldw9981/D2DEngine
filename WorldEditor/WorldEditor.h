
// WorldEditor.h: WorldEditor 애플리케이션의 기본 헤더 파일
//
#pragma once
#include "../D2DRenderer/D2DRenderer.h"
#include "../D2DRenderer/World.h"
#include "../D2DRenderer/TimeSystem.h"

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CWorldEditorApp:
// 이 클래스의 구현에 대해서는 WorldEditor.cpp을(를) 참조하세요.
//

class CWorldEditorApp : public CWinAppEx
{
public:
	CWorldEditorApp() noexcept;


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	D2DRenderer m_Renderer;
		
	// 플레이모드에서는 편집한 월드를 복사해서 원본은 유지하면서 게임플레이를 해본다.
	// 편집모드로 돌아가면 플레이월드는 초기화한다.
	bool m_bPlayMode;	// PlayMode or EditMode  
	World* m_pCurrWorld;
	World m_PlayWorld;

	static float m_deltaTime;
	GameTimer m_Timer;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	void Update();
	void Render();
	void CalculateFrameStats();
	void SetWorld(World* pWorld) { m_pCurrWorld = pWorld;  }

	void SetMode(bool PlayMode);

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
};

extern CWorldEditorApp theApp;

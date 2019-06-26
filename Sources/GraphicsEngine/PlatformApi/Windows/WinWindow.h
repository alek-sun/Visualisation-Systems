#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"
#include <Windows.h>


// Appication window implementation in Windows OS
class WinWindow
{
public:
	WinWindow(const TCHAR * pTitle);
	~WinWindow();

	void Init(GraphicsEngineImpl * pEngineImpl);
	void Deinit();

	void Show();
	HWND GetHWND();
	void SetResolution();
	void GetResolution(int & width, int & height);

	void DispatchMessages();
	bool IsRunning();

private:
	HWND		m_hWnd;
	WNDCLASSEX	m_wc;
	MSG			m_msg;

	const TCHAR * m_pTitle;

	GraphicsEngineImpl * m_pWindowsEngineImpl;
};

#endif

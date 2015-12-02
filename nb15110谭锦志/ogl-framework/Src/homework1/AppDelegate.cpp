#include "AppDelegate.h"
#include "../GLWindow/GLWindow.h"

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{

}

//ApplicationDelegate theApp;
BOOL AppDelegate::InitInstance()
{
	GLWindow *pMainWnd = new GLWindow();
	assert(pMainWnd);
	m_pMainWnd = (LPVOID)pMainWnd;

	BOOL bRet = pMainWnd->CreateEx(0, "OpenGL", "ogl-framework", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);
	if (!bRet)
	{
		return FALSE;  // 创建窗口GLWindow窗口失败
	}

	pMainWnd->ShowWindow(SW_SHOW);
	pMainWnd->UpdateWindow();

	return TRUE;
}

BOOL AppDelegate::ExitInstance()
{
	if (m_pMainWnd)
	{
		delete m_pMainWnd;
		m_pMainWnd = NULL;
	}
	return true;
}


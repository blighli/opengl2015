#include "AppDelegate.h"
#include "MainScene.h"

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{

}

BOOL AppDelegate::InitInstance()
{
	MainScene *pMainWnd = new MainScene();
	if (NULL == pMainWnd)
	{
		return 0; // 窗口创建失败
	}
	m_pMainWnd = (LPVOID)pMainWnd;  // 保留指针，程序退出时将其delete

	pMainWnd->CreateGlWnd("ogl-framework", 30, 20, 800, 600);
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


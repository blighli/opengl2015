#include "QWndApp.h"
#include "Global.h"

QWndApp::QWndApp()
{
	m_pMainWnd = NULL;
	g_pWndApp = this;  // 保存全局app指针
}

QWndApp::~QWndApp()
{
	
}

BOOL QWndApp::InitInstance()
{
	return true;
}

BOOL QWndApp::ExitInstance()
{
	return true;
}

// 消息循环
void QWndApp::run()
{
	// 消息循环
	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0))
	{
		::DispatchMessage(&msg);  // 翻译
		::TranslateMessage(&msg); // 派发
	}
}


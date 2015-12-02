/************************************************************************/
/* 应用程序基类                                                           */
/************************************************************************/
#pragma once
#include "stdafx.h"

class QWndApp
{
public:
	QWndApp();
	~QWndApp();

public:
	virtual BOOL InitInstance();   // 初始化 app
	virtual BOOL ExitInstance();   // 退出 app
	virtual void run();			   // 运行

private:
	LPVOID m_pMainWnd;
};

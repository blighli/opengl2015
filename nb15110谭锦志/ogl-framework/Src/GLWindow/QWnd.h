#pragma once
#include "stdafx.h"

class QWnd
{
public:
	QWnd();

	// 虚析构
	virtual ~QWnd();

	// 创建窗口
	BOOL CreateEx(DWORD dwExStyle,
		LPCTSTR lpClassName,
		LPCTSTR lpWindowName,
		DWORD dwStyle,
		int x,
		int y,
		int nWidth,
		int nHeight,
		QWnd* pWndParent,
		HMENU hMenu);
private:
	HWND m_hWnd;
};


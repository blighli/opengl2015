#pragma once
#include "../GLWindow/QWndApp.h"

class ApplicationDelegate : QWndApp
{
public:
	ApplicationDelegate();
	~ApplicationDelegate();

public:

	// 初始化程序
	virtual BOOL InitInstance();

	// 退出程序
	virtual BOOL ExitInstance();
};

extern ApplicationDelegate theApp; // 全局app
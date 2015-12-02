#pragma once

#include "stdafx.h"
#include "QWndApp.h"

// 后期改为单例
extern QWndApp *g_pWndApp; // 全局应用程序指针
extern QWndApp *GlbGetApp();
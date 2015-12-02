#include "ApplicationDelegate.h"

ApplicationDelegate::ApplicationDelegate()
{

}

ApplicationDelegate::~ApplicationDelegate()
{

}

// 处理窗口消息
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		::DestroyWindow(hWnd); // 销毁窗口
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);  // 推出程序
		break;
	default:
		break;
	}
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}


ApplicationDelegate theApp;
BOOL ApplicationDelegate::InitInstance()
{
	HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);
	assert(hInstance);

	WNDCLASSEX wcex;
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)::GetStockObject(GRAY_BRUSH);
	wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = ::LoadIcon(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = "OpenGL";
	wcex.lpszMenuName = NULL;
	wcex.style = CS_VREDRAW | CS_HREDRAW;

	BOOL bRet = ::RegisterClassEx(&wcex); // 注册窗口
	if (!bRet)
	{
		return 0; // 注册窗口类失败
	}

	// 创建窗口
	HWND hWnd = ::CreateWindowEx(0, wcex.lpszClassName, "ogl-framework",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (NULL == hWnd)
	{
		return 0; // 创建窗口失败
	}

	::ShowWindow(hWnd, SW_SHOW);
	::UpdateWindow(hWnd);
}

BOOL ApplicationDelegate::ExitInstance()
{
	return true;
}


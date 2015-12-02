#include "GLWindow.h"

GLWindow::GLWindow()
{

}

GLWindow::~GLWindow()
{

}

HRESULT GLWindow::OnClose(WPARAM wParam, LPARAM lParam)
{
	return DestroyWindow();
}

LRESULT GLWindow::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}


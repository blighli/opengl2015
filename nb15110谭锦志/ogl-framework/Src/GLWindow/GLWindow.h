#pragma once
#include "QWnd.h"

class GLWindow : public QWnd
{
public:
	GLWindow();
	~GLWindow();

	HRESULT OnClose(WPARAM wParam, LPARAM lParam);
	LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
private:

};
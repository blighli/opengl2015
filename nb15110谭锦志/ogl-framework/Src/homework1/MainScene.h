#pragma once
#include "../GLWindow/GLWindow.h"  // 使用GLWindow ： 基于win32封装的窗口应用类库

class MainScene : public GLWindow
{
public:
	MainScene();
	~MainScene();

	// 初始化
	BOOL initGL(GLvoid);

	// 绘制场景
	BOOL DrawGL(GLvoid);

	// 更新窗口消息
	BOOL UpdateGL(GLvoid);

	// opengl窗口销毁前的处理
	GLvoid DestroyGL(GLvoid);

private:
	float m_posx;
};
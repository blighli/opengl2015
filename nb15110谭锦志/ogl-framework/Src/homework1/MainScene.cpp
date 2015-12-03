#include "MainScene.h"

MainScene::MainScene()
{
	m_posx = -1.5f;
}

MainScene::~MainScene()
{

}

BOOL MainScene::initGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	// 选择深度测试方
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // 最精细的透视计算

	return TRUE;
}

BOOL MainScene::DrawGL(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清除颜色和深度缓存
	glLoadIdentity();
	// 重置当前矩阵
	glFlush();

	int NUM = 200;
	// 定义绘制圆时用的顶点数(用顶点组成的线段逼近圆)(new)
	GLfloat r = 1.0f;
	// 定义圆半径(new)
	glTranslatef(m_posx, 1.0f, -7.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	// 绘制三角形
	glVertex3f(0.0f, 1.0f, 0.0f);
	// 上顶点
	glVertex3f(-1.0f, -1.0f, 0.0f);
	// 左下顶点
	glVertex3f(1.0f, -1.0f, 0.0f);
	// 右下顶点
	glEnd();

	// 刷新GL命令队列
	return TRUE;
}

BOOL MainScene::UpdateGL(GLvoid)
{
	/* 
	* 系统键盘映射说明
	* F1->F12     : VK_F1 -> VK_F12
	* num 0 -> 9  : VK_NUMPAD0 -> VK_NUMPAD9
	* char A -> Z : 0x41 -> ... 递增 。
	*/

	if (keyUp(0x41))
	{
		m_posx += 0.01f;
	}

	return TRUE;
}

GLvoid MainScene::DestroyGL(GLvoid)
{

}


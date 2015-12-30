// homework1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"  
#include <GL/glut.h>

// 太阳、地球和月亮
// 假设每个月都是 30 天
// 一年 12 个月，共是 360 天
static int day = 200; //day的初始值， day 的变化：从 0 到 359
void myDisplay(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 40000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -23000000, 23000000, 0, 0, 0, 0, 0, 1);
	// 绘制红色的“太阳”
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(6960000, 15000,15000);
	// 绘制蓝色的“地球”
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(15000000, 0.0f, 0.0f);
	glutSolidSphere(1594500, 15000,15000);
	// 绘制黄色的“月亮”
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(3800000, 0.0f, 0.0f);
	glutSolidSphere(434500, 15000, 15000);
	glFlush();
	glutSwapBuffers();
}

void myIdle(void)
{
	/* 新的函数，在空闲时调用，作用是把日期往后移动一天并重新绘制，达到动画效果 */
	++day;
	if (day >= 360)
		day = 0;
	myDisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // 修改了参数为 GLUT_DOUBLE
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("太阳，地球和月亮"); // 改了窗口标题
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle); 
	glutMainLoop();
	return 0;
}


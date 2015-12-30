// homework1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <time.h>
#include <GL/glut.h>
#define WIDTH 400	
#define HEIGHT 400
static GLfloat angle = 0.0f;
static float day = 200; // day 的变化：从 0 到 359

double CalFrequency()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;
	++count;
	if (count <= 50)
		return save;
	count = 0;
	last = current;
	current = clock();
	timegap = (current - last) / (double)CLK_TCK;
	save = 50.0 / timegap;
	return save;
}
void myDisplay(void)
{
	float FPS = CalFrequency();
	printf("FPS = %.4f\n", FPS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 创建透视效果视图
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// 定义太阳光源，它是一种白色的光源
	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}
	// 定义太阳的材质并绘制太阳
	{
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
		glutSolidSphere(2.0, 40, 32);
	}
	// 定义地球的材质并绘制地球
	{
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
		glRotatef(angle, 0.0f, -1.0f, 0.0f);
		glTranslatef(7.0f, 0.0f, 0.0f);
		glutSolidSphere(1.0, 40, 32);
	}
	//定义月亮的材质并绘制地球
	{
		GLfloat moon_mat_ambient[] = { 0.5f, 0.5f, 0.0f, 1.0f };
		GLfloat moon_mat_diffuse[] = { 0.5f, 0.5f, 0.0f, 1.0f };
		GLfloat moon_mat_specular[] = { 0.5f, 0.5f, 0.0f, 1.0f };
		GLfloat moon_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat moon_mat_shininess = 30.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, moon_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, moon_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, moon_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, moon_mat_shininess);
		glRotatef(angle / 30.0*360.0 - angle / 360.0*360.0, 0.0f, -1.0f, -0.0f);
		glTranslatef(2.0f, 0.0f, 0.0f);
		glutSolidSphere(0.5, 100, 100);
	}
	glutSwapBuffers();
}
void myIdle(void)
{
	angle += 0.05f;
	if (angle >= 360.0f)
		angle = 0.0f;
	myDisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL 光照演示");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
	return 0;
}
/*
void myDisplay(void)
{
double FPS = CalFrequency();
printf("FPS = %f\n", FPS);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 创建透视效果视图
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
glEnable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//glClear(GL_COLOR_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(90, 1,100000000, 450000000);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);
// 绘制红色的“太阳”
glColor3f(1.0f, 0.0f, 0.0f);
glutSolidSphere(60000000, 100, 100);
// 绘制蓝色的“地球”
glColor3f(0.0f, 0.0f, 1.0f);
glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
glTranslatef(150000000, 0.0f, 0.0f);
glutSolidSphere(15945000, 100, 100);
// 绘制黄色的“月亮”
glColor3f(1.0f, 1.0f, 0.0f);
glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
glTranslatef(38000000, 0.0f, 0.0f);
glutSolidSphere(4345000, 100, 100);
glFlush();
glutSwapBuffers();
}

void myIdle(void)
{
/* 新的函数，在空闲时调用，作用是把日期往后移动一天并重新绘制，达到动画效果
day += 0.1;
if (day >= 360.0)
day = 0;
myDisplay();
}
int main(int argc, char *argv[])
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
glutInitWindowPosition(100, 100);
glutInitWindowSize(500, 500);
glutCreateWindow("太阳，地球和月亮");
glutDisplayFunc(&myDisplay);
glutIdleFunc(&myIdle);
glutMainLoop();
return 0;
}
*/
// OpenglWork1.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <GL/glut.h>
#include <math.h>

//漫反射光参数
GLfloat lightDiffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightDiffuse1[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat lightDiffuse2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightDiffuse3[] = { 0.0f, 1.0f, 0.0f, 1.0f };

//光源位置
GLfloat lightPosition[] = { 0.0f, 4.0f, 0.0f, 1.0f };

float spin = 0;
static GLint fogMode;
const int n = 100;
GLfloat R = 1.0f;
const GLfloat Pi = 3.1415926536f;
void DrawCircle()
{
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse3);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; ++i)
	{
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(R*cos(2 * Pi / n*i), 0, R*sin(2 * Pi / n*i));
	}
	glEnd();
	glFlush();
}

void display(void)
{
	glEnable(GL_DEPTH_TEST); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT1);
	
	glEnable(GL_LIGHTING);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix(); //记住太阳的位置
	glutSolidSphere(1.0, 20, 16);   //太阳
	
	R = 4;
	DrawCircle();

	glRotatef(spin, 0.0, 1.0, 0.0);  //公转，绕着一个向量以给定角度旋转（正的为逆时针）
	glTranslatef(4.0, 0.0, 0.0);

	R = 1;
	DrawCircle();

	glPushMatrix(); //记住地球的位置
	glRotatef(spin, 1.0, 0.0, 0.0); //自转
	glColor3f(0.0, 0.0, 1.0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
	glutSolidSphere(0.5, 16, 8);   //地球

	glPopMatrix();//回到地球的位置
	glColor3f(0.0, 1.0, 0.0);
	//glTranslatef(1.0, 0.0, 0.0);
	glRotatef(3 * spin, 0.0, 1.0, 0.0);//月球绕地球转
	////glPopMatrix();//回到地球的位置
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef(5 * spin, 1.0, 0.0, 0.0);//月球自转

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse2);
	glutSolidSphere(0.3, 16, 8); //月亮
	glPopMatrix();//回到原来的位置
	glutSwapBuffers();
}
void spinDisplay(void)
{
	spin = spin + 0.05;
	if (spin > 360)
		spin = spin - 360;
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


int _tmain(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MyOpengGL");
	glutDisplayFunc(display);
	glutIdleFunc(spinDisplay);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}


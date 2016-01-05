#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl/glut.h"

static double year = 0, day = 0, startYear = 0;
static double moonday = 0, moonmonth = 0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	/*绘画太阳*/
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);//太阳自转
	glutWireSphere(1.01, 20, 16);
	//glutSolidSphere(1.0, 20, 16);
	glPopMatrix();

	//glPushMatrix();
	/*绘制行星*/
	glPushMatrix();
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);//行星公转
	glTranslatef(3.0, 0.0, 0.0);
	glColor3f(0.0, 0.5, 0.5);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);//行星自转
	glutWireSphere(0.3, 10, 8);

	/*绘制卫星轨道*/
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	//glRotatef(45.0f, 0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 1.0, 10, 64);
	glPopMatrix();

	/*绘画卫星*/
	glPushMatrix();
	glRotatef((GLfloat)moonmonth, 0.0, 1.0, 0.0);
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)moonday, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.6, 0.5);
	glutWireSphere(0.2, 10, 8);
	glPopMatrix();
	glPopMatrix();

	/*绘制行星轨道*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	glutSolidTorus(0.005, 3.0, 10, 64);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0);
}

void idle()
{
	moonday = moonday + 2.4;
	if (moonday >= 360)
	{
		moonday -= 360;
	}
	moonmonth = moonmonth + 1.5;
	if (moonmonth >= 360)
	{
		moonmonth -= 360;
	}
	day = day + 1.2;
	if (day >= 360)
	{
		day -= 360;
	}
	year = year + 0.5;
	if (day >= 360)
	{
		year -= 360;
	}
	startYear = startYear + 0.1;
	if (startYear >= 360)
	{
		startYear -= 360;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutRotateFunc(rotate);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
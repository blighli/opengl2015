#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl/glut.h"

static double sunRot = 0, firstPlaRot = 0;
static double firstPlaSatRot = 0, firstPlaSatRev = 0;
static double secondPlaRot = 0, secondPlaRev = 0;
static double thirdPlaRev = 0, thirdPlaRot = 0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	/*太阳*/
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRotatef((GLfloat)sunRot, 0.0, 0.0, 1.0);//太阳自转
	glutWireSphere(2, 30, 16);
	glPopMatrix();

	/*第一颗行星轨道*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 5.0, 10, 64);
	glPopMatrix();
	/*第一颗行星*/
	glPushMatrix();
	glRotatef((GLfloat)sunRot, 0.0, 0.0, 1.0);//公转
	glTranslatef(5.0, 0.0, 0.0);
	glColor3f(0.5, 0.3, 0.6);
	glRotatef((GLfloat)firstPlaRot, 0.0, 0.0, 1.0);//自转
	glutWireSphere(0.3, 10, 8);

	/*第一颗行星的卫星轨道*/
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	glutSolidTorus(0.005, 1.0, 10, 64);
	glPopMatrix();

	/*第一颗行星的卫星*/
	glPushMatrix();
	glRotatef((GLfloat)firstPlaSatRev, 0.0, 0.0, 1.0);//公转
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)firstPlaSatRot, 0.0, 0.0, 1.0);//自转
	glColor3f(0.5, 0.6, 0.5);
	glutWireSphere(0.1, 10, 8);
	glPopMatrix();
	glPopMatrix();


	/*第二颗行星轨道*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 8.0, 10, 64);
	glPopMatrix();

	/*第二颗行星*/
	glPushMatrix();
	glRotatef((GLfloat)secondPlaRev, 0.0, 0.0, 1.0);//公转
	glTranslatef(8.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glRotatef((GLfloat)secondPlaRot, 0.0, 0.0, 1.0);//自转
	glutWireSphere(1, 20, 10);
	glPopMatrix();

	/*第三颗行星轨道*/
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 11.0, 10, 64);
	glPopMatrix();

	/*第三颗行星*/
	glPushMatrix();
	glRotatef((GLfloat)thirdPlaRev, 0.0, 0.0, 1.0);//行星公转
	glTranslatef(11.0, 0.0, 0.0);
	glColor3f(0.36, 0.88, 0.44);
	glRotatef((GLfloat)thirdPlaRot, 0.0, 0.0, 1.0);//行星自转
	glutWireSphere(0.45, 10, 8);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, -20.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void resetAngle(double& angle)
{
	if (angle >= 360)
	{
		angle -= 360;
	}
}

void idle()
{
	//太阳自转，第一颗行星的公转
	sunRot += 1;
	resetAngle(sunRot);
	//第一颗行星的自转
	firstPlaRot += 1.1;
	resetAngle(firstPlaRot);
	//第一颗行星的卫星自转
	firstPlaSatRot += 0.1;
	resetAngle(firstPlaSatRot);
	//第一颗行星的卫星公转
	firstPlaSatRev += 0.3;
	resetAngle(firstPlaSatRot);
	//第二颗行星的自转
	secondPlaRot += 1.2;
	resetAngle(secondPlaRot);
	//第二颗行星的公转
	secondPlaRev += 0.8;
	resetAngle(secondPlaRev);
	//第三颗行星的自转
	thirdPlaRot += 1.4;
	resetAngle(thirdPlaRot);
	//第三颗行星的公转
	thirdPlaRev += 0.6;
	resetAngle(thirdPlaRev);

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
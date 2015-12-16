#include "GL/glut.h"
#include <math.h>
#include<stdio.h>
// Rotation amounts
static GLfloat xans = 0.0f;
static GLfloat yans = 0.0f;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xans, 1.0f, 0.0f, 0.0f);
	glRotatef(yans, 0.0f, 1.0f, 0.0f);

	//绘制太阳
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(60.0f, 15, 15);
	
	//绘制地球
	static GLfloat angle = 0;
	const GLfloat radius = 100.0f;
	glRotatef(angle, 0, 0, 1);
	glTranslatef(radius, radius, 0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(30.0f, 15, 15);

	// 绘制月亮
	glColor3f(1.0f, 0.5f, 0.0f);
	glRotatef(angle / 30.0*360.0 - angle / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(radius / 2, 0.0f, 0.0f);
	glutSolidSphere(15, 50, 50);
	
	//每次旋转0.05°，控制旋转速度
	angle += 0.1;
	if (angle >= 360)
	{
		angle -= 360;
	}

	glPopMatrix();

	glutSwapBuffers();
}

void SquareSize(GLsizei w, GLsizei h)
{
	GLfloat size = 300.0f;

	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat fAspect;
	fAspect = (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-size, size, -size*h / w, size*h / w, -size, size);
	else
		glOrtho(-size*w / h, size*w / h, -size, size, -size, size);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TouchKeyborad(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xans -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xans += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yans -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yans += 5.0f;

	if (xans > 356.0f)
		xans = 0.0f;

	if (xans < -1.0f)
		xans = 355.0f;

	if (yans > 356.0f)
		yans = 0.0f;

	if (yans < -1.0f)
		yans = 355.0f;

	glutPostRedisplay();

}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("太阳系");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(SquareSize);
	glutSpecialFunc(TouchKeyborad);
	init();
	glutMainLoop();

	return 1;
}

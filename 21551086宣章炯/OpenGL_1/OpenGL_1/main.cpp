//
//  main.cpp
//  OpenGL_1
//
//  Created by John on 15/12/8.
//  Copyright © 2015年 John. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <stdio.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

#include <math.h>

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored"-Wdeprecated-declarations"

#define ROT_SPEED 2

static int yAngle = 0, mAngle = 0, dAngle = 0;
static float sAngle = 0;

//太阳
void drawSun() {
    glPushMatrix();  //压栈
    glColor3f(1, 0, 0);
    glRotatef(sAngle, 0, 0, 1);
    glutWireSphere(1, 24, 20);
}

//地球
void drawEarth() {
    glColor3f(0, 0, 1);
    glTranslatef(0, 2.5, 0);
    glRotatef((GLfloat)mAngle, 0, 0, 1);
    glutWireSphere(0.3, 12, 10);
}

//月亮
void drawMoon() {
    glTranslatef(1, 0, 0);
    glRotatef((GLfloat)dAngle, 0, 0, 1);
    glColor3f(1, 1, 1);
    glutWireSphere(0.15, 10, 8);
}

void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    drawSun();
    drawEarth();
    drawMoon();
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void timeChange(int i)
{
    yAngle = (yAngle + ROT_SPEED) % 360;
    mAngle = (mAngle + ROT_SPEED) % 360;
    dAngle = (dAngle + ROT_SPEED) % 360;
    sAngle = (sAngle >= 360) ? 0 : sAngle + 0.5 * ROT_SPEED;
    glutPostRedisplay();
    glutTimerFunc(10, timeChange, 1);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
     gluPerspective(fovy,aspect,zNear,zFar)
     GLdouble fovy,
     GLdouble aspect,
     GLdouble zNear,
     GLdouble zFar
     */
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*
     void gluLookAt(GLdouble eyex,GLdouble eyey,GLdouble eyez,
     GLdouble centerx,GLdouble centery,GLdouble centerz,
     GLdouble upx,GLdouble upy,GLdouble upz);
     */
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 0, 1);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("宣章炯OpenGL第一次作业");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, timeChange, 1);
    glutMainLoop();
    return 0;
}
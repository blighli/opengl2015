//
//  main.cpp
//  sun
//
//  Created by linbo on 15/12/6.
//  Copyright © 2015年 linbo. All rights reserved.
//
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>


static double year = 0, day = 0, startYear = 0;
static double moonDay = 0, moonMonth = 0;
//static double secondYear = 0, secondDay = 0;
//static double thirdYear = 0, thirdDay = 0;
//static double thirdSatelliteYear = 0, thridSatelliteDay = 0;


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    /*绘画太阳*/
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glRotatef((GLfloat)year, 0.0, 1.0, 0.0);//太阳自转
    glutWireSphere(1.01, 20, 16);
    //glutSolidSphere(1.0, 20, 16);
    glPopMatrix();
    
    /*绘制地球轨道*/
    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0);
    glRotatef(90.0f, 1.0, 0.0, 0.0);
    glutSolidTorus(0.005, 3.0, 10, 64);
    glPopMatrix();
    
    /*绘制地球*/
    glPushMatrix();
    glRotatef((GLfloat)year, 0.0, 1.0, 0.0);//行星公转
    glTranslatef(3.0, 0.0, 0.0);
    glColor3f(0.0, 0.1, 1.0);
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
    glRotatef((GLfloat)moonMonth, 0.0, 1.0, 0.0);
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)moonDay, 0.0, 1.0, 0.0);
    glColor3f(0.5, 0.6, 0.5);
    glutWireSphere(0.2, 10, 8);
    glPopMatrix();
    glPopMatrix();
    
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0);
}

void idle()
{
    moonDay = moonDay + 0.4;
    if (moonDay >= 360)
    {
        moonDay -= 360;
    }
    moonMonth = moonMonth + 0.3;
    if (moonMonth >= 360)
    {
        moonMonth -= 360;
    }
    day = day + 0.2;
    if (day >= 360)
    {
        day -= 360;
    }
//    可控制地球转动的速度
    year = year + 0.4;
    if (day >= 360)
    {
        year -= 360;
    }
    startYear = startYear + 0.02;
    if (startYear >= 360)
    {
        startYear -= 360;
    }
//    secondDay += 0.15;
//    if (secondDay>=360)
//    {
//        secondDay -= 360;
//    }
//    secondYear += 0.03;
//    if (secondYear>=360)
//    {
//        secondYear -= 360;
//    }
//    thirdDay += 0.1;
//    if (thirdDay>=360)
//    {
//        thirdDay -= 360;
//    }
//    thirdYear += 0.02;
//    if (thirdYear>=360)
//    {
//        thirdYear -= 360;
//    }
//    thirdSatelliteYear += 0.25;
//    if (thirdSatelliteYear>=360)
//    {
//        thirdSatelliteYear -= 360;
//    }
//    thridSatelliteDay += 0.2;
//    if (thridSatelliteDay>=360)
//    {
//        thridSatelliteDay -= 360;
//    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    初始化窗口大小
    glutInitWindowSize(1000, 600);
//    初始化位置
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
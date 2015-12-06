//
//  main.cpp
//  hmwFirst
//
//  Created by zhuzhu on 15/12/6.
//  Copyright © 2015年 wequeen. All rights reserved.
//

#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

static double revolution = 0, rotation = 0;
static double moon = 0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    //太阳
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    
    //太阳的自转，第一个参数是旋转地角度，后三个参数确定围绕的坐标轴
    glRotatef((GLfloat)revolution, 0.0, 1.0, 0.0);
    
    //渲染太阳球体，第一个参数是半径，第二个参数是经线条数，第三个参数是纬线条数
    glutWireSphere(1.2, 25, 25);
    glPopMatrix();
    
    //地球
    glPushMatrix();
    
    //地球公转
    glRotatef((GLfloat)revolution, 0.0, 1.0, 0.0);
    glTranslatef(5.0, 0.0, 0.0);
    glColor3f(0.2, 1.0, 0.8);
    
    //地球自转
    glRotatef((GLfloat)rotation, 0.0, 1.0, 0.0);
    glutWireSphere(0.4, 15, 10);
    
    //月球转动轨迹
    glPushMatrix();
    glColor3f(0.0, 1.0, 1.0);
    glRotatef(90.0f, 1.0, 0.0, 0.0);
    glutSolidTorus(0.005, 1.5, 10, 64);
    glPopMatrix();
    
    //月球
    glPushMatrix();
    glRotatef((GLfloat)moon, 0.0, 1.0, 0.0);
    glTranslatef(1.5, 0.0, 0.0);
    glRotatef((GLfloat)moon, 0.0, 1.0, 0.0);
    glColor3f(0.5, 0.6, 0.5);
    glutWireSphere(0.25, 10, 8);
    glPopMatrix();
    glPopMatrix();
    
    //地球运动轨迹
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glRotatef(90.0f, 1.0, 0.0, 0.0);
    glutSolidTorus(0.005, 5.0, 10, 64);
    glPopMatrix();

    //双缓冲技术，交换缓冲区
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
    gluLookAt(-10.0, 10.0, 0.0, 0.0,0.0, 0.0, 0.0, -1.0,1.0);
}


void idle()
{
    moon = moon + 0.3;
    if (moon >= 360)
    {
        moon = 0;
    }
    rotation = rotation + 9;
    if (rotation >= 360)
    {
        rotation = 0;
    }
    revolution = revolution + 0.24;
    if (rotation >= 360)
    {
        revolution = 0;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    // 初始化GLUT库
    glutInit(&argc, argv);
    
    //设置初始显示模式
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(250, 250);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
    
}
//
//  main.cpp
//  op1
//
//  Created by 天天 龚 on 15/12/14.
//  Copyright © 2015年 天天 龚. All rights reserved.
//
//引用相关包


//<span style="font-family: Arial, sans-serif, Helvetica, Tahoma; line-height: 18px;">#include "stdafx.h"</span>
#include <stdio.h> 
#include <stdlib.h>
#include <GLUT/GLUT.h>

//行星序是水星、金星、地球、火星、木星、土星、天王星、和海王星
//adam,hesper,earth,mars,jupiter,saturn,uranus,neptune
//行星
GLfloat rot0 = 30.0;
GLfloat rot1 = 0.0;
GLfloat rot2 = 0.0;
GLfloat rot3 = 0.0;
GLfloat rot4 = 0.0;
GLfloat rot5 = 0.0;
GLfloat rot6 = 0.0;
GLfloat rot7 = 0.0;
GLfloat rot8 = 0.0;
//卫星
GLfloat rot9 = 0.0;
GLfloat rot10 = 0.0;
GLfloat rot11 = 0.0;

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClearDepth(1.0);
    glShadeModel(GL_FLAT);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glLoadIdentity();
    //gluLookAt(0, 10, 10, 0,0,0,0, 1,0);
    //glRotatef(45.0,0.0,0.0,1.0);
    glTranslatef(0.0,0.0,-20.0);
    glRotatef(90.0,1.0,0.0,0);
    glPushMatrix();
    //绘制太阳
    glColor3f(1.0,0.0,0.0);
    glutSolidSphere(2.0,32,32);
    //绘制地球
    glPushMatrix();
    glColor3f(0.0,0.0,1.0);
    // 绘制辅助轨道
    glRotatef(90,1.0,0,0.0);
    glutSolidTorus(0.02, 5.0, 10, 64);
    glRotatef(-90,1.0,0,0.0);
    // 设置地球公转速度
    glRotatef(rot0,0.0,1.0,0.0);
    // 设置地球半径
    glTranslatef(5.0,0.0,0.0);
    // 设置地球自转速度
    //glRotatef(rot1,0.0,1.0,0.0);
    // 绘制地球
     glutSolidSphere(0.4,32,32);
    // 绘制地球的卫星-月亮
    glColor3f(0.5,0.6,0.5);
    // 抵消地球自转影响
    //glRotatef(-rot1,0.0,1.0,0.0);
    // 绘制辅助轨道
    glRotatef(90,1.0,0,0.0);
    glRotatef(-90,1.0,0,0.0);
    // 设置月亮公转速度
    glRotatef(rot9,0.0,1.0,0.0);
    // 设置月亮公转半径
    glTranslatef(0.6,0.0,0.0);
    // 绘制月亮
    glutSolidSphere(0.1,10,8);
    glPopMatrix();
    
    glutSwapBuffers();
    glFlush();
}

void idle()
{
    rot0+=0.1;
    if(rot0>=360.0)
        rot0-=360.0;
    rot1+=0.416;
    if(rot1>=360.0)
        rot1-=360.0;
    rot2+=0.1631;
    if(rot2>=360.0)
        rot2-=360.0;
    rot3+=0.053;
    if(rot3>=360.0)
        rot3-=360.0;
    rot4+=0.0083;
    if(rot4>=360.0)
        rot4-=360.0;
    rot5+=0.0034;
    if(rot5>=360.0)
        rot5-=360.0;
    rot6+=0.00119;
    if(rot6>=360.0)
        rot6-=360.0;
    rot7+=0.00069;
    if(rot7>=360.0)
        rot7-=360.0;
    rot8+=0.0008;
    if(rot8>=360.0)
        rot8-=360.0;
    rot9+=1.0;
    if(rot9>=360.0)
        rot9-=360.0;
    rot10+=0.005;
    if(rot10>=360.0)
        rot10-=360.0;
    rot11+=0.01;
    if(rot11>=360.0)
        rot11-=360.0;
    
    glutPostRedisplay();
}

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLdouble)w/(GLdouble)h,1.0,100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,400);
    glutInitWindowPosition(500,500);
    glutCreateWindow("planet sim");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    
    return 0;
}
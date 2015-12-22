//
//  main.cpp
//  MyOpenGL
//
//  Created by Xin on 6/12/2015.
//  Copyright © 2015 Huang Xin. All rights reserved.
//

#include <iostream>
#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>
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

void drawSun() {
    glPushMatrix();  //压栈
    glColor3f(1, 0, 0);   //设置红色绘图
    glRotatef(sAngle, 0, 0, 1);
    glutWireSphere(1, 24, 20);   //绘制太阳
}

void drawEarth() {
    glColor3f(0, 0, 1);   //设置蓝色绘图
    glTranslatef(0, 2.5, 0); //将场景中的物体沿x轴正方向移动3个单位长
    glRotatef((GLfloat)mAngle, 0, 0, 1);  //沿y轴旋转
    glutWireSphere(0.3, 12, 10);   //绘制地球
}

void drawMoon() {
    glTranslatef(1, 0, 0); //将场景中的物体沿x轴正方向移动1个单位长
    glRotatef((GLfloat)dAngle, 0, 0, 1);  //沿y轴旋转
    glColor3f(1, 1, 1);   //设置白色绘图
    glutWireSphere(0.15, 10, 8);//绘制月球
}

void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);  //清空颜色缓冲区
    drawSun();
    drawEarth();
    drawMoon();
    glPopMatrix(); //出栈
    glutSwapBuffers();
    glFlush();   //刷新窗口以显示当前绘制图形
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);   //设置视口矩阵的原点坐标与宽高
    glMatrixMode(GL_PROJECTION);  //指定当前矩阵为投影矩阵
    glLoadIdentity();//重置当前矩阵为单位矩阵
    /*
     gluPerspective(fovy,aspect,zNear,zFar)
     GLdouble fovy, //角度
     GLdouble aspect,//视景体的宽高比
     GLdouble zNear,//沿z轴方向的两裁面之间的距离的近处
     GLdouble zFar //沿z轴方向的两裁面之间的距离的远处
     */
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 20);
    glMatrixMode(GL_MODELVIEW);//指定当前矩阵为模型矩阵
    glLoadIdentity();
    /*
     void gluLookAt(GLdouble eyex,GLdouble eyey,GLdouble eyez,
     GLdouble centerx,GLdouble centery,GLdouble centerz,
     GLdouble upx,GLdouble upy,GLdouble upz);
     第一组eyex, eyey,eyez 相机在世界坐标的位置
     第二组centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
     第三组upx,upy,upz 相机向上的方向在世界坐标中的方向
     */
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 0, 1);
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

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("太阳系-黄鑫-第一次作业");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, timeChange, 1);
    glutMainLoop(); //进人GLUT事件处理循环
    return 0;
}
#pragma clang diagnostic pop
//
//  main.cpp
//  YCOpenGLHomeWork01
//
//  Created by YC－MacBookPro on 15/12/16.
//  Copyright © 2015年 YC－MacBookPro. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <unistd.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>
using namespace std;

GLfloat spin = 0;
const GLfloat lightPosition[] = {10.0,10.0,10.0,0.0};
const GLfloat whiteLight[] = {0.8,0.8,0.8,1.0};
GLfloat matSpecular [] = {0.3,0.3,0.3,1.0};
GLfloat matShininess [] = {20.0};
GLfloat matEmission [] = {0.3,0.3,0.3,1.0};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();;
    glOrtho(-10.0,10.0,-10.0,10.0,-10.0,10.0);
    
    gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);//设置观察角度
    //绘制坐标系
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(10.0,0.0,0.0);//X轴
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,10.0,0.0);//Y轴
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,10.0);//Z轴
    glEnd();
    glFlush();
    
    //绘制太阳
    glMatrixMode(GL_MODELVIEW);
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glRotatef(spin,0.0,1.0,0.0);
    glMaterialfv(GL_FRONT,GL_SPECULAR,matSpecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,matShininess);
    glMaterialfv(GL_FRONT,GL_EMISSION,matEmission);
    glutSolidSphere(2.5,160,16);
    
    glPopMatrix();
    glFlush();
    
    
    //绘制地球
    GLfloat RADIUS = 6.0f;
    glMatrixMode(GL_MODELVIEW);
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glRotatef(spin, 0.0, 1.0,0.0);
    glTranslatef(RADIUS, 0, 0);
    glMaterialfv(GL_FRONT,GL_SPECULAR,matSpecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,matShininess);
    glMaterialfv(GL_FRONT,GL_EMISSION,matEmission);
    glutSolidSphere(1.2,160,16);
    
    glPopMatrix();
    
    
    //绘制月亮
    glMatrixMode(GL_MODELVIEW);
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glRotatef(spin, 0.0, 1.0, 0.0);
    GLfloat alpha = spin;
    if (spin > 180)
        alpha = 360 - spin;
    GLfloat t = sqrt(RADIUS*RADIUS + RADIUS*RADIUS*0.25 - RADIUS*RADIUS*cos(alpha));
    glTranslatef(t, 0, 0);
    glMaterialfv(GL_FRONT,GL_SPECULAR,matSpecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,matShininess);
    glMaterialfv(GL_FRONT,GL_EMISSION,matEmission);
    glutSolidSphere(1.0,160,16);
    
    glPopMatrix();
    
    spin = spin + 1;
    if (spin>=360)
    {
        spin = 0;
    }
    //sleep(500);
    glFlush();
}

void MyKeyboard(unsigned char key,int x,int y)//键盘事件
{
    switch(key)
    {
        case 'a':
        {
            while (true)
            {
                spin = spin + 10;
                display();
                //Sleep(500);
            }
            break;
        }
    }
}

void myReshape(int w, int h)//针对窗体大小改变而写的函数
{
    if (!h)
        return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0*(GLfloat)w/(GLfloat)h,1.0, 30.0);//视角
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);//平移
}

void SetMatrial()//设置光源和材质，以材质为主
{
    /*设置合适的光源和材质，设置材质的各种光的颜色成分反射比率*/
    GLfloat mat_ambient[]={0.8,0.8,0.8,1.0};
    GLfloat mat_diffuse[]={0.8,0.0,0.8,1.0};/* 紫色 */
    GLfloat mat_specular[] = { 1.0, 0.0, 1.0, 1.0 };/* 亮紫色 */
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//材质光源位置
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glLightfv(GL_LIGHT0, GL_POSITION,light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void SetLightSource()//设置光源和材质，以光源为主
{
    //设置合适的光源和材质
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };//设置材质光
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_ambient[] = { 1.0, 0.0, 1.0, 1.0 };//设置环境光，这三种光的颜色要是一样的，现在是紫色
    GLfloat light_diffuse[] = { 1.0, 0.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 0.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; //最后一个参数为0表示该光源是directional的
    //GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 }; //最后一个参数非0表示该光源是positional的
    //GLfloat Light_Model_Ambient[] = { 0.0 , 0.0 , 0.0 , 1.0 }; //全局环境光设为黑色
    GLfloat Light_Model_Ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 }; //默认的全局环境光
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT , Light_Model_Ambient ); //设置全局环境光的方法
    
    glClearColor (0.0, 0.0, 0.0, 0.0);//清除颜色
    glShadeModel (GL_SMOOTH);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); //把全局环境光设置为黑色,然后注释掉本句可以发现"黑屏"
}

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glEnable(GL_DEPTH_TEST);//打开深度测试
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LESS);
    //SetLightSource();
    SetMatrial();
    glShadeModel (GL_FLAT);
}

void draw() {
    
    //设置清屏色
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //设置颜色，红色
    glColor3f(1.0f, 0.0f, 0.0f);
    //设置绘图时的坐标系统
    glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
    //开始渲染
    glBegin(GL_POLYGON);
    //设置多边形的4个顶点
    glVertex3f(0.25f, 0.25f, 0.0f);
    glVertex3f(0.75f, 0.25f, 0.0f);
    glVertex3f(0.75f, 0.75f, 0.0f);
    glVertex3f(0.25f, 0.75f, 0.0f);
    //结束渲染
    glEnd();
    
    
//    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();;
//    glOrtho(-10.0,10.0,-10.0,10.0,-10.0,10.0);
//    
//    gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);//设置观察角度
//    //绘制坐标系
//    glBegin(GL_LINES);
//    glVertex3f(0.0,0.0,0.0);
//    glVertex3f(10.0,0.0,0.0);//X轴
//    glVertex3f(0.0,0.0,0.0);
//    glVertex3f(0.0,10.0,0.0);//Y轴
//    glVertex3f(0.0,0.0,0.0);
//    glVertex3f(0.0,0.0,10.0);//Z轴
//    glEnd();
//    glFlush();
//    //绘制太阳
//    glMatrixMode(GL_MODELVIEW);
//    glColor3f(0.0f, 1.0f, 0.0f);
//    glPushMatrix();
//    glRotatef(spin,0.0,1.0,0.0);
//    glMaterialfv(GL_FRONT,GL_SPECULAR,matSpecular);
//    glMaterialfv(GL_FRONT,GL_SHININESS,matShininess);
//    glMaterialfv(GL_FRONT,GL_EMISSION,matEmission);
//    glutSolidSphere(2.5,160,16);
//    glPopMatrix();
    
    //强制刷新缓冲区，保证绘制命令被执行
    glFlush();
    
}

int main(int argc, const char * argv[]) {
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition (300,300);
    glutCreateWindow("绘制太阳系");
    
    myInit();
//    glutDisplayFunc(draw);
    glutDisplayFunc(display);
    glutIdleFunc (display);
    glutReshapeFunc(myReshape);
//    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    
    return 0;
}

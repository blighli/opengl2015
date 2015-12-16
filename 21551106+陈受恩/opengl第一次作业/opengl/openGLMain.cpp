//
//  openGLMain.cpp
//  opengl
//
//  Created by 陈受恩 on 15/12/16.
//  Copyright © 2015年 chenshouen. All rights reserved.
//
//
#include <GLUT/GLUT.h>
#include <OpenGL/gl3.h>

void display()
{
    //开启更新深度缓冲区
    glEnable(GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    //去除痕迹
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    //随后的矩阵操作－投影
    glMatrixMode( GL_PROJECTION );
    //重置投影矩阵，坐标复位
    glLoadIdentity();
    //glutGet(GLenum state)检索指定的GLUT状态
    //指定透视投影的观察空间(眼角度＋纵横比＋近线距离＋远线距离)
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective(60.0,(float)w/(float)h,0.1,100.0);
    
    //随后的矩阵操作－描绘模型的适应
    glMatrixMode( GL_MODELVIEW );
    //重置投影矩阵，坐标复位
    glLoadIdentity();
    
    //平移（x，y，z）
    glTranslatef( 0, 0,-30 );
    //旋转（角度，x，y，z）
    glRotatef(-80, 1, 0, 0);
    
    //返回两次调用glutGet(GLUT_ELAPSED_TIME)的时间间隔,单位为毫秒
    static int lastMs = glutGet(GLUT_ELAPSED_TIME );
    int curMs = glutGet( GLUT_ELAPSED_TIME );
    double dt = ( curMs - lastMs ) / 100.0;
    lastMs = curMs;
    //设置地球、月球旋转的速度，保证月球速度是地球的27倍
    static float earth = 0;
    static float moon = 0;
    earth += 2 * dt;
    moon += 2*27 * dt;
    
    //将当前矩阵压入栈顶
    glPushMatrix();
    {
        //绘制太阳
        glColor3ub( 255, 0, 0 );//设置颜色
        glutWireSphere(10,60,60);//三个参数分别是半径，经线和纬线的数量
   
        //绘制地球
        glPushMatrix();
        {
            glRotatef( earth, 0, 0, 2);//旋转
            glTranslatef( 15, 0, 0 );//平移
            glColor3ub( 0 , 0, 255 );
            glutWireSphere(3, 18,18);
            
            //绘制月球
            glPushMatrix();
            {
                glRotatef( moon, 0, 0, 1);
                glTranslatef( 5, 0, 0 );
                glColor3ub( 255, 255, 0 );
                glutWireSphere(1, 8 , 8);            }
            
             glPopMatrix();//出栈
            }
           glPopMatrix();
        }
    glPopMatrix();
    
    //双缓冲调换位置
    glutSwapBuffers();
}

void timer(int miao)
{
    //标记当前窗口需要重绘，便于回调glutDisplayFunc(&display );
    glutPostRedisplay();
    //计时器
    glutTimerFunc(0, timer, 0);
}


int main( int argc, char **argv )
{
    //初始化GLUT函数库
    glutInit(&argc,argv );//初始化
    
    //创建窗口显示模式
    glutInitDisplayMode( GLUT_RGB|GLUT_DOUBLE);
    //glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    
    //设定窗口大小和位置，创建窗口
    glutInitWindowSize( 800 , 600 );
    glutInitWindowPosition(100, 100);
    glutCreateWindow( "OPENGL第一次作业 BY 陈受恩" );
    
    //处理渲染函数
    glutDisplayFunc(&display );
    
    //计时器,立即开始
    glutTimerFunc(0, timer, 0);
    
    //事件处理，运行程序
    glutMainLoop();
    return 0;
    
}
//
//  main.cpp
//  OpenGLHomeWork01
//
//  Created by 黄炳杰 on 12/5/15.
//  Copyright © 2015 Bing. All rights reserved.
//
#include <GLUT/GLUT.h>

void display()
{
    static int lastMs = glutGet( GLUT_ELAPSED_TIME );
    int curMs = glutGet( GLUT_ELAPSED_TIME );
    double dt = ( curMs - lastMs ) / 100.0;
    lastMs = curMs;                                 //返回两次调用GLUT_ELAPSED_TIME的间隔
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//清空缓存
    
    glMatrixMode( GL_PROJECTION );                  //对投影矩阵应用随后的矩阵操作
    glLoadIdentity();                               //将矩阵置为单位矩阵
    double w = glutGet( GLUT_WINDOW_WIDTH );//获取屏幕长度宽度
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    double ar = w / h;//得到长宽比例
    gluPerspective( 60, w / h, 0.1, 100 );//设定视角
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0, 0, -24 );//三个参数分别表示分别向三个轴用地懂得距离
    glRotatef(-70, 1, 0, 0);//表示将当前图形沿方向向量(1,0,0)顺时针旋转70度
    
    glEnable(GL_DEPTH_TEST);//启用深度测试
    glDepthFunc (GL_LESS);//深度比较函数，如果比参考值小则通过
    static float earth = 0;//设置地球旋转的速度
    static float moon = 0;//设置月球旋转的速度
    
    earth += 2 * dt;//应该保证月球速度是地球的12倍
    moon += 24 * dt;
    
    glPushMatrix();//将当前矩阵压入栈顶
    {
        //绘制太阳
        glColor3ub( 255, 100, 0 );//设置颜色
        glutWireSphere( 4, 18, 18 );//绘制线条构成的球体，三个参数分别是半径，经线和纬线的数量
        
        glPushMatrix();//讲当前的矩阵压入栈顶
        {
            glRotatef( earth, 0, 0, 2 );//旋转
            glTranslatef( 10, 0, 0 );//平移
            
            glColor3ub( 0 , 100, 255 );//颜色
            glutWireSphere( 1.5, 12, 12 );
            
            glPushMatrix();
            {
                glRotatef( moon, 0, 0, 1 );
                glTranslatef( 3, 0, 0 );
                
                glColor3ub( 128, 128, 128 );//灰色实心的
                glutSolidSphere(0.5, 12 , 12);//绘制实心球的函数，也是经线和纬线
            }
            glPopMatrix();//出栈
        }
        glPopMatrix();
    }
    glPopMatrix();
    
    glutSwapBuffers();
}

void timer(int extra)
{
    glutPostRedisplay();//标记当前窗口需要重新绘制
    glutTimerFunc(10, timer, 0);//glutTimerFunc(毫秒数, 回调函数指针, 区别值);计时器
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );//初始化
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 800 , 800 );
    glutCreateWindow( "21551036黄炳杰" );
    glutDisplayFunc(&display );
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
    
}
//
//  main.cpp
//  OpenGL_1
//
//  Created by 常惠源 on 12/8/15.
//  Copyright © 2015 常惠源. All rights reserved.
//


#include <GLUT/GLUT.h>

void display()
{
    static int lastMs = glutGet( GLUT_ELAPSED_TIME );
    int curMs = glutGet( GLUT_ELAPSED_TIME );
    double dt = ( curMs - lastMs ) / 100.0;
    lastMs = curMs;
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//清空缓存区
    
    glMatrixMode( GL_PROJECTION );//投影
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    double ar = w / h;
    gluPerspective( 75, w / h, 0.1, 100 );
    
    glMatrixMode( GL_MODELVIEW );//视景
    glLoadIdentity();
    glTranslatef( 0, 0, -24 );
    glRotatef(-70, 1, 0, 0);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    static float earth = 0;
    static float moon = 0;
    
    //单位时间内，旋转不同的角度
    earth += 2 * dt;
    moon += 36 * dt;
    
    glPushMatrix();
    {
        //太阳
        //太阳的颜色
        glColor3ub( 255, 69, 0 );
        glutWireSphere( 6, 200 , 200 );//半径以及经纬
        
        glPushMatrix();
        {
            //地球
            glRotatef( earth, 0, 0, 1 );//地球旋每次绘制转的角度，沿Z轴旋转
            glTranslatef( 10, 0, 0 );
            
            glColor3ub( 0, 0, 155 );
            glutWireSphere( 1.5, 18, 18 );
            
            glPushMatrix();//压栈
            {
                //月亮
                glRotatef( moon, 0, 0, 1 );
                glTranslatef( 2, 0, 0 );
                
                glColor3ub( 130, 130, 130 );
                glutWireSphere( 0.5, 18, 18 );
            }
            glPopMatrix();//出栈
        }
        glPopMatrix();
    }
    glPopMatrix();
    
    glutSwapBuffers();//实现双缓冲
}

void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);//定时器，每10毫秒刷新重绘
}

int main( int argc, char **argv )
{
    //初始化
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 640, 640 );
    
    glutCreateWindow( "21551058_常惠源" );
    glutDisplayFunc( display );
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();//循环绘图
    return 0;
}
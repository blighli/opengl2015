//
//  main.cpp
//  Work1
//
//  Created by YXQ on 15/12/8.
//  Copyright © 2015年 YXQ. All rights reserved.
//

//引用相关的包
#include <GLUT/GLUT.h>
#define N 2

static int year = 0, month = 0, day = 0;

void display(void)
{
    //清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    //重置颜色
    glColor3f(1, 0, 0);
    //压栈
    glPushMatrix();
    
    //绘制太阳
    glutWireSphere(1, 20, 16);
    //沿y轴旋转
    glRotatef((GLfloat) year, 0, 1, 0);
    //将场景中的物体沿x轴正方向移动2个单位长
    glTranslatef(2, 0, 0);
    
    //沿y轴旋转
    glRotatef((GLfloat) day, 0, 1, 0);
    //绘制地球
    glutWireSphere(0.2, 10, 8);
    //将场景中的物体沿x轴正方向移动2个单位长
    glTranslatef(2, 0, 0);
    
    //沿y轴旋转
    glRotatef((GLfloat) month, 0, 1, 0);
    //绘制月球
    glutWireSphere(0.1, 8, 5);
    
    //出栈
    glPopMatrix();
    glutSwapBuffers();
    //刷新窗口以显示当前绘制图形
    glFlush();
}

void init(void)
{
    glClearColor(0, 0, 0, 0);
    //选择平面明暗模式或光滑明暗模式
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
    //设置机口
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    //指定哪一个矩阵是当前矩阵
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //创建透视投影矩阵(fovy, aspect, zNear, zFar)
    gluPerspective(60, (GLfloat)w/(GLfloat)h, 1.0, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glFrustum(-1, 1, -1, 1, 1.5, 20.0);
    //用透视矩阵乘以当前矩阵(left, right, bottom, top, near, far)
    gluLookAt(0, 5, 5, 0, 0, 0, 0, 1, 0);
}

void onTimer(int value)
{
    year = (year + N) % 360;
    month = (month + N) % 360;
    day = (day + N) % 360;
    glutPostRedisplay();
    glutTimerFunc(10, onTimer, 1);
}

int main(int argc, char * argv[]) {
    //固定格式
    glutInit(&argc, argv);
    //缓存模式
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    //显示框大小
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("太阳系");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100, onTimer, 1);
    //进入GLUT事件处理循环
    glutMainLoop();
    return 0;
}

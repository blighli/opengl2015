//
//  main.cpp
//  Work01
//
//  Created by 黄梦妃 on 15/12/8.
//  Copyright (c) 2015年 黄梦妃. All rights reserved.
//

#include <GLUT/GLUT.h>

static int day=0;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  //清空颜色缓冲区
    glColor3f(1,0,0);   //重置颜色
    glPushMatrix();  //压栈
    
    glutWireSphere(1,20,16);   //绘制太阳
    glRotatef((GLfloat)day,0,1,0);  //沿y轴旋转
    glTranslatef(2,0,0); //将场景中的物体沿x轴正方向移动2个单位长
    
    glRotatef((GLfloat)day*12,0,1,0);  //沿y轴旋转
    
    glColor3f(0,0,1);   //重置颜色
    glutWireSphere(0.2,10,8);   //绘制行星
    glTranslatef(0.5,0,0); //将场景中的物体沿x轴正方向移动0.5个单位长
    
    glColor3f(0xff,0xff,0);   //重置颜色
    glutWireSphere(0.1,5,4);   //绘制行星
    glPopMatrix(); //出栈
    glutSwapBuffers();
    glFlush();   //刷新窗口以显示当前绘制图形
    
}

void timer(int p)
{
    day++;
    if(day>360)day=0;
    glutTimerFunc(50,timer,0);
    glutPostRedisplay();
}


void init(void)
{
    glClearColor(0,0,0,0);
    glShadeModel(GL_FLAT); //选择平面明暗模式或光滑明暗模式
}

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);   //设置机口
    glMatrixMode(GL_PROJECTION);  //指定哪一个矩阵是当前矩阵
    glLoadIdentity();
    gluPerspective(60,(GLfloat)w/(GLfloat)h,1.0,20);   //创建透视投影矩阵(fovy,aspect,zNear,zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,5,5,0,0,0,0,1,0);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv); //固定格式
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
    glutInitWindowSize(400, 400);    //显示框的大小
    glutInitWindowPosition(400,400); //确定显示框左上角的位置
    glutCreateWindow("earth,sun,moon");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(50,timer,0);
    glutMainLoop(); //进人GLUT事件处理循环
    return 0;
}
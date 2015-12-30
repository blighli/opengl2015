//
//  main.cpp
//  plh-homework1
//
//  Created by peilinghui on 15/12/8.
//  Copyright © 2015年 peilinghui. All rights reserved.
//

//太阳、地球和月亮
// 假设每个月都是 30 天
// 一年 12 个月,共是 360 天
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/GLUT.h>
int day = 200; // day 的变化:从 0 到 359 void myDisplay(void)
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, 1, 1, 400000000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);
    
    // 绘制红色的“太阳”
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(69600000, 20, 20);
    
    // 绘制蓝色的“地球”
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f); glTranslatef(150000000, 0.0f, 0.0f); glutSolidSphere(15945000, 20, 20);
    
    // 绘制黄色的“月亮”
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f); glTranslatef(38000000, 0.0f, 0.0f);
    glutSolidSphere(4345000, 20, 20);
    
    glFlush();
    glutSwapBuffers();
}
void myIdle(void)
{
    /* 新的函数,在空闲时调用,作用是把日期往后移动一天并重新绘制,达到动画效果 */ ++day;
    if( day >= 360 )
        day = 0;
    display();
}
int main(int argc, char *argv[]) {
// 新加入了这句
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // 修改了参数为 GLUT_DOUBLE glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("太阳,地球和月亮");
    glutDisplayFunc(&display);
    glutIdleFunc(&myIdle);
    glutMainLoop();
    return 0;
}

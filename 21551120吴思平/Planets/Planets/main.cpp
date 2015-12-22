//
//  main.cpp
//  Planets
//
//  Created by Anglet on 15/12/8.
//  Copyright © 2015年 Anglet. All rights reserved.
//

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cmath>

int day=0;

void ChangeSize(int width,int height)
{
    glViewport(0, 0, width, height);
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    glRotatef(90, 1, 0, 0);//设置旋转
    
    //绘制太阳
    glColor3f(1, 0, 0);//设置颜色
    glRotatef((GLfloat)day, 0, 0, 1);//设置旋转
    glutWireSphere(0.3, 30, 30);//设置球体半径和分割
    
    //绘制地球
    glTranslated(0.5, 0, 0);
    glColor3f(0, 0, 1);
    glRotatef((GLfloat)day*6, 0, 0, 1);
    glutWireSphere(0.1, 20, 20);
    
    //绘制月球
    glTranslated(0.18, 0, 0);
    glColor3f(1, 1, 0);
    glutWireSphere(0.05, 15, 15);
    
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void update(int id)
{
    day++;
    if (day>365)
    {
        day=0;
    }
    glutTimerFunc(30, update, 0);
    glutPostRedisplay();
}

int main(int argc,char *argv[])

{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("太阳*地球*月亮");
    
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_FLAT);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(30, update, 1);
    glutMainLoop();
    
    return 0;
}

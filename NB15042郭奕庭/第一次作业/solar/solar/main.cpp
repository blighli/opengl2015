//
//  main.cpp
//  solar
//
//  Created by greeting on 12/8/15.
//  Copyright © 2015 greeting. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>

static int day = 360;


void draw()
{
    //sun
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidSphere(49600000, 20, 20);
    //earth
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(150000000, 0.0f, 0.0f);
    glutSolidSphere(15945000, 20, 20);
    //moon
    glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
    glTranslatef(38000000, 0.0f, 0.0f);
    glutSolidSphere(4345000, 20, 20);
}

void displayFunc(void)
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, 1, 1, 400000000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, -210000000, 210000000, 0, 0, 0, 0, 0, 1);
    draw();
    glFlush();
    glutSwapBuffers();
}

void idleFunc(void)
{
    day = day%361;
    ++day;
    displayFunc();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("太阳地球和月球");
    glutDisplayFunc(&displayFunc);
    glutIdleFunc(&idleFunc);
    glutMainLoop();
    return 0;
}

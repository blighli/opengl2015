//
//  main.m
//  OpenGL-HomeWork01
//
//  Created by alezai on 15/12/7.
//  Copyright © 2015年 alezai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLUT/GLUT.h>

static float sunDay = 0;
static float year = 0, month = 0, day = 0, moonDay = 0;

void prepareOpenGL(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    //sun
    glPushMatrix();
    glColor3f(1.f, 0, 0);
    glRotatef((GLfloat)sunDay, 0, 0, 1);
    glutWireSphere(2, 24, 20);
    glPopMatrix();
    
    //earth
    glPushMatrix();
    glRotatef((GLfloat)year, 0, 1, 0);
    glTranslatef(6, 0, 0);
    glColor3f(0, 0, 1);
    glRotatef((GLfloat)day, 0, 1, 0);
    glutWireSphere(0.8, 12, 10);
    
    //moon
    glPushMatrix();
    glRotatef((GLfloat)month, 0, 1, 0);
    glTranslatef(2, 0, 0);
    glRotatef((GLfloat)moonDay, 0, 1, 0);
    glColor3f(0.5, 0.6, 0.5);
    glutWireSphere(0.2, 10, 8);
    glPopMatrix();
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0);
}

void idle(){
    sunDay = sunDay + 0.1;
    if (sunDay >= 360) {
        sunDay = 0;
    }
    moonDay = moonDay + 1.2;
    if (moonDay >= 360){
        moonDay = 0;
    }
    month = month + 1.2;
    if (month >= 360){
        month = 0;
    }
    day = day + 0.6;
    if (day >= 360){
        day = 0;
    }
    year = year + 0.3;
    if (day >= 360){
        year = 0;
    }
    
    glutPostRedisplay();
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        glutInit(&argc, (char **)argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(200, 100);
        glutCreateWindow(argv[0]);
        
        prepareOpenGL();
        
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutIdleFunc(idle);
        glutMainLoop();
    }
    return 0;
}

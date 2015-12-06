//
//  main.cpp
//  Atlas_OpenGL_DEMO_solar
//
//  Created by Atlas on 15/12/6.
//  Copyright © 2015年 Atlas. All rights reserved.
//

#include <GLUT/GLUT.h>

static double year_of_sun = 0;
static double year_of_mercury = 0, day_of_mercury = 0;
static double year_of_venus = 0, day_of_venus = 0;
static double year_of_earth = 0, day_of_earth = 0;
static double year_of_saturn = 0, day_of_saturn = 0;
static double month_of_moon = 0, day_of_moon = 0;



void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    {
        // paint sun
        glPushMatrix();
        glColor3f(1, 0, 0);
        glRotatef(-year_of_sun, 0, 0, 1);
        glutWireSphere(1, 20, 20);
        glPopMatrix();
    }
    {
        //paint the track of Mercury
        glPushMatrix();
        glColor3f(1, 1, 1);
        glRotatef(90, 0, 0, 1);
        glutSolidTorus(0.03, 3, 10, 50);
        glPopMatrix();
        //paint the Mercury
        glPushMatrix();
        glColor3f(0.8, 0.7, 0);
        glRotatef(year_of_mercury, 0, 0, 1);
        glTranslatef(3, 0, 0);
        glRotatef(-day_of_mercury, 0, 0, 1);
        glutWireSphere(0.4, 14, 10);
        glPopMatrix();
    }
    {
        //paint the track of Venu
        glPushMatrix();
        glColor3f(1, 1, 1);
        glRotatef(90, 0, 0, 1);
        glutSolidTorus(0.03, 6, 20, 60);
        glPopMatrix();
        
        //paint the Venus
        glPushMatrix();
        glColor3f(0.9, 0.6, 0);
        glRotatef(year_of_venus, 0, 0, 1);
        glTranslatef(6, 0, 0);
        glRotatef(day_of_venus, 0, 0, 1);
        glutWireSphere(0.6, 14, 10);
        glPopMatrix();
    }
    {
        //paint the track of Earth
        glPushMatrix();
        glColor3f(1, 1, 1);
        glRotatef(90, 0, 0, 1);
        glutSolidTorus(0.03, 10, 120, 160);
        glPopMatrix();
        
        //paint the Earth
        glPushMatrix();
        glColor3f(0, 0.2, 0.6);
        glRotatef(year_of_earth, 0, 0, 1);
        glTranslatef(10, 0, 0);
        glRotatef(day_of_earth, 0, 0, 1);
        glutWireSphere(0.6, 14, 10);
        
        {
            //paint the track of moon
            glPushMatrix();
            glColor3f(1, 1, 1);
            glRotatef(90, 0, 0, 1);
            glutSolidTorus(0.03, 2, 20, 60);
            glPopMatrix();
            
            //paint the moon
            glPushMatrix();
            glColor3f(0.9, 0.6, 0);
            glRotatef(month_of_moon, 0, 0, 1);
            glTranslatef(2, 0, 0);
            glRotatef(-day_of_moon, 0, 0, 1);
            glutWireSphere(0.4, 10, 6);
            glPopMatrix();
        }
        glPopMatrix();
    }
    {
        //paint the track of Venu
        glPushMatrix();
        glColor3f(1, 1, 1);
        glRotatef(90, 0, 0, 1);
        glutSolidTorus(0.03, 16, 20, 60);
        glPopMatrix();
        
        //paint the Venus
        glPushMatrix();
        glColor3f(0.9, 0.5, 0.4);
        glRotatef(year_of_saturn, 0, 0, 1);
        glTranslatef(16, 0, 0);
        glRotatef(day_of_saturn, 0, 0, 1);
        glutWireSphere(0.6, 14, 10);
        
        {
            //paint the track of moon
            glPushMatrix();
            glColor3f(1, 1, 1);
            glRotatef(90, 0, 0, 1);
            glutSolidTorus(0.5, 2, 20, 60);
            glPopMatrix();
        }
        
        glPopMatrix();
    }
    glutSwapBuffers();
    
}

void MyReshaped(int w,int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1, 50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 35, 0, 0, 0, 0, 1, 0);
}

void MyIdle(){
    year_of_sun += 0.9;
    if (year_of_sun >=360) {
        year_of_sun = 0;
    }
    
    month_of_moon += 1;
    if (month_of_moon >= 360) {
        month_of_moon =0;
    }
    
    year_of_mercury += 0.5;
    if (year_of_mercury  >= 360) {
        year_of_mercury = 0;
    }
    
    year_of_venus += 0.7;
    if (year_of_venus >=360) {
        year_of_venus = 0;
    }
    
    year_of_earth += 0.4;
    if (year_of_earth >= 360) {
        year_of_earth = 0;
    }
    
    year_of_saturn += 0.6;
    if (year_of_saturn >= 360) {
        year_of_saturn = 0;
    }
    
    
    day_of_mercury += 0.5;
    if (day_of_mercury  >= 360) {
        day_of_mercury = 0;
    }
    
    day_of_venus += 0.7;
    if (day_of_venus >=360) {
        day_of_venus = 0;
    }
    
    day_of_earth += 0.4;
    if (day_of_earth >= 360) {
        day_of_earth = 0;
    }
    
    day_of_saturn += 0.4;
    if (day_of_saturn >= 360) {
        day_of_saturn = 0;
    }
    
    day_of_moon += 3.8;
    if (day_of_moon >= 360) {
        day_of_moon = 0;
    }
    
    glutPostRedisplay();

}

int main(int argc, char** argv){
    // insert code here...
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("我的第一个 opengl 展示");
    glClearColor(0, 0, 0, 0.8);
    glShadeModel(GL_FLAT);
   
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(MyReshaped);
    glutIdleFunc(MyIdle);
    
    glutMainLoop();
    
    return 0;
}







//
//  main.cpp
//  OpenGLHomeWork1
//
//  Created by 张焕 on 12/6/15.
//  Copyright © 2015 张焕. All rights reserved.
//


#include <GLUT/GLUT.h>

void display()
{
    static int lastMs = glutGet( GLUT_ELAPSED_TIME );
    int curMs = glutGet( GLUT_ELAPSED_TIME );
    double dt = ( curMs - lastMs ) / 100.0;
    lastMs = curMs;
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    double ar = w / h;
    gluPerspective( 60, w / h, 0.1, 100 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0, 0, -24 );
    glRotatef(-70, 1, 0, 0);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    static float earth = 0;
    static float moon = 0;
    
    earth += 2 * dt;
    moon += 36 * dt;
    
    glPushMatrix();
    {
        glColor3ub( 255, 255, 0 );
        glutWireSphere( 4, 18, 18 );
        
        glPushMatrix();
        {
            glRotatef( earth, 0, 0, 1 );
            glTranslatef( 10, 0, 0 );
            
            glColor3ub( 0, 255, 255 );
            glutWireSphere( 1.5, 18, 18 );
            
            glPushMatrix();
            {
                glRotatef( moon, 0, 0, 1 );
                glTranslatef( 3, 0, 0 );
                
                glColor3ub( 128, 128, 128 );
                glutWireSphere( 0.5, 18, 18 );
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
    
    glutSwapBuffers();
}

void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow( "21551051张焕" );
    glutDisplayFunc( display );
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
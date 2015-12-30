#include <GLUT/GLUT.h>


static double sunAngle = 0;
static int earthDay = 0;
static int marsDay = 0;

void display()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0f, 1.0f, 1.0f, 4.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, -1.5f, 1.5f, 0, -0.5f, 0, 0, 0, 1);
    
    
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glRotatef(sunAngle, 0.0f, 0.0f, -1.0f);
    glutWireSphere(0.5, 20, 20);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidTorus(0.005, 1.5f, 10, 64);
    glColor3f(0.5f, 0.0f, 0.0f);
    glutSolidTorus(0.005, 1.8f, 10, 64);
    glPopMatrix();
   
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(earthDay / 365.0 / 4.0 * 360.0f, 0, 0, -1.0f);
    glTranslated(1.5f, 0.0f, 0.0f);
    glutWireSphere(0.07, 20, 20);
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidTorus(0.005, 0.2f, 10, 64);

    
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef(earthDay / 360.0 * 360.0f, 0, 0, -1.0f);
    glTranslated(0.2f, 0.0f, 0.0f);
    glutWireSphere(0.02, 20, 20);
    glPopMatrix();
    
    glColor3f(0.5f, 0.0f, 0.0f);
    glRotatef(marsDay / 686.0 / 4.0 * 360.0f, 0, 0, -1.0f);
    glTranslated(1.8f, 0.0f, 0.0f);
    glutWireSphere(0.07, 20, 20);
    
    
    
    
    glFlush();
    glutSwapBuffers();
}

void refresh()
{
    sunAngle += 0.2;
    earthDay ++;
    earthDay = earthDay % (365 * 4);
    marsDay ++;
    marsDay = marsDay % (686 * 4);
    display();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow(argv[0]); // 改了窗口标题
    glutDisplayFunc(display);
    glutIdleFunc(refresh);
    glutMainLoop();
    return 0;
}
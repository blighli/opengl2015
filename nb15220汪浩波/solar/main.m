#include <GLUT/GLUT.h>  
#define N 2
static int year = 0;
static int day = 0;
static int month = 0;
void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(3,6,3);
    glPushMatrix();
    glutWireSphere(1,50,16);   
    glRotatef((GLfloat)year,0,1,0);
    
    glTranslatef(2,0,0);
    glRotatef((GLfloat)day,0,1,0);
    glutWireSphere(0.2,10,8);
    
    glTranslatef(0.3,0,0);
    glRotatef(0,2,1,0);
    glutWireSphere(0.05, 10, 8);
    
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
    
}


void init(void)
{
    glClearColor(0,0,0,0);
    glShadeModel(GL_FLAT);
}

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(GLfloat)w/(GLfloat)h,1.0,20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,5,5,0,0,0,0,1,0);
}
void onTimer(int value)
{
    year = (year + N) % 360;
    month = (month + N) % 360;
    day = (day + N) % 3600;
    glutPostRedisplay();
    glutTimerFunc(10,onTimer, 1);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(600,600);
    glutCreateWindow("Solar System");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100,onTimer, 1);
    glutMainLoop();
    return 0;
}

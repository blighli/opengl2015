


#include <GLUT/GLUT.h>  //引用相关包
#define N 2
static int year = 0;
static int day = 0;
static int month = 0;
void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(65/100,105/100,170/100);
    glPushMatrix();
    glutWireSphere(1,50,80);
    glRotatef((GLfloat)year,1,0,0);
    glTranslatef(0,2,0);
    //    glRotatef((GLfloat)day,0,1,0);
    glutWireSphere(0.2,10,8);
    
    glTranslatef(0,0.3,0);
    glRotatef(0,0,1,0);
    glutWireSphere(0.05, 10, 8);
    
    glPopMatrix();
    glutSwapBuffers();
    glFlush();       
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
    //    glFrustum(-1,1,-1,1,1.5,20.0);  //用透视矩阵乘以当前矩阵(left,Right,bottom,top,near,far);
    
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
    glutInit(&argc, argv); //固定格式
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
    glutInitWindowSize(800, 800);    //显示框的大小
    glutInitWindowPosition(600,600); //确定显示框左上角的位置
    glutCreateWindow("Solar System");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100,onTimer, 1);
    
    glutMainLoop(); //进人GLUT事件处理循环
    return 0;
}
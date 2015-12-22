#include <GLUT/GLUT.h>
#include <cmath>
static int year = 0, month = 0, day = 0;
static float self_rot = 0;

void changeAngle(int id)
{
    year = (year + 2) % 360;
    month = (month + 2) % 360;
    day = (day + 2) % 360;
    self_rot = self_rot + 0.5;
    if (self_rot >= 360)
        self_rot = 0;
    glutPostRedisplay();
    glutTimerFunc(33, changeAngle, 1);//递归调用以改变角度
}

void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);  //清空颜色缓冲区
    glPushMatrix();  //压栈
    
    glColor3f(1, 0, 0);   //设置红色绘图
    glRotatef(self_rot, 0, 1, 0);
    glutWireSphere(1, 20, 16);   //绘制太阳
    
    glColor3f(0, 1, 0);
    glRotatef((GLfloat)year, 0, 1, 0);  //沿y轴旋转
    glTranslatef(3, 0, 0); //将场景中的物体沿x轴正方向移动3个单位长
    glutWireSphere(0.3, 10, 8);   //绘制地球
    
    float angle = 0;
    int splitNum = 100;//想用100条直接来模拟圆
    float step = 2 * 3.14 / splitNum;//每次增加的角度
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    for (angle = 0; angle < 2 * 3.14; angle += step)
        glVertex3f(sin(angle), 0.0, cos(angle));
    glEnd();
    glRotatef((GLfloat)month, 0, 1, 0);
    
    glColor3f(0, 0, 1);
    glTranslatef(1, 0, 0); //将场景中的物体沿x轴正方向移动1个单位长
    glRotatef((GLfloat)day, 0, 1, 0);  //沿y轴旋转
    glutWireSphere(0.15, 10, 8);//绘制月球
    
    
    glPopMatrix(); //出栈
    glFlush();   //刷新窗口以显示当前绘制图形
}


void init(void)
{
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_FLAT); //选择平面明暗模式或光滑明暗模式
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);   //设置机口
    glMatrixMode(GL_PROJECTION);  //指定哪一个矩阵是当前矩阵
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 20);   //创建透视投影矩阵(fovy,aspect,zNear,zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0, 5, 5, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char *argv[])
{
    //配置环境
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);   
    glutInitWindowSize(960, 640);
    glutInitWindowPosition(0, 0); //左上角
    glutCreateWindow("太阳系");
    
    init();
    glutDisplayFunc(display);//绘制
    glutReshapeFunc(reshape);//配置环境
    glutTimerFunc(33, changeAngle, 1);
    
    glutMainLoop(); //进人GLUT事件处理循环
}

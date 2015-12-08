#include <GLUT/GLUT.h>  //引用相关包

static int year=0,day=0,month=0;

void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT);  //清空颜色缓冲区
    //glPushMatrix();
    
    glColor3f(1,0,0);   //重置颜色
    glPushMatrix();  //压栈
    glTranslated(0,0, -0.8);
    glRotatef((GLfloat)day,0,0,1);
    glutWireSphere(1,100,100);   //绘制太阳
    
    glRotatef((GLfloat)day,0,1,0);  //沿y轴旋转
     //将场景中的物体沿x轴正方向移动2个单位长
    //glRotatef((GLfloat)day,0,1,0);
    glTranslatef(2,1,1);//沿y轴旋转
    glColor3f(0,1,0);
    
    //glPopAttrib();
    glRotatef((GLfloat)day,0,0,1);
    glutWireSphere(0.3,100,100);   //绘制地球
    
    
    glTranslatef(1,0,0);
    glColor3f(0,0,1);
    glTranslatef(0.2,0,0);
    glRotatef((GLfloat)month,0,1,0);
    glutWireSphere(0.1,100,100);
    
    glPopMatrix(); //出栈
    glutSwapBuffers();
    glFlush();   //刷新窗口以显示当前绘制图形
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
    //glFrustum(-1,1,-1,1,1.5,20.0);  //用透视矩阵乘以当前矩阵(left,Right,bottom,top,near,far);
    
    gluLookAt(0,5,5,0,0,0,0,1,0);
}

void shap()
{
    year=(year+2)%360;
    day=(day+2)%360;
    month=(month+1)%360;
    glutPostRedisplay();
    glutTimerFunc(20, shap,1);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); //固定格式
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
    glutInitWindowSize(800, 800);    //显示框的大小
    glutInitWindowPosition(400,400); //确定显示框左上角的位置
    glutCreateWindow("第7个OpenGL程序(太阳系)");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(20,  shap,1);
    glutMainLoop(); //进人GLUT事件处理循环
    return 0;
}

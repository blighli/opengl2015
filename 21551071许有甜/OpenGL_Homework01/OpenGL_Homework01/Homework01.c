#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/wglew.h>
#include <stdio.h>
#include <math.h>
#pragma comment (lib, "freeglut.lib")
#pragma comment (lib, "glew32.lib")

GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// 定义环境光的颜色
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// 定义漫反射光的颜色
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };					// 定义光源的位置
GLUquadricObj* quadric;


// OpenGL初始化
void initGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_TEXTURE_2D);											// 开启2D纹理映射
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);						// 设置环境光
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);						// 设置漫反射光
	quadric = gluNewQuadric();											// 建立一个曲面对象指针
	gluQuadricTexture(quadric, GLU_TRUE);								// 建立纹理坐标
	gluQuadricDrawStyle(quadric, GLU_FILL);								// 用面填充
	glEnable(GL_LIGHTING);												// 打开光照
	glEnable(GL_LIGHT1);												// 打开光源1
}

//////////////////////////////////////////////////////////////////////////
// 太阳、地球和月球
// 一年12个月，假设共360天，每个月30天
static int day = 100; // day的变化：从 0到 359
void myDisplay(void)
{
	// 设置投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);										// 将坐标系移入屏幕8.0f
	glRotatef(10, 1.0f, 0.0f, 0.0f);									// 将坐标系绕x轴旋转10度
	gluLookAt(0, 50, -50, 0, 0, 0, 0, 0, 1);
	
	// 绘制红色的太阳
	glDisable(GL_LIGHTING);
	glColor4f(1.0f, 0.0f, 0.0f,0.5f);
	gluSphere(quadric, 17.2f, 32, 32);
	glEnable(GL_LIGHTING);												// 开启光照
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);					// 设置光源1的当前位置

 	// 绘制蓝色的地球
	glDisable(GL_LIGHT0);												// 关闭光照
	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 0.0f, 1.0f);
	glDisable(GL_LIGHTING);
	glRotatef(day / 360.0*360.0, 0.0f, 1.0f, 0.0f);						// 将坐标系绕Y轴旋转角度，控制地球公转
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);									// 将坐标系绕X轴旋转-90度
	glTranslatef(30.0f, 0.0f, 0.0f);
	glPushMatrix();														// 当前模型视图矩阵入栈
	glRotatef(day / 360.0*360.0, 0.0f, 0.0f, 1.0f);						// 将坐标系绕Z轴旋转角度，控制地球自转
	gluSphere(quadric, 3.9f, 32, 32);									// 地球球体
	glPopMatrix();														// 当前模型视图矩阵出栈
	glEnable(GL_LIGHTING);												// 开启光照


 	// 绘制白色的月亮
//	glDisable(GL_LIGHTING);												// 关闭光照
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, 1.0f);	// 将坐标系绕Z轴旋转mp_Angle角度，控制月亮公转
	glTranslatef(8.5f, 0.0f, 0.0f);										// 右移0.5f
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, 1.0f);	// 将坐标系绕Z轴旋转ms_Angle角度，控制月亮自转
	gluSphere(quadric, 1.2f, 32, 32);									// 绘制月亮星体
//	glEnable(GL_LIGHTING);												// 开启光照
	
	glutSwapBuffers();
	glFlush();
}

void update(int p)
{
	day++;
	if (day > 360)
	{
		day = 0;
	}
	glutTimerFunc(30, update, 0);
	glutPostRedisplay();
}

// 设置窗口改变大小时的处理函数
void Reshape(int width, int height)
{
	if (height == 0)
	{
		height = 600;
	}
	// 设置视口
	glViewport(0, 0, width, height);
	// 设置投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("太阳-地球-月亮");
	initGL();
	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(Reshape);	// 设置窗口改变大小时的处理函数
	glutTimerFunc(30, update, 1);
	glutMainLoop();
	return 0;
}


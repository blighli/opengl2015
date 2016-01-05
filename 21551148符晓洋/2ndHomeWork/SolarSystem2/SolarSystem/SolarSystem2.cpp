
#include <gl/glew.h>
#include <gl/glut.h>
#include <gl/glext.h>
#include <gl/glaux.h>
#include <cmath>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 640

GLint sun_self_rot = 0;
GLint earth_circle_rot = 0;
GLint earth_self_rot = 0;
GLint moon_circle_rot = 0;
GLint moon_self_rot = 0;

GLuint uSunTexture;
GLuint uEarthTexture;
GLuint uMoonTexture;

GLUquadricObj* qSunTexture;
GLUquadricObj* qEarthTexture;
GLUquadricObj* qMoonTexture;

AUX_RGBImageRec* pSunTexture = nullptr;
AUX_RGBImageRec* pEarthTexture = nullptr;
AUX_RGBImageRec* pMoonTexture = nullptr;

void displayInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	qSunTexture = gluNewQuadric();								  // Create A New Quadratic
	gluQuadricNormals(qSunTexture, GL_SMOOTH);					  // Generate Smooth Normals For The Quad
	gluQuadricTexture(qSunTexture, GL_TRUE);						  // Enable Texture Coords For The Quad

	qEarthTexture = gluNewQuadric();								  // Create A New Quadratic
	gluQuadricNormals(qEarthTexture, GL_SMOOTH);					  // Generate Smooth Normals For The Quad
	gluQuadricTexture(qEarthTexture, GL_TRUE);						  // Enable Texture Coords For The Quad

	qMoonTexture = gluNewQuadric();								  // Create A New Quadratic
	gluQuadricNormals(qMoonTexture, GL_SMOOTH);					  // Generate Smooth Normals For The Quad
	gluQuadricTexture(qMoonTexture, GL_TRUE);						  // Enable Texture Coords For The Quad


	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);	// Set Up Sphere Mapping

	pSunTexture = auxDIBImageLoad(L"Texture/sun.bmp");
	glGenTextures(1, &uSunTexture);
	glBindTexture(GL_TEXTURE_2D, uSunTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pSunTexture->sizeX, pSunTexture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pSunTexture->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	pEarthTexture = auxDIBImageLoad(L"Texture/earth.bmp");
	glGenTextures(1, &uEarthTexture);
	glBindTexture(GL_TEXTURE_2D, uEarthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pEarthTexture->sizeX, pEarthTexture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pEarthTexture->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	pMoonTexture = auxDIBImageLoad(L"Texture/moon.bmp");
	glGenTextures(1, &uMoonTexture);
	glBindTexture(GL_TEXTURE_2D, uMoonTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pMoonTexture->sizeX, pMoonTexture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pMoonTexture->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//绘制太阳
	glPushMatrix();
	//定义太阳光源，它是一种白色光源  
	{//此处的一对大括号是代码块，一方面可以使其中的内容逻辑集中，另一方面可以局部变量作用域
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };//光源的位置
		GLfloat sun_light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };//环境光强
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };//漫反射光强
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };//镜面反射光
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	}
	{//定义太阳的材质并绘制太阳  
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat sun_mat_shininess = 30.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient); //环境变量  
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse); //散射模式  
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular); //镜面反射  
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission); //发射，散发喷射  
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
		glRotatef((GLfloat)sun_self_rot, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, uSunTexture);
		gluSphere(qSunTexture, 1, 40, 32); //绘制太阳
	}
	glPopMatrix();
	//
	
	//绘制地球
	glPushMatrix();
	{//定义地球材质并绘制地球 
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient); //环境变量  
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse); //散射模式  
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular); //镜面反射  
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission); //发射，散发喷射  
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
	}
	glBegin(GL_LINE_LOOP);
	GLfloat earth_track_angle = 0;
	GLint earth_track_num = 100;//想用100条直接来模拟圆
	GLfloat earth_angle_step = 2 * 3.14f / earth_track_num;//每次增加的角度
	for (earth_track_angle = 0; earth_track_angle < 2 * 3.14; earth_track_angle += earth_angle_step)
		glVertex3f(3 * sin(earth_track_angle), 0.0, 3 * cos(earth_track_angle));
	glEnd();
	glRotatef((GLfloat)earth_circle_rot, 0, 1, 0); //沿y轴旋转 
	glTranslatef(3, 0, 0); //将场景中的物体沿x轴正方向移动3个单位长
	glRotatef((GLfloat)earth_self_rot, 0, 1, 0);  //沿y轴旋转
	glBindTexture(GL_TEXTURE_2D, uEarthTexture);
	gluSphere(qEarthTexture, 0.3, 40, 32);   //绘制地球
	//

	//绘制月球
	{//定义月球材质并绘制月球 
		GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat moon_mat_diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat moon_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat moon_mat_emission[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat moon_mat_shininess = 30.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, moon_mat_ambient); //环境变量  
		glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_mat_diffuse); //散射模式  
		glMaterialfv(GL_FRONT, GL_SPECULAR, moon_mat_specular); //镜面反射  
		glMaterialfv(GL_FRONT, GL_EMISSION, moon_mat_emission); //发射，散发喷射  
		glMaterialf(GL_FRONT, GL_SHININESS, moon_mat_shininess);
	}
	glBegin(GL_LINE_LOOP);
	GLfloat moon_track_angle = 0;
	GLint moon_track_num = 100;//想用100条直接来模拟圆
	GLfloat moon_angle_step = 2 * 3.14f / moon_track_num;//每次增加的角度
	for (moon_track_angle = 0; moon_track_angle < 2 * 3.14; moon_track_angle += moon_angle_step)
		glVertex3f(sin(moon_track_angle), 0.0, cos(moon_track_angle));
	glEnd();
	glRotatef((GLfloat)moon_circle_rot, 0, 1, 0);
	glTranslatef(1, 0, 0); //将场景中的物体沿x轴正方向移动1个单位长
	glRotatef((GLfloat)moon_self_rot, 0, 1, 0);  //沿y轴旋转
	glColor3f(1, 1, 1);   //设置白色绘图
	glBindTexture(GL_TEXTURE_2D, uMoonTexture);
	gluSphere(qMoonTexture, 0.15, 40, 32);   //绘制月球

	glPopMatrix(); //出栈
	//
	
	glutSwapBuffers();
	glFlush();   //刷新窗口以显示当前绘制图形
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);   //设置机口
	glMatrixMode(GL_PROJECTION);  //指定哪一个矩阵是当前矩阵
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 20);   //创建透视投影矩阵(fovy,aspect,zNear,zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glFrustum(-1,1,-1,1,1.5,20.0);  //用透视矩阵乘以当前矩阵(left,Right,bottom,top,near,far);
	gluLookAt(0, 5, 5, 0, 0, 0, 0, 1, 0);
}

void changeAngle(int id)
{
	earth_circle_rot = (earth_circle_rot + 2) % 360;
	earth_self_rot = (earth_self_rot + 2) % 360;
	moon_circle_rot = (moon_circle_rot + 2) % 360;
	moon_self_rot = (moon_self_rot + 2) % 360;
	sun_self_rot = (sun_self_rot + 1) % 360;
	glutPostRedisplay();
	glutTimerFunc(33, changeAngle, 1);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv); //固定格式
	glutInitDisplayMode(GLUT_RGBA |GLUT_DOUBLE);   //缓存模式
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);    //显示框的大小
	glutInitWindowPosition(0, 0); //确定显示框左上角的位置
	glutCreateWindow("Glut绘制太阳系");
	displayInit();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);//当窗口变化时保证物体不变形
	glutTimerFunc(33, changeAngle, 1);//隔33秒调用一次改变角度函数
	glutMainLoop(); //进人GLUT事件处理循环
	return 0;
}



#include <GL/glut.h>
#include<windows.h>

static GLfloat sunRevolute   = 0.0f;	//太阳自传天数
static GLfloat earthRevolute = 0.0f;	//地球自传天数
static GLfloat earthRotate   = 200.0f;	//地球公转天数
static GLfloat moonRevolute  = 0.0f;	//月球自传天数
static GLfloat moonRotate    = 10.0f;	//月球公转天数


static int day = 0; // day 的变化：从 0 到 359
void myDisplay(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75,1,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,20,-25,0,0,0,0,-1,0);

	// 定义太阳光源
	{
	GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	}

	// 定义太阳的材质并绘制太阳
	{
	GLfloat sun_mat_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_diffuse[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
	GLfloat sun_mat_shininess = 10.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);
	glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glutWireSphere(7, 200, 200);
	}

	// 定义地球的材质并绘制地球
	{
	GLfloat earth_mat_ambient[] = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat earth_mat_diffuse[] = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat earth_mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
	glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(12.0f, 0.0f, 0.0f);
	glutWireSphere(2, 200, 200);
	}

	//定义月亮的材质并绘制月亮
	{
	GLfloat moon_mat_ambient[] = {1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat moon_mat_diffuse[] = {1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat moon_mat_specular[] = {1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat moon_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat moon_mat_shininess = 50.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, moon_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, moon_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, moon_mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, moon_mat_shininess);
	glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(5.0f, 0.0f, 0.0f);
	glutWireSphere(1, 100, 100);
	}
	glFlush();
	glutSwapBuffers();
}



void myIdle(void)
{

++day;
if( day >= 360 )
	day = 0;
Sleep(100);
myDisplay();
}
int main(int argc, char *argv[])
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
glutInitWindowPosition(100, 100);
glutInitWindowSize(500, 500);
glutCreateWindow("太阳、地球、月亮");
glutDisplayFunc(&myDisplay);
glutIdleFunc(&myIdle); 
glutMainLoop();
return 0;
}

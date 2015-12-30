#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

#include <math.h>
#include <stdio.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLShaderManager shaderManager;
GLMatrixStack modelViewMatrix;
GLMatrixStack projectionMatrix;
GLFrustum viewFrustum;
GLGeometryTransform transformPipeline;

GLTriangleBatch sunSphereBatch;
GLTriangleBatch earthSphereBatch;
GLTriangleBatch moonSphereBatch;
GLBatch floorBatch;
GLFrame cameraFrame;

void SetupRc()
{
	//初始化着色管理器
	shaderManager.InitializeStockShaders();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//做一个环
	gltMakeSphere(sunSphereBatch, 0.4f, 30, 30);
	//做一个球体
	gltMakeSphere(earthSphereBatch, 0.2f, 26, 13);
	//做一个小球体
	gltMakeSphere(moonSphereBatch, 0.1f, 18, 9);

	//做一个地板
	floorBatch.Begin(GL_LINES, 324);
	for(GLfloat x = -20.0; x <= 20.0f; x += 0.5)
	{
		floorBatch.Vertex3f(x, -0.55f, 20.0f);
		floorBatch.Vertex3f(x, -0.55f, -20.0f);

		floorBatch.Vertex3f(20.0f, -0.55f, x);
		floorBatch.Vertex3f(-20.0f, -0.55f, x);
	}
	floorBatch.End();
}

void ChangeSize(int nWidth, int nHeight)
{
	glViewport(0, 0, nWidth, nHeight);
	
	//创建投影矩阵，并加载它的投影矩阵堆栈
	viewFrustum.SetPerspective(35.0f, float(nWidth)/float(nHeight), 1.0f, 100.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());

	//设置转换通道使两个矩阵堆叠
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void RenderScene()
{
	//设定颜色值
	static GLfloat vSunColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
	static GLfloat vEarthColor[] = {0.0f, 0.0f, 1.0f, 1.0f};
	static GLfloat vMoonColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
	static GLfloat vFloorColor[] = { 0.0f, 1.0f, 0.0f, 1.0f};

	//基于时间的动画
	static CStopWatch rotTimer;
	float yRot = rotTimer.GetElapsedSeconds() * 60.0f;

	//清除颜色，深度缓冲
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//保存当前模型视图矩阵（单位矩阵）
	modelViewMatrix.PushMatrix();

	M3DMatrix44f mCamera;
	cameraFrame.GetCameraMatrix(mCamera);
	modelViewMatrix.PushMatrix(mCamera);

	//变换光源的位置到眼睛坐标
	M3DVector4f vLightPos = {0.0f, 10.0f, 5.0f, 1.0f};
	M3DVector4f vLightEyePos;
	m3dTransformVector4(vLightEyePos, vLightPos, mCamera);

	//绘制地板
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vFloorColor);
	floorBatch.Draw();

	//显示为线框球
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//绘制正在旋转的太阳
	modelViewMatrix.Translate(0.0f, 0.0f, -3.5f);

	//保存变化
	modelViewMatrix.PushMatrix();

	//应用一个旋转方式，绘制太阳
	modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vSunColor);
	sunSphereBatch.Draw();
	modelViewMatrix.PopMatrix();

	//应用另一个旋转方式，再平移，然后绘制地球
	modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
	modelViewMatrix.Translate(0.8f, 0.0f, 0.0f);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vEarthColor);
	earthSphereBatch.Draw();

	//应用另一个旋转方式，再平移，然后绘制月球
	modelViewMatrix.Rotate(yRot * -4.0f, 0.0f, 1.0f, 0.0f);
	modelViewMatrix.Translate(0.4f, 0.0f, 0.0f);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vMoonColor);
	moonSphereBatch.Draw();

	//恢复之前的模型视图矩阵（单位矩阵）
	modelViewMatrix.PopMatrix();
	modelViewMatrix.PopMatrix();    
	modelViewMatrix.PopMatrix();

	//执行缓冲区交换
	glutSwapBuffers();

	//告诉GLUT重复做
	glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
	float linear = 0.1f;
	float angular = float(m3dDegToRad(5.0f));

	if(key == GLUT_KEY_UP)
		cameraFrame.MoveForward(linear);
	if(key == GLUT_KEY_DOWN)
		cameraFrame.MoveForward(-linear);
	if(key == GLUT_KEY_LEFT)
		cameraFrame.RotateWorld(angular, 0.0f, 1.0f, 0.0f);
	if(key == GLUT_KEY_RIGHT)
		cameraFrame.RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
}

int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);

	glutCreateWindow("SphereWorld");

	glutSpecialFunc(SpecialKeys);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);

	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	SetupRc();
	glutMainLoop();

	return 0;
}

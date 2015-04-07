#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#include <GL/glut.h>
#endif

GLFrame             viewFrame;
GLFrustum           viewFrustum;
GLTriangleBatch     sphereBatch;
GLMatrixStack       modelViewMatrix;
GLMatrixStack       projectionMatrix;
GLGeometryTransform transformPipeline;
GLShaderManager     shaderManager;

GLuint	ADSPhoneShader;		// ADS光线着色器
GLint	locAmbient;			// 环境光颜色
GLint   locDiffuse;			// 漫反射颜色
GLint   locSpecular;		// 镜面反射颜色
GLint	locLight;			// 视点坐标系下光源坐标
GLint	locMVP;				// 模型视图投影矩阵
GLint	locMV;				// 模型视图矩阵
GLint	locNM;				// 模型视图矩阵旋转分量

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_DEPTH_TEST); // 开启深度测试
	glEnable(GL_CULL_FACE);  // 开启表面剔除

    shaderManager.InitializeStockShaders();
    viewFrame.MoveForward(4.0f);

    gltMakeSphere(sphereBatch, 1.0f, 26, 13);

    ADSPhoneShader = shaderManager.LoadShaderPairWithAttributes("ADSPhong.vp", "ADSPhong.fp", 2, GLT_ATTRIBUTE_VERTEX, "vVertex",
			GLT_ATTRIBUTE_NORMAL, "vNormal"); // 加载着色器程序

    // 初始化location of uniform
    locAmbient  = glGetUniformLocation(ADSPhoneShader, "ambientColor");
	locDiffuse  = glGetUniformLocation(ADSPhoneShader, "diffuseColor");
	locSpecular = glGetUniformLocation(ADSPhoneShader, "specularColor");
	locLight    = glGetUniformLocation(ADSPhoneShader, "vLightPosition");
	locMVP      = glGetUniformLocation(ADSPhoneShader, "mvpMatrix");
	locMV       = glGetUniformLocation(ADSPhoneShader, "mvMatrix");
	locNM       = glGetUniformLocation(ADSPhoneShader, "normalMatrix");
}

void ShutdownRC(void) {
    
}

void RenderScene(void) {
    static CStopWatch rotTimer;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓存区和深度缓冲区
    modelViewMatrix.PushMatrix(viewFrame); 
    {
		modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 10.0f, 0.0f, 1.0f, 0.0f);
        GLfloat vEyeLight[] = { -100.0f, 100.0f, 100.0f };
		GLfloat vAmbientColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat vDiffuseColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat vSpecularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glUseProgram(ADSPhoneShader); // 使用phone着色器
		glUniform4fv(locAmbient, 1, vAmbientColor);
		glUniform4fv(locDiffuse, 1, vDiffuseColor);
		glUniform4fv(locSpecular, 1, vSpecularColor);
		glUniform3fv(locLight, 1, vEyeLight);
		glUniformMatrix4fv(locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
		glUniformMatrix4fv(locMV, 1, GL_FALSE, transformPipeline.GetModelViewMatrix());
		glUniformMatrix3fv(locNM, 1, GL_FALSE, transformPipeline.GetNormalMatrix());
        sphereBatch.Draw();
    }
    modelViewMatrix.PopMatrix();
    glutSwapBuffers();
	glutPostRedisplay();
}

void ChangeSize(int w, int h) {
	if(h == 0)
		h = 1;
    glViewport(0, 0, w, h);
    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 100.0f);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}


int main(int argc, char* argv[]) {
    gltSetWorkingDirectory(argv[0]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("ADS Lighting, Phong Shading");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
    }
	
	SetupRC();    
	glutMainLoop();
	ShutdownRC();
    return 0;
}
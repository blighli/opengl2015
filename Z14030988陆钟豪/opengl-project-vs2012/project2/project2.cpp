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
#include <GL/glut.h>
#endif

GLShaderManager		shaderManager;			// Shader Manager
GLMatrixStack		modelViewMatrix;		// Modelview Matrix
GLMatrixStack		projectionMatrix;		// Projection Matrix
GLFrustum			viewFrustum;			// View Frustum
GLGeometryTransform	transformPipeline;		// Geometry Transform Pipeline

GLBatch				floorBatch;
GLTriangleBatch     sunBatch;
GLTriangleBatch     earthBatch;
GLTriangleBatch     moonBatch;

GLFrame             cameraFrame;

void SpecialKeys(int key, int x, int y);
void MouseAction(int button, int state, int x, int y);
void MotionAction(int x, int y);
void ChangeSize(int nWidth, int nHeight);
void RenderScene(void);
void SetupRC();

int main(int argc, char *argv[]) {
    gltSetWorkingDirectory(argv[0]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);

    glutCreateWindow("Deom2");

    glutSpecialFunc(SpecialKeys);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutMouseFunc(MouseAction);
    glutMotionFunc(MotionAction);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    SetupRC();
    glutMainLoop();    
    return 0;
}

void SetupRC() {
    shaderManager.InitializeStockShaders();

    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    cameraFrame.MoveUp(1.0); // init camera

    floorBatch.Begin(GL_LINES, 324);
    for(GLfloat x = -20.0; x <= 20.0f; x+= 0.5) {
        floorBatch.Vertex3f(x, -0.55f, 20.0f);
        floorBatch.Vertex3f(x, -0.55f, -20.0f);

        floorBatch.Vertex3f(20.0f, -0.55f, x);
        floorBatch.Vertex3f(-20.0f, -0.55f, x);
    }
    floorBatch.End();    

    gltMakeSphere(sunBatch, 0.5f, 26, 13);
    gltMakeSphere(earthBatch, 0.1f, 26, 13);
    gltMakeSphere(moonBatch, 0.03f, 26, 13);
}

void ChangeSize(int nWidth, int nHeight) {
    glViewport(0, 0, nWidth, nHeight);

    viewFrustum.SetPerspective(35.0f, float(nWidth)/float(nHeight), 1.0f, 100.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());

    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void RenderScene(void) {
    static GLfloat vFloorColor[] = { 0.0f, 1.0f, 0.0f, 1.0f};
    static GLfloat vSunColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    static GLfloat vEarthColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    static GLfloat vMoonColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    static CStopWatch	rotTimer;
	float yEarthRot = rotTimer.GetElapsedSeconds() * 360.0f / 36.5f;
    float yMoonRot = rotTimer.GetElapsedSeconds() * 360.0f / 3.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    M3DMatrix44f mCamera;
    cameraFrame.GetCameraMatrix(mCamera);
    modelViewMatrix.PushMatrix(mCamera);
    {
        M3DVector4f vLightPos = { 10.0f, 10.0f, 10.0f, 1.0f };
        M3DVector4f vLightEyePos;
        m3dTransformVector4(vLightEyePos, vLightPos, mCamera);

        modelViewMatrix.Translate(0.0f, 0.0f, -10.0f);

        // Draw the ground
	    shaderManager.UseStockShader(GLT_SHADER_FLAT,
								 transformPipeline.GetModelViewProjectionMatrix(),
								 vFloorColor);	
	    floorBatch.Draw();    

        modelViewMatrix.PushMatrix();
        {
            shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), 
                                     transformPipeline.GetProjectionMatrix(), vLightEyePos, vSunColor);
            sunBatch.Draw();
            modelViewMatrix.PushMatrix();
            {
                modelViewMatrix.Rotate(yEarthRot, 0.0f, 1.0f, 0.0f);
                modelViewMatrix.Translate(0.0f, 0.0f, 5.0f);
                shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), 
                                     transformPipeline.GetProjectionMatrix(), vLightEyePos, vEarthColor);
                earthBatch.Draw();
                {
                    modelViewMatrix.Rotate(yMoonRot, 0.0f, 1.0f, 0.0f);
                    modelViewMatrix.Translate(0.0f, 0.0f, 0.2f);
                    shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), 
                                     transformPipeline.GetProjectionMatrix(), vLightEyePos, vMoonColor);
                    moonBatch.Draw();
                }
            }
            modelViewMatrix.PopMatrix();
        }
        modelViewMatrix.PopMatrix();

    }
    modelViewMatrix.PopMatrix();    

    glutSwapBuffers();
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
    
	float linear = 0.1f;
	float angular = float(m3dDegToRad(5.0f));
	
    switch (key)
    {
    case GLUT_KEY_UP:
        cameraFrame.MoveForward(linear);
        break;
    case GLUT_KEY_DOWN:
        cameraFrame.MoveForward(-linear);
        break;
    case GLUT_KEY_LEFT:
        cameraFrame.MoveRight(linear);
        break;
    case GLUT_KEY_RIGHT:
        cameraFrame.MoveRight(-linear);
        break;
    case GLUT_KEY_PAGE_UP:
        cameraFrame.MoveUp(linear);
        break;
    case GLUT_KEY_PAGE_DOWN:
        cameraFrame.MoveUp(-linear);
        break;
    default:
        break;
    }

}

int mx, my = -1;

void MouseAction(int button, int state, int x, int y){
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN) {
            mx = x;
            my = y;
        }
        else {
            mx = -1;
            my = -1;
        }
        break;
    default:
        break;
    }
}

void MotionAction(int x, int y) {
    if(mx == -1 || my == -1) return ;
    float angular = float(m3dDegToRad(0.1f));
    int dx = x - mx;
    int dy = y - my;
    cameraFrame.RotateWorld(angular * dx, 0.0f, 1.0f, 0.0f);
    cameraFrame.RotateWorld(angular * dy, 1.0f, 0.0f, 0.0f);
    mx = x;
    my = y;
}
#include <GLTools.h>            // OpenGL toolkit
#include <GLShaderManager.h>    // Shader Manager Class
#include <math3d.h>

#ifdef __APPLE__
#include <glut/glut.h>          // OS X version of GLUT
#else
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif

GLBatch	triangleBatch;
GLShaderManager	shaderManager;

GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f, 
		              0.5f, 0.0f, 0.0f,
				      0.0f, 0.5f, 0.0f };

GLfloat vColors[] = { 1.0f, 0.0f, 0.0f, 1.0f, 
		              0.0f, 1.0f, 0.0f, 1.0f,
				      0.0f, 0.0f, 1.0f, 1.0f };

// Window has changed size, or has just been created. In either case, we need
// to use the window dimensions to set the viewport and the projection matrix.
void ChangeSize(int w, int h) {
	glViewport(0, 0, w, h);
}

// This function does any needed initialization on the rendering context. 
// This is the first opportunity to do any OpenGL related tasks.
void SetupRC() {

    glClearColor(0.7f, 0.7f, 0.7f, 1.0f );
    
	shaderManager.InitializeStockShaders();

	// Load up a triangle
	
	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.CopyColorData4f(vColors);
	triangleBatch.End();
}

// Called to draw scene
void RenderScene(void) {
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    M3DMatrix44f identityMatrix;
    m3dLoadIdentity44(identityMatrix);
    shaderManager.UseStockShader(GLT_SHADER_SHADED, identityMatrix);
	triangleBatch.Draw();

	// Perform the buffer swap to display back buffer
	glutSwapBuffers();
    //glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
    GLfloat stepSize = 0.025f;
    if(key == GLUT_KEY_UP && vVerts[7] + stepSize <= 1.0f) {
        vVerts[1] += stepSize;
        vVerts[4] += stepSize;
        vVerts[7] += stepSize;
    }
    else if(key == GLUT_KEY_DOWN && vVerts[1] - stepSize >= -1.0f) {
        vVerts[1] -= stepSize;
        vVerts[4] -= stepSize;
        vVerts[7] -= stepSize;
    }
    else if(key == GLUT_KEY_RIGHT && vVerts[3] + stepSize <= 1.0f) {
        vVerts[0] += stepSize;
        vVerts[3] += stepSize;
        vVerts[6] += stepSize;
    }
    else if(key == GLUT_KEY_LEFT && vVerts[0] - stepSize >= -1.0f) {
        vVerts[0] -= stepSize;
        vVerts[3] -= stepSize;
        vVerts[6] -= stepSize;
    }
    triangleBatch.CopyVertexData3f(vVerts);
    glutPostRedisplay();
}

// Main entry point for GLUT based programs
int main(int argc, char* argv[]) {
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    SetupRC();
    glutMainLoop();
    return 0;
}

//
//  main.cpp
//  OpenGL_Homework_1
//
//  Created by YunhanXu on 15/12/9.
//  Copyright © 2015年 YunhanXu. All rights reserved.
//

#include "GLTools.h"
#include "GLShaderManager.h"
#include "GLFrustum.h"
#include "GLBatch.h"
#include "GLFrame.h"
#include "GLMatrixStack.h"
#include "GLGeometryTransform.h"
#include "StopWatch.h"

#include <math.h>
#include <stdio.h>

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLShaderManager shaderManager;  // Shader 管理器
GLMatrixStack modelViewMatrix;     // 模型视图矩阵
GLMatrixStack projectionMatrix;		// 投影矩阵
GLFrustum viewFrustum;
GLGeometryTransform transformPipeline;    // 多边形位移管线

GLTriangleBatch sunSphereBatch;
GLTriangleBatch earthSphereBatch;
GLTriangleBatch moonSphereBatch;
GLBatch floorBatch;
GLFrame cameraFrame;


void SetupRC()
{
    shaderManager.InitializeStockShaders();
    
    glEnable(GL_DEPTH_TEST);// 开启深度测试
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // 太阳球体
    gltMakeSphere(sunSphereBatch, 0.4f, 30, 30);
    
    // 地球球体
    gltMakeSphere(earthSphereBatch, 0.2f, 26, 13);
    
    // 月球球体
    gltMakeSphere(moonSphereBatch, 0.1, 18, 9);
    
    // 画轨道
    floorBatch.Begin(GL_LINES, 324);
    for(GLfloat x = -20.0; x <= 20.0f; x+= 0.5)
    {
        floorBatch.Vertex3f(x, -0.55f, 20.0f);
        floorBatch.Vertex3f(x, -0.55f, -20.0f);
        
        floorBatch.Vertex3f(20.0f, -0.55f, x);
        floorBatch.Vertex3f(-20.0f, -0.55f, x);
    }
    floorBatch.End();
}

void ChangeSize(int nWidth, int nHeight)// 视口大小改变响应函数
{
    glViewport(0, 0, nWidth, nHeight);
    
    viewFrustum.SetPerspective(35.0f, float(nWidth)/float(nHeight), 1.0f, 100.0f);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void RenderScene()
{
    static GLfloat vSunColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };// 太阳颜色
    static GLfloat vEarthColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };// 地球颜色
    static GLfloat vMoonColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };// 月球颜色
    static GLfloat vFloorColor[] = { 0.0f, 1.0f, 0.0f, 1.0f};// 轨道颜色
    
    static CStopWatch rotTimer;
    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
    
    // 清除颜色
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // 当前模型视图矩阵压入堆栈
    modelViewMatrix.PushMatrix();
    
    M3DMatrix44f mCamera;
    cameraFrame.GetCameraMatrix(mCamera);
    modelViewMatrix.PushMatrix(mCamera);
    
    // 灯光位置
    M3DVector4f vLightPos = { 0.0f, 10.0f, 5.0f, 1.0f };
    M3DVector4f vLightEyePos;
    m3dTransformVector4(vLightEyePos, vLightPos, mCamera);
    
    // 画轨道
    shaderManager.UseStockShader(GLT_SHADER_FLAT,
                                 transformPipeline.GetModelViewProjectionMatrix(),
                                 vFloorColor);
    floorBatch.Draw();
    
    // 显示线框
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // 显示太阳
    modelViewMatrix.Translate(0.0f, 0.0f, -3.5f);
    
    // 矩阵入栈
    modelViewMatrix.PushMatrix();
    
				// 旋转并显示太阳
				modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
				shaderManager.UseStockShader(GLT_SHADER_FLAT,
                                             transformPipeline.GetModelViewProjectionMatrix(), vSunColor);
				sunSphereBatch.Draw();// 出栈
    
				// 地球
				modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
				modelViewMatrix.Translate(0.8f, 0.0f, 0.0f);
				shaderManager.UseStockShader(GLT_SHADER_FLAT,
                                             transformPipeline.GetModelViewProjectionMatrix(), vEarthColor);
				earthSphereBatch.Draw();
    
				// 月球
				modelViewMatrix.Rotate(yRot * -4.0f, 0.0f, 1.0f, 0.0f);
				modelViewMatrix.Translate(0.4f, 0.0f, 0.0f);
				shaderManager.UseStockShader(GLT_SHADER_FLAT,
                                             transformPipeline.GetModelViewProjectionMatrix(), vMoonColor);
				moonSphereBatch.Draw();
    
    // 出栈
    modelViewMatrix.PopMatrix();
    modelViewMatrix.PopMatrix();
    modelViewMatrix.PopMatrix();
    
    glutSwapBuffers();
    
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
    glutInitWindowSize(1024, 768);
    
    glutCreateWindow("Solar System Simulation");
    
    glutSpecialFunc(SpecialKeys);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) 
    {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    SetupRC();
    glutMainLoop();   
    
    return 0;
}

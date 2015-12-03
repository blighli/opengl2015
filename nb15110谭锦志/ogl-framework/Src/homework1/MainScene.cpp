#include "MainScene.h"
#include "../ShaderLoader/LoadShaders.h"
#include <math.h>

MainScene::MainScene()
{
	m_posx = -1.5f;
}

MainScene::~MainScene()
{

}

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs{ArrayBuffer, NumBuffers};
enum Attrib_IDs
{
	vPosition = 0
};


// 显示模式
void MainScene::ViewMode()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 透视模式
	gluPerspective(45.0f, this->GetWidth() / this->GetHeight(), 0.01f, 100.0f);

	// 摄像机位置
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0); 

	// 选择模式观察矩阵
	glMatrixMode(GL_MODELVIEW); 

	glLoadIdentity();
}


GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertcies = 6;


BOOL MainScene::initGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);

	// 选择深度测试方
	glDepthFunc(GL_LEQUAL);
	
	glShadeModel(GL_SMOOTH);

	// 最精细的透视计算
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 

	////////
	
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	GLfloat vertices[NumVertcies][2] = {
		{-0.90, -0.90},
		{ 0.85, -0.90},
		{-0.90,  0.85},
		{ 0.90, -0.85},
		{ 0.90,  0.90},
		{-0.85,  0.90}
	};
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "shader/triangles.vert"},
		{GL_FRAGMENT_SHADER, "shader/triangles.frag"},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program); 
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
	
	/////////
	return TRUE;
}

BOOL MainScene::DrawGL(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清除颜色和深度缓存

	//////////////////////////////////////////////////////////////////////////
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertcies);
	//////////////////////////////////////////////////////////////////////////

	glFlush(); // 刷新GL命令队列
	return TRUE;
}

BOOL MainScene::UpdateGL(GLvoid)
{
	/* 
	* 系统键盘映射说明
	* F1->F12     : VK_F1 -> VK_F12
	* num 0 -> 9  : VK_NUMPAD0 -> VK_NUMPAD9
	* char A -> Z : 0x41 -> ... 递增 
	*/

	if (keyDown(VK_F1))
	{
		m_posx += 0.01f;
	}

	return TRUE;
}

GLvoid MainScene::DestroyGL(GLvoid)
{

}


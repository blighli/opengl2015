//
//  main.cpp
//  OpenGL_Z14030917韩坚
//
//  Created by HJ on 15/4/9.
//  Copyright (c) 2015年 HJ. All rights reserved.
//
//#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

#include "MyLoader.h"
#include <iostream>
using namespace std;
MyLoader Loader;
static GLfloat Spin = 0;
GLint MyList;
void BuildList()
{
    MyList = glGenLists( 1 );
    glNewList( MyList, GL_COMPILE );
    Model TempModel = Loader.GetModel();
    for( size_t i = 0; i != TempModel.MyObject.size(); ++ i )
    {
        const Object& object = TempModel.MyObject[i];
        glBegin( GL_TRIANGLES );
        for(int j = 0; j != object.Faces.size(); j++)
        {
            const Face& ThisFace = object.Faces[ j ];
            const Material& MyMaterial = TempModel.MyMaterial[ ThisFace.MaterialPos ];
            glNormal3f( ThisFace.Normal.x, ThisFace.Normal.y, ThisFace.Normal.z );
            glColor4f( MyMaterial.diffuseColor[ 0 ], MyMaterial.diffuseColor[ 1 ],
                      MyMaterial.diffuseColor[ 2 ], MyMaterial.transparency );
            if( MyMaterial.transparency )
                glEnable( GL_BLEND );
            for( size_t k = 0; k != 3; ++ k )
            {
                size_t index = object.Faces[ j ].Index[ k ];
                glVertex3f( object.Vertexs[ index ].x, object.Vertexs[ index ].y, object.Vertexs[ index ].z );
            }
            if( MyMaterial.transparency )
                glDisable( GL_BLEND );
        }
        glEnd();
    }
    glEndList();
}
void Init()
{
    try
    {
        Loader.OpenFile( "Car.3DS" );
        Loader.LoadFile();
        Loader.CloseFile();
    }
    catch( runtime_error e )
    {
        cout << e.what() << endl;
    }
    catch(...)
    {
        cout << "未知错误" << endl;
    }
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    GLfloat Ambient[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat Diffuse[4] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat Position[4] = { 0.0, 0.0, -1.0, 1.0 };
    GLfloat GlobalLight[4] = { 0.1, 0.1, 0.1, 1.0 };
    glLightfv( GL_LIGHT0, GL_AMBIENT, Ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, Diffuse );
    glLightfv( GL_LIGHT0, GL_POSITION, Position );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, GlobalLight );
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glBlendFunc( GL_SRC_ALPHA, GL_SRC_ALPHA );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    BuildList();
}
void SpinDisplay()
{
    if( ++ Spin > 360 )
        Spin -= 360;
    glutPostRedisplay();
}
void Display()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    gluLookAt( 0., 0.0, 200.0 , 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
    glRotatef( Spin, 0.0, 1.0, 0.0 );
    glCallList( MyList );
    glFlush();
    glutSwapBuffers();
}
void Reshape( int width, int high )
{
    if ( high == 0 )
        high = 1;
    glViewport( 0, 0, static_cast< GLsizei >( width ), static_cast< GLsizei >( high ) );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0, static_cast< GLdouble >( width ) / static_cast< GLdouble >( high ), 0.1, 1000.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}
int main( int argc, char* argv[] )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
    glutInitWindowSize( 800, 600 );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( "MySystem" );
    Init();
    glutDisplayFunc( Display );
    glutReshapeFunc( Reshape );
    glutIdleFunc( SpinDisplay );
    glutMainLoop();
    return 0;
}



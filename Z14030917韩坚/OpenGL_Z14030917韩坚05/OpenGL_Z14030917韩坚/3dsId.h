//
//  3dsId.h
//  OpenGL_Z14030917韩坚
//
//  Created by HJ on 15/4/9.
//  Copyright (c) 2015年 HJ. All rights reserved.
//

#ifndef _3DS_ID_H_
#define _3DS_ID_H_
const GLsizei   PRIMARY             = 0x4D4D;
const GLsizei   MAINOBJECT          = 0x3D3D;     // 网格对象的版本号
const GLsizei   EDITKEYFRAME        = 0xB000;     // 所有关键帧信息的头部
const GLsizei   MATERIAL         = 0xAFFF;     // 保存纹理信息
const GLsizei   OBJECT          = 0x4000;     // 保存对象的面、顶点等信息
const GLsizei   MATNAME             = 0xA000;     // 保存材质名称
const GLsizei   OBJECT_MESH         = 0x4100;     // 新的网格对象
const GLsizei   OBJECT_VERTICES     = 0x4110;    // 对象顶点
const GLsizei   OBJECT_FACES     = 0x4120;    // 对象的面
const GLsizei   OBJECT_MATERIAL     = 0x4130;    // 对象的材质
const GLsizei MAT_AMBIENT    = 0xa010;
const GLsizei MAT_DIFFUSE    = 0xa020;
const GLsizei MAT_SPECULAR   = 0xa030;
const GLsizei MAT_SHININESS   = 0xa040;
const GLsizei MAT_TRANSPARENCY = 0xa050;
const GLsizei INT_PERCENTAGE   = 0x0030;
const GLsizei FLOAT_PERCENTAGE = 0x0031;
const GLsizei COLOR_F     = 0x0010;
const GLsizei COLOR_24    = 0x0011;
#endif

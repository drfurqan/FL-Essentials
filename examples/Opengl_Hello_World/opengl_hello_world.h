#pragma once
#ifndef opengl_hello_world_h__
#define opengl_hello_world_h__

/*********************************************************************************
created:	2017/03/14   01:03AM
filename: 	opengl_hello_world.h
file base:	opengl_hello_world
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Simplest OpenGL program written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_OpenGLWindow.h>

// Description:
// Inherited class from OpenGL window
class GLWindow : public R3D::Fle_OpenGLWindow
{
public:
	// Description:
	// Default Constructor that will create a GL window.
	GLWindow(int _w, int _h, const char* _title);

	// Description:
	// Function that will be called only once at the start of the window.
	// It uses to initialize the OpenGL states or any other data such as textures etc.
	void initializeGL() override;

	// Description:
	// Function for all kinds of OpenGL rendering.
	void paintGL() override;
};

#endif // opengl_hello_world_h__

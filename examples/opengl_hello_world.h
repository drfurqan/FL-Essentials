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

#include "Fle_OpenGLWindow.h"

using namespace R3D;

class GLWindow : public Fle_OpenGLWindow
{
public:
	GLWindow(int _w, int _h, const char* _title);

	// Description:
	// Function that will be called only once at the start of the window.
	// It uses to initialize the OpenGL states or any other data such as textures etc.
	void initializeGL();

	// Function for all kinds of OpenGL rendering.
	void paintGL();
};

#endif // opengl_hello_world_h__

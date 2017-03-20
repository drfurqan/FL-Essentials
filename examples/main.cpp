/*********************************************************************************
created:	2017/03/14   01:03AM
filename: 	opengl_hello_world_main.cpp
file base:	opengl_hello_world_main
file ext:	cpp
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

#include "Fle_Core.h"
#include "Fle_OpenGLWindow.h"

#include <glew.h>
#include <Fl/gl.h>
#include <Fl/glu.h>
#include <Fl/glut.h>

using namespace R3D;

// Description:
// Inherited class from OpenGL window
class GLWindow : public Fle_OpenGLWindow
{
public:
	// Description:
	// Default Constructor that will create a GL window.
	GLWindow(int _w, int _h, const char* _title) : Fle_OpenGLWindow(_w, _h, _title)
	{
	}

	// Description:
	// Function that will be called only once at the start of the window.
	// It uses to initialize the OpenGL states or any other data such as textures etc.
	void initializeGL()
	{
		// enable the depth test state.
		glEnable(GL_DEPTH_TEST);
	}

	// Description:
	// Function for all kinds of OpenGL rendering.
	void paintGL();
};


int main1(int argc, char* argv[])
{
	// FLE library initialization with default modes.
	Fle_Core::init();

	// create OpenGL window by specifying width, height and title.
	GLWindow win(1024, 500, "Simplest OpenGL Program");
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}


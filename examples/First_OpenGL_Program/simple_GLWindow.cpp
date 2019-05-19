/*********************************************************************************
created:	2017/03/14   01:03AM
filename: 	GLWindow.cpp
file base:	GLWindow
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

#include <FLE/Fle_Core.h>
#include <FLE/Fle_OpenGLWindow.h>

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
	GLWindow(int _w, int _h, const char* _title) : 
		Fle_OpenGLWindow(_w, _h, _title)
	{
	}

	// Description:
	// Function that will be called only once at the start of the window.
	// It uses to initialize the OpenGL states or any other data such as textures etc.
	void initializeGL() override
	{
		// enable the depth test state.
		glEnable(GL_DEPTH_TEST);
	}

	// Description:
	// Function for all kinds of OpenGL rendering.
	void paintGL() override
	{
		glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}
};


int main(int argc, char* argv[])
{
	// FLE library initialization with default modes.
	Fle_Core::init();

	// create OpenGL window by specifying width, height and title.
	GLWindow win(1024, 500, "Simplest OpenGL Program");
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}


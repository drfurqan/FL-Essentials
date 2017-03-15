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

#include "opengl_hello_world.h"
#include "Fl/gl.h"
#include "Fl/glu.h"
#include "Fl/glut.h"

GLWindow::GLWindow(int _w, int _h, const char* _title) : 
Fle_OpenGLWindow(_w, _h, _title)
{

}

void GLWindow::initializeGL()
{
	// enable the depth test state.
	glEnable(GL_DEPTH_TEST);
}

void GLWindow::paintGL()
{
	// clear the screen with black color.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// clear the color and depth buffers for displaying the next frame.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set width and height of the view port.
	// w() and h() are the width and height of this window.
	glViewport(0, 0, w(), h());
	// setup perspective projection with angle, aspect ratio and near and far planes.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, static_cast<double>(w()) / static_cast<double>(h()), 0.1, 1000.0);

	// setup the camera eye. 
	// first 3 arguments (0.0, 0.0, 100.0) are for eye position
	// next 3 (0.0, 0.0, 0.0) are the eye center
	// and last 3 are the up vector, meaning flipping of the camera.
	gluLookAt(0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// push matrix for creating the local coordinate system.
	glPushMatrix();
	// rotate 45 degrees around x-axes because x is 1.0f.
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	// rotate 30 degrees around y-axes because y is 1.0f.
	glRotatef(10, 0.0f, 1.0f, 0.0f);
	// assign red color to tea pot.
	glColor3f(1.0f, 0.0f, 0.0f);

	// render teapot.
	glutWireTeapot(20.0);
	// you can draw various models using GLUT, like
	// glutWireTorus(5, 20, 36, 36);

	// pop matrix that was pushed above.
	glPopMatrix();
}
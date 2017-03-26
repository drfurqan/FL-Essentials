/*********************************************************************************
created:	2017/03/20   02:16AM
filename: 	my_first_opengl_program.cpp
file base:	my_first_opengl_program
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
	void paintGL()
	{
		// clear the screen with black color (setting up background color).
		glClearColor(0.2f, 0.3f, 0.4f, 0.0f);
		// clear the color and depth buffers for displaying the next frame.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// setting up viewport and camera. 
		/************************************************************************/
		// set width and height of the viewport.
		// w() and h() are the width and height of this window.
		// it tells OpenGL how to convert from coordinates to pixel values.
		glViewport(0, 0, w(), h());
		glMatrixMode(GL_PROJECTION);			// switch to setting the camera perspective
		glLoadIdentity();						// reset the camera
												// set the camera perspective
												// arguments: the camera angle, the width-to-height ratio, the near z clipping coordinate, the far z clipping coordinate
		gluPerspective(45.0, static_cast<double>(w()) / static_cast<double>(h()), 0.1, 10000.0);

		// setup the camera eye. 
		gluLookAt(
			0.0, 0.0, 100.0,					// camera eye position
			0.0, 0.0, 0.0,						// camera eye center
			0.0, 1.0, 0.0);						// camera up vector
		glMatrixMode(GL_MODELVIEW);				// switch to the drawing perspective
		glLoadIdentity();						// reset the drawing perspective
		/************************************************************************/

		// drawing/rendering of shapes start from here.
		// rotation of global coordinate system.
		//glTranslatef(0.0f, 0.0f, 0.0f);			// translate in X, Y, Z directions.
		//glRotatef(45.0f, 1.0f, 0.0f, 0.0f);		// rotate 45 degrees around x-axes because x is 1.0f.
		//glRotatef(15, 0.0f, 1.0f, 0.0f);		// rotate 30 degrees around y-axes because y is 1.0f.

		glColor3f(1.0f, 0.0f, 0.0f);
		glutWireTeapot(20.0);

		glColor3f(0.0f, 0.0f, 1.0f);
		glutWireTorus(5, 30, 36, 36);
	}
};


int main()
{
	// FLE library initialization with default modes.
	Fle_Core::init();

	// create OpenGL window by specifying width, height and title.
	GLWindow win(1024, 500, "Simplest OpenGL Program");
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}


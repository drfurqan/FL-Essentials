/*********************************************************************************
created:	2017/04/13   01:16AM
filename: 	opengl_point_on_a_line_simulation.cpp
file base:	opengl_point_on_a_line_simulation
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	OpenGL simulation of a Point on a Line Equation.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Core.h>
#include <FLE/Fle_OpenGLWindow.h>
#include <FLE/Math/Fle_Vector3D.h>

#include <FL/gl.h>
#include <FL/glu.h>

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
		P1.set(-500, 100, 0);
		P2.set(500, 100, 0);
		alpha = 0.4f;
		getTimer().start();
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
			0.0, 0.0, 1100.0,					// camera eye position
			0.0, 0.0, 0.0,						// camera eye center
			0.0, 1.0, 0.0);						// camera up vector
		glMatrixMode(GL_MODELVIEW);				// switch to the drawing perspective
		glLoadIdentity();						// reset the drawing perspective
		/************************************************************************/

		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex3f(P1.x, P1.y, P1.z);
		glVertex3f(P2.x, P2.y, P2.z);
		glEnd();

		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex3f(P.x, P.y, P.z);
		glEnd();
	}

	void timerEvent()
	{
		P = P1 + alpha * (P2 - P1);

		alpha = alpha + 0.001f;
		if (alpha >= 1.f)
			alpha = 0.f;

		update();
	}

private:
	Vector3D P1;
	Vector3D P2;
	Vector3D P;
	float alpha;
};


int main()
{
	// FLE library initialization with default modes.
	Fle_Core::init();

	// create OpenGL window by specifying width, height and title.
	GLWindow win(1024, 500, "Point On A Line Simulation");
	win.show();

	// execute the main loop.
	return Fle_Core::exec();
}


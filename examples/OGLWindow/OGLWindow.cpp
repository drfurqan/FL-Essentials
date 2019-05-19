/*********************************************************************************
created:	2017/03/14   02:10AM
filename: 	OGLWindow.cpp
file base:	OGLWindow
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	OpenGL program to animate the scene, written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "OGLWindow.h"
#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/glut.H>

using namespace R3D;

GLWindow::GLWindow(int _x, int _y, int _w, int _h, const char* _title) :
	Fle_OpenGLWindow(_x, _y, _w, _h, _title),
	m_use_light_0(true),
	m_use_light_1(false),
	m_use_material(true),
	m_angle(0)
{
	// start the timer that will start calling timerEvent() function in real-time with around 60 fps. 
	m_timer.start();
}

GLWindow::GLWindow(int _w, int _h, const char* _title) : 
	Fle_OpenGLWindow(_w, _h, _title),
	m_use_light_0(true),
	m_use_light_1(false),
	m_use_material(true),
	m_angle(0)
{
	// start the timer that will start calling timerEvent() function in real-time with around 60 fps. 
	m_timer.start();
}

void GLWindow::initializeGL()
{
	// enable the depth test state.
	glEnable(GL_DEPTH_TEST);

	// because we want to setup lights/bulbs, so turn on the lighting for this scene.
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);	// for lighting and normals
}

void GLWindow::setupCamera()
{
	// set width and height of the view port.
	// w() and h() are the width and height of this window.
	glViewport(0, 0, w(), h());
	// setup perspective projection with angle, aspect ratio and near and far planes.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, static_cast<double>(w()) / static_cast<double>(h()), 0.1, 1000.0);

	// setup the camera eye. 
	gluLookAt(
		0.0, 0.0, 100.0,	// eye is at (0,0,100)
		0.0, 0.0, 0.0,      // center is at (0,0,0)
		0.0, 1.0, 0.);      // up is in positive Y direction
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// This routine draws the text string at the given (x,y,z) position.
// x,y,z:  Raster position for text
// txt:    String to draw
void drawText(float _x, float _y, float _z, char* _txt, float _red = 1.0f, float _green = 1.0f, float _blue = 1.0f, float _alpha = 1.0f)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(_red, _green, _blue, _alpha);
	glRasterPos3f(_x, _y, _z);
	while (*_txt != '\0')
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *_txt);
		_txt++;
	}
	glPopAttrib();
}

void GLWindow::paintGL()
{
	// clear the screen with black color.
	glClearColor(0.23f, 0.56f, 231.0f, 0.9f);
	// clear the color and depth buffers for displaying the next frame.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// place camera at the eye position.
	setupCamera();

	// set lights/bulbs to the scene.
	if (m_use_light_0)
		setupPointLight0();		// switch on of light/bulb 0.
	else
		glDisable(GL_LIGHT0);	// switch off of light/bulb 0.

	if (m_use_light_1)
		setupPointLight1();		// switch on of light/bulb 1.
	else
		glDisable(GL_LIGHT1);	// switch off of light/bulb 1.

	if (m_use_material)
		setupMaterial();		// set material color to 3D models.

	// push matrix for creating the local coordinate system.
	glPushMatrix();
	// rotate m_angle degrees around x-axes because x is 1.0f.
	glRotatef(m_angle, 1.0f, 0.0f, 0.0f);
	// rotate m_angle degrees around y-axes because y is 1.0f.
	glRotatef(m_angle, 0.0f, 1.0f, 0.0f);
	// rotate m_angle degrees around y-axes because z is 1.0f.
	glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

	// render teapot.
	glutSolidTeapot(15.0);
	// you can draw various models using GLUT, like
	glutWireTorus(5.0, 32.0, 20, 20);

	// pop matrix that was pushed above.
	glPopMatrix();

	// draw a line.
	glLineWidth(2.0f);			// line thickness
	glColor4f(1.f, 0.f, 1.f, 1.f);		// line color
	glBegin(GL_LINES);			// start drawing line
		glVertex3f(-50.f, 0.f, 0.f);		// first coordinates of the line P1
		glVertex3f(50.f, 0.f, 0.f);		// 2nd coordinates of the line P2
	glEnd();					// end drawing

	//// draw a triangle
	//glBegin(GL_TRIANGLES);
	//glColor3f(1, 0, 0);
	//glVertex3f(0, 0, 0);
	//glColor3f(0, 1, 0);
	//glVertex3f(0, 20, 0);
	//glColor3f(0, 0, 1);
	//glVertex3f(20, 0, 0);
	//glEnd();
}
int GLWindow::keyPressEvent(int _key)
{
	if (_key == '0')
	{
		m_use_light_0 = !m_use_light_0;		// toggle On/Off
		update();							// update/redraw the scene
		return 1;
	}
	else if (_key == '1')
	{
		m_use_light_1 = !m_use_light_1;		// toggle On/Off
		update();							// update/redraw the scene
		return 1;
	}
	else if (_key == 'm')
	{
		m_use_material = !m_use_material;	// toggle On/Off
		update();							// update/redraw the scene
		return 1;
	}

	return 0;
}

void GLWindow::setupPointLight0()
{
	// set the position of bulb 0.
	GLfloat light_position_0[] = { 0, 5, 1000, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);

	// give specular color (shininess) to bulb 0.
	GLfloat light_specular_0[] = { 1, 0.5, 0, 1 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular_0);
	
	glEnable(GL_LIGHT0);	// enable light 0, meaning to turn the switch ON of bulb 0.
}

void GLWindow::setupPointLight1()
{
	// set the position of bulb 1.
	GLfloat light_position_1[] = { 1000, 5, 1000, 1 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);

	// give specular color (shininess) to bulb 1.
	GLfloat light_specular_1[] = { 0.8f, 0.8f, 0.8f, 1 };
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular_1);

	glEnable(GL_LIGHT1);	// enable light 1, meaning to turn the switch ON of bulb 1.
}

void GLWindow::setupMaterial()
{
	GLfloat diffuse_material[] = { 0.751640f, 0.606480f, 0.226480f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material);

	GLfloat speular_material[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speular_material);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80.0f);
}

void GLWindow::timerEvent()
{
	// increment the angle and when it crosses the 360, make it zero.
	m_angle += 0.5f;
	if (m_angle >= 360.0f)
		m_angle = m_angle - 360.0f;

	// update or redraw the scene.
	update();
}

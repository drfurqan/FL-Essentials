/*********************************************************************************
created:	2017/03/14   02:10AM
filename: 	opengl_events_lights.cpp
file base:	opengl_events_lights
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	OpenGL program with Events, Lights, and Material written in FLE.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "opengl_events_lights.h"
#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/glut.H>

using namespace R3D;

GLWindow::GLWindow(int _w, int _h, const char* _title) : 
	Fle_OpenGLWindow(_w, _h, _title),
	m_use_light_0(true),
	m_use_light_1(false),
	m_use_material(false)
{

}

void GLWindow::initializeGL()
{
	// enable the depth test state.
	glEnable(GL_DEPTH_TEST);

	// because we want to setup lights/bulbs, so turn on the lighting for this scene.
	glEnable(GL_LIGHTING);
}

void GLWindow::paintGL()
{
	// clear the screen with black color.
	glClearColor(0.23f, 0.56f, 231.0f, 0.9f);
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
	// rotate 45 degrees around x-axes because x is 1.0f.
	glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
	// rotate 30 degrees around y-axes because y is 1.0f.
	glRotatef(5.0f, 0.0f, 1.0f, 0.0f);

	// render teapot.
	glutSolidTeapot(15.0);
	// you can draw various models using GLUT, like
	glutWireTorus(5.0, 32.0, 20, 20);

	// pop matrix that was pushed above.
	glPopMatrix();
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
	GLfloat light_position_1[] = { 0, 5, 1000, 1 };
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
